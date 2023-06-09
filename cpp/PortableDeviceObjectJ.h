#include <PortableDeviceApi.h>
#include <jni.h>

#ifndef _Included_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32
#define _Included_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32
#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32_getPropertiesN
	(JNIEnv*, jobject, jstring id);

	JNIEXPORT jboolean JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32_isContainerN
	(JNIEnv* env, jobject cls, jstring idJava);

#ifdef __cplusplus
}
#endif
#endif

jobject keyAndValues(JNIEnv* env, LPWSTR id);