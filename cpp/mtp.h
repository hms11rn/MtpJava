#include <jni.h>
#include "portabledeviceapi.h"

#ifndef _Included_com_github_hms11rn_Mtp
#define _Included_com_github_hms11rn_Mtp
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_github_hms11rn_Mtp
 * Method:    registerJNI
 */
JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_Mtp_registerJNI
  (JNIEnv *);

#ifdef __cplusplus
}
#endif
#endif

// Handles all types of exceptions that might be thrown in a location that there is no JNIEnv*
void handleException(const char* type, const char* name, HRESULT hr);
// Converts Unsinged Long to Java BigInterger (Note to Self: since Java 8 added support for unsigned longs Long#parseUnsignedLong)
jobject ConvertUnsignedLongLongToJava(JNIEnv* env, ULONGLONG number);