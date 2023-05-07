#include "pch.h"
#include "PortableDeviceObjectJ.h"
#include "PortableDevice.h"
#include "PortableDeviceContentJ.h"
#include "mtp.h"

#include <iostream>
#include <PortableDevice.h>

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
		if (hr == 0x80042009) { // Object does not exist
			jclass generalPortableDeviceException = env->FindClass("com/github/hms11rn/mtp/PortableDeviceException");
			env->ThrowNew(generalPortableDeviceException, "Specified Object could not be found (Was it deleted)?");
			return nullptr;
		}
		else if (hr == E_POINTER || hr == E_WPD_DEVICE_NOT_OPEN) {
			printf("GetSupportedeProperties Failed, hr = 0x%lx\n", hr);
			jclass deviceClosedException = env->FindClass("com/github/hms11rn/mtp/DeviceClosedException");
			env->ThrowNew(deviceClosedException, "Can't get Properties since the Device has been closed");
		}
		printf("Unknown error occured when trying to call GetSupportedProperties, hr = 0x%lx\n", hr);
		return nullptr;
	}
	IPortableDeviceValues* deviceValues{};
	 hr = p->GetValues(id, coll, &deviceValues);
	 if (!SUCCEEDED(hr)) {
		 handleException("DEVICE", "Failed to get IPortableDeviceValues ", hr);
	 }
	jobject keyAndValuesJava = GetKeyAndValuesMap(env, coll, &deviceValues);
	
	return keyAndValuesJava;
}

