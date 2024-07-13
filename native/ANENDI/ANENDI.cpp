#include "pch.h"
#include "ANENDI.h"

#include "ANEUtils.h"


#include <Processing.NDI.Lib.h>
#ifdef _WIN32
#ifdef _WIN64
#pragma comment(lib, "Processing.NDI.Lib.x64.lib")
#else // _WIN64
#pragma comment(lib, "Processing.NDI.Lib.x86.lib")
#endif // _WIN64
#endif


extern "C" {

	const char* TAG = "ANENDI";

	ANEUtils* ANEutils = new ANEUtils();
	bool debug = false;


	//初始化
	FREObject isSupported(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		printf("\n%s,%s", TAG, "isSupport");
		return ANEutils->AS_Boolean(NDIlib_initialize());	
		//return ANEutils->AS_Boolean(true);
		//const char* version = NDIlib_version();
	}


	FREObject isDeBug(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		debug = ANEutils->nativeBool(argv[0]);
		printf("\n%s %s  %d", TAG, "isDeBug", debug);
		return NULL;
	}


	FREObject ANE_NDIlib_send_create(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		printf("\n%s,%s", TAG, "ANE_NDIlib_send_create");

		std::string ndi_name = ANEutils->nativeString(argv[0]);
		std::string groups = ANEutils->nativeString(argv[1]);
		bool is_video = ANEutils->nativeBool(argv[2]);
		bool is_audio = ANEutils->nativeBool(argv[3]);
		/*
		return NULL;
		*/
		
		NDIlib_send_create_t* config = new NDIlib_send_create_t();
		if (!ndi_name.empty())config->p_ndi_name = ndi_name.c_str();
		if (!groups.empty())config->p_groups = groups.c_str();
		config->clock_video = is_video;
		config->clock_audio = is_audio;


		// We create the NDI sender
		NDIlib_send_instance_t pNDI_send = NDIlib_send_create(config);
		if (!pNDI_send)
			return ANEutils->AS_Number(0);

		double int_NDI_send = (intptr_t)pNDI_send;
		if (debug) {
			std::cout << "\n intptr_t=" << int_NDI_send << std::endl;
		}
		return ANEutils->AS_Number(int_NDI_send);
	}

	FREObject ANE_NDIlib_send_destroy(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{

		double intptr = ANEutils->nativeDouble(argv[0]);
		if (debug)printf("\n%s %s  %lf", TAG, "ANE_NDIlib_send_destroy", intptr);
		NDIlib_send_instance_t pNDI_send = reinterpret_cast<NDIlib_send_instance_t>((uintptr_t)intptr);

		if (pNDI_send) {
			// Destroy the NDI sender
			NDIlib_send_destroy(pNDI_send);
			return ANEutils->AS_Boolean(true);
		}
		return ANEutils->AS_Boolean(false);

	}

	FREObject ANE_NDIlib_send_send_video_v2(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{

		double intptr = ANEutils->nativeDouble(argv[0]);
		if (debug)printf("\n%s %s  %lf", TAG, "ANE_NDIlib_send_send_video_v2", intptr);
		NDIlib_send_instance_t pNDI_send = reinterpret_cast<NDIlib_send_instance_t>((uintptr_t)intptr);

		if (pNDI_send) {

			int width = ANEutils->nativeInt32(argv[1]);
			int height = ANEutils->nativeInt32(argv[2]);
			NDIlib_video_frame_v2_t NDI_video_frame;
			NDI_video_frame.xres = width;
			NDI_video_frame.yres = height;
			NDI_video_frame.FourCC = NDIlib_FourCC_video_type_BGRA;
			NDI_video_frame.p_data = (uint8_t*)malloc(NDI_video_frame.xres * NDI_video_frame.yres * 4);

			//ARGB
			//BGRA

			FREObject objectByteArray = argv[3];
			FREByteArray byteArray;
			FREAcquireByteArray(objectByteArray, &byteArray);
			memcpy(NDI_video_frame.p_data, byteArray.bytes, byteArray.length);
			FREReleaseByteArray(objectByteArray);

			NDIlib_send_send_video_v2(pNDI_send, &NDI_video_frame);

			SafeDeleteVideoArr(NDI_video_frame.p_data);

			return ANEutils->AS_Boolean(true);
		}
		return ANEutils->AS_Boolean(false);
	}
	

	///
	// Flash Native Extensions stuff	
	void ANENDIContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToSet, const FRENamedFunction** functionsToSet) {

		static FRENamedFunction extensionFunctions[] =
		{
			{ (const uint8_t*)"isSupported",     NULL, &isSupported },
			{ (const uint8_t*)"isDeBug",     NULL, &isDeBug },
			
			{ (const uint8_t*)"ANE_NDIlib_send_create",     NULL, &ANE_NDIlib_send_create },

			{ (const uint8_t*)"ANE_NDIlib_send_destroy",     NULL, &ANE_NDIlib_send_destroy },


			{ (const uint8_t*)"ANE_NDIlib_send_send_video_v2",     NULL, &ANE_NDIlib_send_send_video_v2 },
			

		};

		*numFunctionsToSet = sizeof(extensionFunctions) / sizeof(FRENamedFunction);
		*functionsToSet = extensionFunctions;
	}

	void ANENDIContextFinalizer(void* extData)
	{
		printf("\n%s,%s", TAG, "ANEWinCoreContextFinalizer：release()");
		// Not required, but nice
		NDIlib_destroy();
	}


	void ANENDIExtInitializer(void** extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer)
	{
		*ctxInitializer = &ANENDIContextInitializer;
		*ctxFinalizer = &ANENDIContextFinalizer;
	}

	void ANENDIExtFinalizer(void* extData)
	{
		return;
	}
}