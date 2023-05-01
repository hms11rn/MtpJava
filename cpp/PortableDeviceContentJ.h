#pragma once

#include <PortableDeviceApi.h>
#include "PortableDeviceObjectJ.h"
#include <jni.h>

static IPortableDeviceProperties* ppProperties;

class PortableDeviceContentJ
{
	public:
		PortableDeviceContentJ();
		PortableDeviceContentJ(IPortableDeviceContent*, LPWSTR deviceID);
		IPortableDeviceContent* getContent();
		
		IPortableDeviceProperties* getProperties();
		jstring addFile(JNIEnv* env, LPWSTR parent, jstring, jobject);
		jobject getObject(LPWSTR idd, JNIEnv* env);
		BOOL deleteFile(LPWSTR idd);

		IPortableDevicePropVariantCollection* getPropCollection();
};

