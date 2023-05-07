#include "pch.h"

#include "mtp.h"

#include <string>
#include <iostream>
#include "PortableDeviceManager.h"
#include <sstream>
using namespace std;


JNIEnv* env;

JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_Mtp_registerJNI
(JNIEnv* envv) {
	env = envv;
}


/*
TYPES: DEVICE_MGR - Device Manager
	   DEVICE - Portable Device
	   COM - Com Exception
*/
void handleException(const char* type, const char* msg, HRESULT hr)
{
	ostringstream oss;
	oss << msg << " (HRESULT: 0x" << std::hex << hr << ")";

	if (type == "DEVICE_MGR") {
		jclass generalPortableDeviceException = env->FindClass("com/github/hms11rn/mtp/PortableDeviceException");
		env->ThrowNew(generalPortableDeviceException, oss.str().c_str());
	}
	else if (type == "DEVICE") {
		jclass generalPortableDeviceException = env->FindClass("com/github/hms11rn/mtp/PortableDeviceException");
		env->ThrowNew(generalPortableDeviceException, oss.str().c_str());
	}
	else if (type == "COM") {
		jclass deviceClosedException = env->FindClass("com/github/hms11rn/mtp/ComException");
		jthrowable ex = (jthrowable)env->NewObject(deviceClosedException, env->GetMethodID(deviceClosedException, "<init>", "(Ljava/lang/String;)V"), env->NewStringUTF(oss.str().c_str()));
		env->Throw(ex);
	}
}

jobject ConvertUnsignedLongLongToJava(JNIEnv* env, ULONGLONG number)
{
	jbyteArray buffer;
	jclass cls;
	jmethodID mid;

	buffer = env->NewByteArray(9);
	for (int i = 0; i < 8; i++)
		env->SetByteArrayRegion(buffer, (i + 1), 1, (jbyte*)((byte*)&number + 7 - i));

	cls = env->FindClass("java/math/BigInteger");
	mid = env->GetMethodID(cls, "<init>", "([B)V");
	return env->NewObject(cls, mid, buffer);
}