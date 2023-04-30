#include "pch.h"
#include "PortableDeviceContentJ.h"
#include <jni.h>
#include <iostream>
#include <string>

using namespace std;

IPortableDeviceContent* pContent;

PortableDeviceContentJ::PortableDeviceContentJ(IPortableDeviceContent* content, LPWSTR deviceID)
{
	if (ppProperties == nullptr) {
		pContent = content;
		HRESULT hr = content->Properties(&ppProperties);
		if (FAILED(hr)) {
			cout << "incorrect hr" << endl;
			// handle error
		}
	}
}

jobject PortableDeviceContentJ::getObject(LPWSTR idd, JNIEnv* env)
{
	jclass javaClass = env->FindClass("com/github/hms11rn/mtp/win32/PortableDeviceObjectWin32");
	jmethodID constructor = env->GetMethodID(javaClass, "<init>", "(Ljava/lang/String;)V");
	
	jstring idJava = env->NewString((jchar*)idd, wcslen(idd));
	jobject javaObject = env->NewObject(javaClass, constructor, idJava);
	return javaObject;
}



IPortableDeviceContent* PortableDeviceContentJ::getContent() {
	return pContent;
}


IPortableDeviceProperties* PortableDeviceContentJ::getProperties() {
	return ppProperties;
}

////////////////////
PortableDeviceContentJ::PortableDeviceContentJ()
{
}
