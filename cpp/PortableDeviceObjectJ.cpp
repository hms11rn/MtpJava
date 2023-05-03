#include "pch.h"
#include "PortableDeviceObjectJ.h"
#include "PortableDevice.h"
#include "PortableDeviceContentJ.h"
#include <iostream>

using namespace std;

LPWSTR wid;

JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32_init(JNIEnv* env, jobject cls, jstring idd)
{
	wid = (WCHAR*)env->GetStringChars(idd, nullptr);
}

JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32_getPropertiesN(JNIEnv* env, jobject cls, jstring idJava)
{
	LPWSTR id;
	id = (WCHAR*) env->GetStringChars(idJava, nullptr);
	return keyAndValues(env, id);
}



jobject keyAndValues(JNIEnv* env, LPWSTR id) {

	IPortableDeviceProperties* p = getPDProperties();
	IPortableDeviceKeyCollection* coll = {};
	HRESULT hr = p->GetSupportedProperties(id, &coll);
	if (FAILED(hr)) {
		// handle error
		return nullptr;
	}
	IPortableDeviceValues* deviceValues{};
	 hr = p->GetValues(id, coll, &deviceValues);
	 if (!SUCCEEDED(hr)) {
		 cout << "hr failed at getValues: " << hr << endl;
	 }
	jobject keyAndValuesJava = GetKeyAndValuesMap(env, coll, &deviceValues);
	
	return keyAndValuesJava;
}

