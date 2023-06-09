#include "pch.h"

#include "mtp.h"
#include "PortableDeviceObjectJ.h"
#include "PortableDevice.h"

#include <PortableDevice.h>

JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32_getPropertiesN(JNIEnv* env, jobject cls, jstring idJava)
{
	LPWSTR id;
	id = (WCHAR*) env->GetStringChars(idJava, nullptr);
	return keyAndValues(env, id);
}

JNIEXPORT jboolean JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32_isContainerN(JNIEnv* env, jobject cls, jstring idJava)
{
	
	LPWSTR id;

	IPortableDeviceProperties* p;
	IPortableDeviceKeyCollection* pCol;
	IPortableDeviceValues* pValues;

	p = getPDProperties();
	pCol = getKeyCollection();

	GUID type;

	id = (WCHAR*)env->GetStringChars(idJava, nullptr);

	pCol->Add(WPD_OBJECT_CONTENT_TYPE);
	pCol->Add(WPD_FUNCTIONAL_OBJECT_CATEGORY);
	p->GetValues(id, pCol, &pValues);
	pValues->GetGuidValue(WPD_OBJECT_CONTENT_TYPE, &type);
	if (type == WPD_CONTENT_TYPE_FOLDER)
		return true;
	if (type == WPD_CONTENT_TYPE_FUNCTIONAL_OBJECT) {
		GUID functionalObject;
		pValues->GetGuidValue(WPD_FUNCTIONAL_OBJECT_CATEGORY, &functionalObject);
		if (functionalObject == WPD_FUNCTIONAL_CATEGORY_STORAGE)
			return true;
		return false;
	}
	return false;
}


jobject keyAndValues(JNIEnv* env, LPWSTR id) {

	HRESULT hr;
	IPortableDeviceProperties* p;
	IPortableDeviceKeyCollection* coll = {};

	p = getPDProperties();

	hr = p->GetSupportedProperties(id, &coll);
	if (FAILED(hr)) {
		if (hr == 0x80042009) { // Object does not exist
			jclass generalPortableDeviceException = env->FindClass("com/github/hms11rn/mtp/PortableDeviceException");
			env->ThrowNew(generalPortableDeviceException, "Specified Object could not be found (Was it deleted)?");
			return nullptr;
		}
		else if (hr == E_POINTER || hr == E_WPD_DEVICE_NOT_OPEN) { // both can indicate device closed
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
	jobject keyAndValuesJava = GetKeyAndValuesMap(env, coll, deviceValues);
	coll->Release();
	deviceValues->Release();
	return keyAndValuesJava;
}