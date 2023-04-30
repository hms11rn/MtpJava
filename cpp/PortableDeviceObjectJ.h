#pragma once

#include <PortableDeviceApi.h>
#include <jni.h>

#ifndef _Included_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32
#define _Included_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32
#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32_getPropertiesN
	(JNIEnv*, jobject);

	JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32_init
	(JNIEnv* env, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
jobject getProperties(JNIEnv* env);

jobject keyAndValues(JNIEnv* env);


	
