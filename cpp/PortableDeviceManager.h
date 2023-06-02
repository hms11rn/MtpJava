#pragma once

#include <jni.h>
#include <PortableDeviceApi.h>

/* Header for class com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32 */
HRESULT InitializeDeviceManager();
IPortableDeviceManager* getDeviceManager();

int getDeviceCount();
#ifndef _Included_com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32
#define _Included_com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32
#ifdef __cplusplus
extern "C" {
#endif
	/*
	 * Class:     com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32
	 * Method:    getDeviceCount
	 * Signature: ()I
	 */
	JNIEXPORT jint JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32_getDeviceCount
	(JNIEnv*);

	/*
	 * Class:     com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32
	 * Method:    getDeviceIDs
	 * Signature: ()[Ljava/lang/String;
	 */
	JNIEXPORT jobjectArray JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32_getDeviceIDs
	(JNIEnv*);

	/*
	 * Class:     com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32
	 * Method:    refresh
	 * Signature: ()V
	 */
	JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32_refresh
	(JNIEnv*);

#ifdef __cplusplus
}
#endif
#endif

