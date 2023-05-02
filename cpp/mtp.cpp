#include "pch.h"
#include "mtp.h"
#include <string>
#include <iostream>
#include "PortableDeviceManager.h"

using namespace std;


// Implementation of the native method getMtpNames()
JNIEXPORT jobjectArray JNICALL Java_com_github_hms11rn_mtp_Mtp_getMtpNames
(JNIEnv* env, jclass cls) {
	int device_count = getDeviceCount();
	jobjectArray strarr = env->NewObjectArray(device_count, env->FindClass("java/lang/String"), nullptr);
	for (int i = 0; i < device_count; ++i)
	{
		env->SetObjectArrayElement(strarr, i, env->NewStringUTF("test22"));
	}

	return strarr;
}

void handleException(char* name)
{
	cout << "Exception was thrown: " << name << endl;
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