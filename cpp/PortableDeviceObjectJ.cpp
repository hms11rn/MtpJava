#include "pch.h"
#include "mtp.h"
#include "PortableDeviceObjectJ.h"

#include "PortableDevice.h"

#include <PortableDevice.h>

JNIEXPORT jboolean JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceObjectWin32_isContainerN(JNIEnv* env, jobject cls, jstring idJava)
{
	LPWSTR id;

	IPortableDeviceProperties* p;
	IPortableDeviceKeyCollection* pCol;
	IPortableDeviceValues* pValues;

	p = getPortableDeviceProperties();
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
	}
	return false;
}
