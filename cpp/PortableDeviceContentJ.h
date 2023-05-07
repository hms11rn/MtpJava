#pragma once

#include "PortableDeviceObjectJ.h"

#include <jni.h>
#include <PortableDeviceApi.h>

static IPortableDeviceProperties* ppProperties;

class PortableDeviceContentJ
{
	public:
		PortableDeviceContentJ(IPortableDeviceContent*, LPWSTR deviceID);
		IPortableDeviceContent* getContent();
		
		IPortableDeviceProperties* getProperties();
		jstring addFile(JNIEnv* env, LPWSTR parent, jstring, jobject, jstring contentType, jstring contentFormat, HRESULT*);
		jstring addFileFromInputStream(JNIEnv* env, LPWSTR parent, LPWSTR name, jobject inputStream, LPWSTR type, LPWSTR format);
		jstring addFolder(JNIEnv* env, LPWSTR javaName, LPWSTR parent);
		void copyFile(JNIEnv* env, LPWSTR id, LPWSTR outDir);
		void updateProperty(JNIEnv* env, LPWSTR id, GUID category, DWORD pid, LPWSTR value);

		jobject getObject(LPWSTR idd, JNIEnv* env);
		BOOL deleteFile(LPWSTR idd, int recursion);
		jbyteArray getBytes(JNIEnv* env, LPWSTR id);

		IPortableDevicePropVariantCollection* getPropCollection();

};

