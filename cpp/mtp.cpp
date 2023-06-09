#include "pch.h"

#include "mtp.h"

#include <string>
#include <iostream>
#include "PortableDeviceManager.h"
#include <sstream>
using namespace std;

JavaVM* jvm = nullptr;

JNIEnv* getEnv();

JNIEnv* getEnv() {
	JNIEnv* env;
	JavaVMAttachArgs args;
	jvm->AttachCurrentThread((void**)&env, &args);
	return env;
}

JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_Mtp_registerJNI
(JNIEnv* envv) {
	
	envv->GetJavaVM(&jvm);
}


/*
TYPES: DEVICE_MGR - Device Manager
	   DEVICE - Portable Device
	   COM - Com Exception
*/
void handleException(const char* type, const char* msg, HRESULT hr)
{
	JNIEnv* env = getEnv();
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
		env->NewObject(deviceClosedException, env->GetMethodID(deviceClosedException, "<init>", "(Ljava/lang/String;)V"), env->NewStringUTF(oss.str().c_str()));
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


jobject GetKeyAndValuesMap(JNIEnv* env, IPortableDeviceKeyCollection* keys, IPortableDeviceValues* values) {
    jclass mapClass = env->FindClass("java/util/HashMap");
    if (mapClass == nullptr)
        return nullptr;

    jmethodID init = env->GetMethodID(mapClass, "<init>", "()V");
    jobject hashMap = env->NewObject(mapClass, init);
    jmethodID put = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    DWORD size = 0;

    HRESULT hr = keys->GetCount(&size);

    for (DWORD i = 0; i < size; i++) {
        PROPERTYKEY keyName;
        LPWSTR pszName;
        DWORD pszId;
        hr = keys->GetAt(i, &keyName);

        hr = StringFromCLSID(keyName.fmtid, &pszName);
        pszId = keyName.pid;
        // fill value
        wstring s = pszName;
        s.append(to_wstring(pszId));

        // key for java return value: format {guid}pid
        jstring keyJava = env->NewString((jchar*)s.c_str(), wcslen(s.c_str()));

        CoTaskMemFree(pszName); // pszName is no longer needed, free memory
        s.clear(); // s is no longer need as java key was created

        PROPVARIANT valueAt; // value of key
        hr = values->GetValue(keyName, &valueAt);
        VARTYPE valueType = valueAt.vt;
        switch (valueType) {
        case VT_LPWSTR: {
            LPWSTR valueAtStr = nullptr;
            values->GetStringValue(keyName, &valueAtStr);
            jstring singleValueJava = env->NewString((jchar*)valueAtStr, wcslen(valueAtStr));
            // free memory
            CoTaskMemFree(valueAtStr);
            env->CallObjectMethod(hashMap, put, keyJava, singleValueJava);
            env->DeleteLocalRef(singleValueJava);
            env->DeleteLocalRef(keyJava);
            break;
        }
        case VT_BOOL: {
            BOOL valueAtBool;
            values->GetBoolValue(keyName, &valueAtBool);
            jclass boolClass = env->FindClass("java/lang/Boolean");
            jmethodID initBool = env->GetMethodID(boolClass, "<init>", "(Z)V");
            jobject boolObject = env->NewObject(boolClass, initBool, valueAtBool);
            // free memory
            env->CallObjectMethod(hashMap, put, keyJava, boolObject);
            env->DeleteLocalRef(boolObject);
            env->DeleteLocalRef(keyJava);
            break;
        }
        case VT_UI4: {
            ULONG valueAtInt;
            values->GetUnsignedIntegerValue(keyName, &valueAtInt);
            jclass intClass = env->FindClass("java/lang/Integer");
            jmethodID initInt = env->GetMethodID(intClass, "<init>", "(I)V");
            jobject intObject = env->NewObject(intClass, initInt, valueAtInt);
            // free memory
            env->CallObjectMethod(hashMap, put, keyJava, intObject);
            env->DeleteLocalRef(intObject);
            env->DeleteLocalRef(keyJava);
            break;
        }
        case VT_UI8: {
            ULONGLONG valueAtInt;
            values->GetUnsignedLargeIntegerValue(keyName, &valueAtInt);
            jobject longJava = ConvertUnsignedLongLongToJava(env, valueAtInt);
            env->CallObjectMethod(hashMap, put, keyJava, longJava);
            // free memory
            env->DeleteLocalRef(longJava);
            env->DeleteLocalRef(keyJava);
            break;
        }
        case VT_CLSID: {
            LPWSTR valueAtCLSID = nullptr;
            values->GetStringValue(keyName, &valueAtCLSID);
            jstring singleValueJavaCLSID = env->NewString((jchar*)valueAtCLSID, wcslen(valueAtCLSID));
            // free memory
            CoTaskMemFree(valueAtCLSID);
            env->CallObjectMethod(hashMap, put, keyJava, singleValueJavaCLSID);
            env->DeleteLocalRef(singleValueJavaCLSID);
            env->DeleteLocalRef(keyJava);
            break;
        }
        case VT_DATE: {
            LPWSTR valueAtDate;
            values->GetStringValue(keyName, &valueAtDate);
            jstring singleValueJava = env->NewString((jchar*)valueAtDate, wcslen(valueAtDate));
            // free memory
            CoTaskMemFree(valueAtDate);
            env->CallObjectMethod(hashMap, put, keyJava, singleValueJava);
            env->DeleteLocalRef(singleValueJava);
            env->DeleteLocalRef(keyJava);
            break;
        }
        }

    }
    env->DeleteLocalRef(mapClass);
    return hashMap;
}