/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <PortableDeviceApi.h>

IPortableDeviceProperties* getPDProperties();

void initializePropVariantCollection();
IPortableDevicePropVariantCollection* getPropVariantCollection();


// portable device values
IPortableDeviceValues* getPortableDeviceValues();
HRESULT InitializePortableDeviceValues();
void releasePortableDeviceValues();
IPortableDevice* getPortableDevice();
HRESULT InitializePortableDevice();
void closePortableDevice();

HRESULT OpenDevice(LPCWSTR wszPnPDeviceID, IPortableDevice** ppDevice, LPCWSTR, int, int, int);
jobject GetKeyAndValuesMap(JNIEnv*, IPortableDeviceKeyCollection*, IPortableDeviceValues**);

/* Header for class com_github_hms11rn_mtp_win32_PortableDeviceWin32 */

#ifndef _Included_com_github_hms11rn_mtp_win32_PortableDeviceWin32
#define _Included_com_github_hms11rn_mtp_win32_PortableDeviceWin32
#ifdef __cplusplus
extern "C" {
#endif
	/*
	 * Class:     com_github_hms11rn_mtp_win32_PortableDeviceWin32
	 * Method:    getFriendlyName
	 * Signature: (Ljava/lang/String;)Ljava/lang/String;
	 */
	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getFriendlyName
	(JNIEnv*, jclass, jstring);

	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getManufacturer
	(JNIEnv*, jclass, jstring);

	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getDescription
	(JNIEnv*, jclass, jstring);

	JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getProperties
	(JNIEnv*, jclass, jstring);

	/*
	* Class:     com_github_hms11rn_mtp_win32_PortableDeviceWin32
	 * Method:    open
	* Signature: ()V
	 */
	JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_openN
	(JNIEnv*, jobject);

	/*
	 * Class:     com_github_hms11rn_mtp_win32_PortableDeviceWin32
	 * Method:    close
	 * Signature: ()V
	 */
	JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_closeN
	(JNIEnv*, jobject);

	JNIEXPORT jobjectArray JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getRootObjects
	(JNIEnv*, jobject);


#ifdef __cplusplus
}
#endif
#endif
