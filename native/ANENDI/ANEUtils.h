#pragma once

#include "pch.h"


using std::string;
using namespace std;

typedef signed char			int8;
typedef signed short		int16;
typedef signed int			int32;
typedef signed long long	int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

#ifndef SafeDelete
#define SafeDelete(p) { delete (p); (p) = NULL; }
#endif //SafeDelete

#define SafeDeleteVideoArr(pArr) {delete[] pArr; pArr = 0;}



class ANEUtils {

public:

	FREObject AS_String(std::string value) {
		FREObject result;
		FRENewObjectFromUTF8(uint32_t(value.length()), reinterpret_cast<const uint8_t*>(value.data()), &result);
		return result;
	}
	FREObject AS_String(const char* value) {
		FREObject result;
		FRENewObjectFromUTF8(uint32_t(strlen(value)) + 1, reinterpret_cast<const uint8_t*>(value), &result);
		return result;
	}

	
	FREObject AS_int(int32_t value) {
		FREObject result;
		FRENewObjectFromInt32(value, &result);
		return result;
	}

	FREObject AS_uint(uint32_t value) {
		FREObject result;
		FRENewObjectFromUint32(value, &result);
		return result;
	}
	FREObject AS_uint(uint8_t value) {
		FREObject result;
		FRENewObjectFromUint32(value, &result);
		return result;
	}


	FREObject AS_Boolean(bool value) {
		FREObject result;
		FRENewObjectFromBool(value, &result);
		return result;
	}

	FREObject AS_Number(double value) {
		FREObject result;
		FRENewObjectFromDouble(value, &result);
		return result;
	}

	FREObject AS_Point(double x, double y) {
		FREObject obj;
		FREObject argv[] = {
			AS_Number(x),
			AS_Number(y)
		};
		FRENewObject(reinterpret_cast<const uint8_t*>("flash.geom.Point"), 2, argv, &obj, nullptr);
		return obj;
	}

	bool isFREResultOK(FREResult errorCode, std::string errorMessage) {
		if (FRE_OK == errorCode) return true;
		printf("isFREResultOK = %s", errorMessage.c_str());
		return false;
	}

	bool nativeBool(FREObject freObject) {
		uint32_t result = 0;
		auto ret = false;
		FREGetObjectAsBool(freObject, &result);
		if (result > 0) ret = true;
		return ret;
	}

	std::string nativeString(FREObject freObject) {
		uint32_t string1Length;
		const uint8_t* val;
		auto status = FREGetObjectAsUTF8(freObject, &string1Length, &val);

		if (isFREResultOK(status, "Could not convert UTF8."))
			return std::string(val, val + string1Length);
		return "";
	}

	uint32_t nativeUInt32(FREObject freObject) {
		uint32_t result = 0;
		auto status = FREGetObjectAsUint32(freObject, &result);
		isFREResultOK(status, "Could not convert FREObject to uint32_t.");
		return result;
	}

	int32_t nativeInt32(FREObject freObject) {
		int32_t result = 0;
		auto status = FREGetObjectAsInt32(freObject, &result);
		isFREResultOK(status, "Could not convert FREObject to int32_t.");
		return result;
	}

	double nativeDouble(FREObject freObject) {
		auto result = 0.0;
		auto status = FREGetObjectAsDouble(freObject, &result);
		isFREResultOK(status, "Could not convert FREObject to double.");
		return result;
	}

private:

};




