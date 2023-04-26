#include "pch.h"
#include "mtp.h"
#include "portabledeviceapi.h"
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

