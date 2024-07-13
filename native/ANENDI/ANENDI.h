#pragma once


#include "pch.h"


extern "C"
{
	__declspec(dllexport) void ANENDIExtInitializer(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, FREContextFinalizer* ctxFinalizerToSet);
	__declspec(dllexport) void ANENDIExtFinalizer(void* extData);
}