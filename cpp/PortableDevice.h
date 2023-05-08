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

jstring getFriendlyName(JNIEnv* env, jstring deviceID);



HRESULT OpenDevice(LPCWSTR wszPnPDeviceID, IPortableDevice** ppDevice, LPCWSTR, int, int, int);
jobject GetKeyAndValuesMap(JNIEnv*, IPortableDeviceKeyCollection*, IPortableDeviceValues*);

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

	JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getObjectsN
	(JNIEnv*, jobject, jstring);

	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFileObjectN
	(JNIEnv* env, jobject, jstring name, jstring parent, jobject file, jstring type, jstring format);

	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFileFromInputStreamN
	(JNIEnv* env, jobject, jstring name, jstring parent, jobject inputStream, jstring type, jstring format);
	
	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFolderObjectN
	(JNIEnv* env, jobject, jstring name, jstring parent);
	JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_copyFileN
	(JNIEnv* env, jobject, jstring id, jstring path);
	JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_updatePropertyN
	(JNIEnv* env, jobject, jstring id, jstring fmtid, jint pid, jstring value);

	JNIEXPORT jboolean JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_deleteFileN
	(JNIEnv* env, jobject, jstring id, jint recursion);

	JNIEXPORT jbyteArray JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getBytesN(JNIEnv* env, jobject, jstring id);




#ifdef __cplusplus
}
#endif
#endif
