#include <jni.h>
#include <PortableDeviceApi.h>

IPortableDevice* getPortableDevice();
IPortableDeviceProperties* getPortableDeviceProperties();

IPortableDevicePropVariantCollection* getPropVariantCollection();
IPortableDeviceKeyCollection* getKeyCollection();
IPortableDeviceValues* getPortableDeviceValues();

IPortableDeviceContent2* getContent2();

jstring getFriendlyName(JNIEnv* env, jstring deviceID);

HRESULT OpenDevice(LPCWSTR wszPnPDeviceID, IPortableDevice** ppDevice, LPCWSTR, int, int, int);

// jobject GetKeyAndValuesMap(JNIEnv*, IPortableDeviceKeyCollection*, IPortableDeviceValues*);

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
	/*
	 * Class:     com_github_hms11rn_mtp_win32_PortableDeviceWin32
	 * Method:    getManufacturer
	 * Signature: (Ljava/lang/String;)Ljava/lang/String;
	 */
	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getManufacturer
	(JNIEnv*, jclass, jstring);
	/*
	* Class:     com_github_hms11rn_mtp_win32_PortableDeviceWin32
	* Method:    getDescription
	* Signature: (Ljava/lang/String;)Ljava/lang/String;
	*/
	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getDescription
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

	/// Object Methods
	
	JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getProperties
	(JNIEnv*, jclass, jstring objectID);

	JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getObjectsN
	(JNIEnv*, jobject, jstring objID);

	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFileObjectN
	(JNIEnv* env, jobject, jstring name, jstring parent, jobject file, jstring type, jstring format);

	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFileFromInputStreamN
	(JNIEnv* env, jobject, jstring name, jstring parent, jobject inputStream, jstring type, jstring format);
	
	JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFolderObjectN
	(JNIEnv* env, jobject, jstring name, jstring parent);
	JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_copyFileN
	(JNIEnv* env, jobject, jstring id, jstring path);
	JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_updatePropertyN
	(JNIEnv* env, jobject, jstring id, jstring fmtid, jint pid, jint varType, jstring value);

	JNIEXPORT jboolean JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_deleteFileN
	(JNIEnv* env, jobject, jstring id, jint recursion);

	JNIEXPORT jbyteArray JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getBytesN(JNIEnv* env, jobject, jstring id);


	/* Header for class com_github_hms11rn_mtp_win32_PortableDeviceOutputStreamWin32 */

#ifdef __cplusplus
}
#endif
#endif

#ifndef _Included_com_github_hms11rn_mtp_win32_PortableDeviceOutputStreamWin32
#define _Included_com_github_hms11rn_mtp_win32_PortableDeviceOutputStreamWin32

#ifdef __cplusplus
extern "C" {
#endif
	//  PortableDeviceOutputStreamWin32
	JNIEXPORT jint JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceOutputStreamWin32_writeBuffer
	(JNIEnv*, jobject, jstring id, jbyteArray buffer, jint bufferSize, jboolean append, jboolean rewrite);


#ifdef __cplusplus
}
#endif
#endif