#include "pch.h"
#include "PortableDevice.h"
#include "PortableDeviceManager.h"
#include "PortableDeviceContentJ.h"
#include <PortableDeviceApi.h>
#include <PortableDevice.h>
#include <iostream>
#include <string>
#include "mtp.h"

using namespace std;

IPortableDeviceProperties* pProperties;

BOOL isOpen = false;
IPortableDevice* pPortableDevice;
IPortableDeviceValues* pClientValues;
IPortableDevicePropVariantCollection* propVariantCollections = nullptr;
//
PortableDeviceContentJ* content;

IPortableDeviceKeyCollection* contentTypeKey;

IPortableDeviceKeyCollection* getContentTypeKey() {
    if (contentTypeKey == nullptr) {
        HRESULT hr = CoCreateInstance(CLSID_PortableDeviceKeyCollection, 0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&contentTypeKey));
        if (FAILED(hr)) {
            // handle error
        }
        contentTypeKey->Add(WPD_OBJECT_CONTENT_TYPE);
        contentTypeKey->Add(WPD_FUNCTIONAL_OBJECT_CATEGORY);
        return contentTypeKey;
    }
    return contentTypeKey;
}

IPortableDeviceProperties* getPDProperties() {

    return pProperties;
}

void initializePropVariantCollection() {
    if (propVariantCollections == nullptr) {
        HRESULT hr = CoCreateInstance(CLSID_PortableDevicePropVariantCollection, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&propVariantCollections));
        if (FAILED(hr)) {
            // handle error
        }
    }
}

IPortableDevicePropVariantCollection* getPropVariantCollection() {
    initializePropVariantCollection();
    return propVariantCollections;
}
IPortableDeviceValues* getPortableDeviceValues()
{
    HRESULT hr = InitializePortableDeviceValues();
    if (FAILED(hr)) {
        cout << "Failed to initialize device values" << endl;
    }

    return pClientValues;
}

HRESULT InitializePortableDeviceValues()
{
    if (pClientValues == nullptr)
    {
        HRESULT hr = CoCreateInstance(CLSID_PortableDeviceValues,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IPortableDeviceValues,
            (VOID**)&pClientValues);

        if (FAILED(hr)) {
            return hr;
        }
    }
    return S_OK;
}

void releasePortableDeviceValues() {
    if (pClientValues != nullptr)
    {
        pClientValues->Release();
        pClientValues = nullptr;
    }
}

IPortableDevice* getPortableDevice()
{
    HRESULT hr = InitializePortableDevice();
    if (FAILED(hr)) {
        cout << "Failed to initialize device manager" << endl;
    }
    return pPortableDevice;
}

HRESULT InitializePortableDevice()
{
    if (!SUCCEEDED(CoInitialize(nullptr))) {
        cout << "Failed to initialize" << endl;
    }
    if (pPortableDevice == nullptr)
    {
        HRESULT hr = CoCreateInstance(CLSID_PortableDeviceFTM,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&pPortableDevice));

        if (FAILED(hr)) {
            return hr;
        }
    }
    // initialize content

    return S_OK;
}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getFriendlyName
(JNIEnv* env, jclass, jstring deviceID) {
    IPortableDeviceManager *pDeviceManager;
    LPWSTR wszDeviceID;
    LPWSTR wszDeviceFriendlyName;
    DWORD length;
    jstring friendlyName;

    pDeviceManager = getDeviceManager();
    wszDeviceID = (WCHAR*)env->GetStringChars(deviceID, NULL);

    pDeviceManager->GetDeviceFriendlyName(wszDeviceID, NULL, &length);
    wszDeviceFriendlyName = new WCHAR[length + 1];
    HRESULT hr = pDeviceManager->GetDeviceFriendlyName(wszDeviceID, wszDeviceFriendlyName, &length);

    friendlyName = env->NewString((jchar*)wszDeviceFriendlyName, length);

    env->ReleaseStringChars(deviceID, (jchar*)wszDeviceID);
    delete[] wszDeviceFriendlyName;

    return friendlyName;
}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getManufacturer
(JNIEnv* env, jclass, jstring deviceID) {

    IPortableDeviceManager* pDeviceManager;
    LPWSTR wszDeviceID;
    PWSTR wszDeviceManufacturer;
    DWORD length{};
    jstring manufacturer;

    pDeviceManager = getDeviceManager();
    wszDeviceID = (WCHAR*)env->GetStringChars(deviceID, NULL);
    pDeviceManager->GetDeviceManufacturer(wszDeviceID, NULL, &length);
    if (length == 0) {
        return env->NewStringUTF("");
    }
    wszDeviceManufacturer = new WCHAR[length];
    pDeviceManager->GetDeviceManufacturer(wszDeviceID, wszDeviceManufacturer, &length);
    manufacturer = env->NewString((jchar*)wszDeviceManufacturer, length);

    env->ReleaseStringChars(deviceID, (jchar*)wszDeviceID);
    delete[] wszDeviceManufacturer;

    return manufacturer;
}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getDescription
(JNIEnv* env, jclass, jstring deviceID) {
    IPortableDeviceManager* pDeviceManager;
    LPWSTR wszDeviceID;
    LPWSTR wszDeviceDescription;
    DWORD length {};
    jstring description;

    pDeviceManager = getDeviceManager();
    wszDeviceID = (WCHAR*)env->GetStringChars(deviceID, NULL);

    pDeviceManager->GetDeviceDescription(wszDeviceID, NULL, &length);
    wszDeviceDescription = new WCHAR[length + 1];
    HRESULT hr = pDeviceManager->GetDeviceDescription(wszDeviceID, wszDeviceDescription, &length);

    description = env->NewString((jchar*)wszDeviceDescription, length);

    env->ReleaseStringChars(deviceID, (jchar*)wszDeviceID);
    delete[] wszDeviceDescription;

    return description;

}

JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getProperties
(JNIEnv* env, jclass, jstring deviceID) {
    IPortableDeviceContent* pContent;

    LPWSTR wszDeviceID;
    LPWSTR wszFirmwareVersion = NULL;
    DWORD dwFirmwareVersionLength{};
    PROPERTYKEY guidFirmwareVersion = WPD_DEVICE_FIRMWARE_VERSION;
    wszDeviceID = (WCHAR*)env->GetStringChars(deviceID, NULL);
    HRESULT hr;

    // Get the device manager
    IPortableDevice* pDevice = nullptr;
    pDevice = getPortableDevice();
    if (!isOpen) {
        hr = OpenDevice(wszDeviceID, &pDevice, L"Java Mtp Library", 1, 0, 0);
        if (FAILED(hr))
        {
            cout << "mtp:2 hr failed hr = " << hr << endl;
            // Handle error
            return nullptr;
        }
    }
    // Get the device properties
    hr = pDevice->Content(&pContent);
    if (FAILED(hr))
    {
        cout << "mtp:3 hr failed hr = " << hr << endl;
        // Handle error
        return nullptr;
    }

    PortableDeviceContentJ* content = new PortableDeviceContentJ(pContent, wszDeviceID);

    pProperties = nullptr;
    hr = pContent->Properties(&pProperties);
    if (FAILED(hr))
    {
        cout << "mtp:4 hr failed hr = " << hr << endl;
        // Handle error
        pContent->Release();
        return nullptr;
    }

    // Get the manufacturer property
    IPortableDeviceKeyCollection* deviceKeys{};
    hr = pProperties->GetSupportedProperties(WPD_DEVICE_OBJECT_ID, &deviceKeys);
    if (FAILED(hr)) {
        cout << "mtp:5 hr failed hr = " << hr << endl;
    }
    IPortableDeviceValues* deviceValues{};
    hr = pProperties->GetValues(WPD_DEVICE_OBJECT_ID, deviceKeys, &deviceValues);
    if (FAILED(hr)) {
        cout << "mtp:6 hr failed hr = " << hr << endl;
        // Handle error
        pProperties->Release();
        return nullptr;
    }
    jobject map = GetKeyAndValuesMap(env, deviceKeys, &deviceValues);
    pContent->Release();
    return map;
}

jobject GetKeyAndValuesMap(JNIEnv* env, IPortableDeviceKeyCollection* keys, IPortableDeviceValues** values) {
    jclass mapClass = env->FindClass("java/util/HashMap");
    if (mapClass == NULL) 
        return NULL;

    jmethodID init = env->GetMethodID(mapClass, "<init>", "()V");
    jobject hashMap = env->NewObject(mapClass, init);
    jmethodID put = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    DWORD size = 0;
    HRESULT hr = keys->GetCount(&size);


    for (int i = 0; i < size; i++) {
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
        // value of key
        PROPVARIANT valueAt;
        hr = (*values)->GetValue(keyName, &valueAt);
        // if value is array
        VARTYPE valueType = valueAt.vt;
        switch (valueType) {
        case VT_LPWSTR: {
            LPWSTR valueAtStr = nullptr;
            (*values)->GetStringValue(keyName, &valueAtStr);
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
            (*values)->GetBoolValue(keyName, &valueAtBool);
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
            (*values)->GetUnsignedIntegerValue(keyName, &valueAtInt);
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
            (*values)->GetUnsignedLargeIntegerValue(keyName, &valueAtInt);
            jobject longJava = ConvertUnsignedLongLongToJava(env, valueAtInt);
            env->CallObjectMethod(hashMap, put, keyJava, longJava);
            // free memory
            env->DeleteLocalRef(longJava);
            env->DeleteLocalRef(keyJava);
            break;
        }
        case VT_CLSID: {
            LPWSTR valueAtCLSID = nullptr;
            (*values)->GetStringValue(keyName, &valueAtCLSID);
            jstring singleValueJavaCLSID = env->NewString((jchar*)valueAtCLSID, wcslen(valueAtCLSID));
            // free memory
            CoTaskMemFree(valueAtCLSID);
            env->CallObjectMethod(hashMap, put, keyJava, singleValueJavaCLSID);
            env->DeleteLocalRef(singleValueJavaCLSID);
            env->DeleteLocalRef(keyJava);
            break;
        }
        
        case VT_ARRAY: {
            
            LPSAFEARRAY* arr = valueAt.pparray;
            SAFEARRAY* psa = reinterpret_cast<SAFEARRAY*>(arr);
            // Get a pointer to the array data
            long lowerBound, upperBound, count;
            SafeArrayGetLBound(psa, 1, &lowerBound);
            SafeArrayGetUBound(psa, 1, &upperBound);
            count = upperBound - lowerBound + 1;

            jobjectArray valueJavaArr = env->NewObjectArray(count, env->FindClass("java/lang/String"), nullptr);
            for (int i1 = 0; i1 < count; i1++) {
                LONG l = i1;
                LPWSTR valueAtt;
                SafeArrayGetElement(psa, &l, &valueAtt);
                if (SUCCEEDED(hr)) {
                    jstring singleValueJavaArr = env->NewString((jchar*)valueAtt, wcslen(valueAtt));
                    env->SetObjectArrayElement(valueJavaArr, i1, singleValueJavaArr);
                    env->DeleteLocalRef(singleValueJavaArr);
                    CoTaskMemFree(valueAtt);
                }
            }
            env->CallObjectMethod(hashMap, put, keyJava, valueJavaArr);
            env->DeleteLocalRef(keyJava);
            env->DeleteLocalRef(valueJavaArr);
            break;
        }                  
       }
      
    }

    jobject hashMapGobal = static_cast<jobject>(env->NewGlobalRef(hashMap));
    env->DeleteLocalRef(hashMap);
    env->DeleteLocalRef(mapClass);
    return hashMapGobal;
}
/*
      wstring ws(wszDeviceID);
    string myVarS = string(ws.begin(), ws.end());
    cout << myVarS << endl;
*/

HRESULT OpenDevice(LPCWSTR wszPnPDeviceID, IPortableDevice** ppDevice, LPCWSTR clientName, int majorV, int minorV, int clientRevision)
{
    HRESULT                hr = S_OK;
    IPortableDeviceValues* pClientInformation = NULL;
    IPortableDevice* pDevice = NULL;

    if ((wszPnPDeviceID == NULL) || (ppDevice == NULL))
    {
        hr = E_INVALIDARG;
        return hr;
    }

    // CoCreate an IPortableDeviceValues interface to hold the client information.
    pClientInformation = getPortableDeviceValues();
        HRESULT ClientInfoHR = S_OK;

        // Attempt to set all properties for client information. If we fail to set
        // any of the properties below it is OK. Failing to set a property in the
        // client information isn't a fatal error.
        ClientInfoHR = pClientInformation->SetStringValue(WPD_CLIENT_NAME, clientName);
        if (FAILED(ClientInfoHR))
        {
            cout << "here3" << endl;
            // Failed to set WPD_CLIENT_NAME
        }

        ClientInfoHR = pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_MAJOR_VERSION, majorV);
        if (FAILED(ClientInfoHR))
        {
            cout << "here4" << endl;
            // Failed to set WPD_CLIENT_MAJOR_VERSION
        }

        ClientInfoHR = pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_MINOR_VERSION, minorV);
        if (FAILED(ClientInfoHR))
        {
            cout << "here5" << endl;
            // Failed to set WPD_CLIENT_MINOR_VERSION
        }

        ClientInfoHR = pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_REVISION, clientRevision);
        if (FAILED(ClientInfoHR))
        {
            cout << "here6" << endl;
            // Failed to set WPD_CLIENT_REVISION
        }

    ClientInfoHR = pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_SECURITY_QUALITY_OF_SERVICE, SECURITY_IMPERSONATION);
    if (FAILED(ClientInfoHR))
    {
        // Failed to set WPD_CLIENT_SECURITY_QUALITY_OF_SERVICE
    }

    if (SUCCEEDED(hr))
    {
        // CoCreate an IPortableDevice interface
        pDevice = getPortableDevice();
        
            // Attempt to open the device using the PnPDeviceID string given
            // to this function and the newly created client information.
            // Note that we're attempting to open the device the first 
            // time using the default (read/write) access. If this fails
            // with E_ACCESSDENIED, we'll attempt to open a second time
            // with read-only access.
            hr = pDevice->Open(wszPnPDeviceID, pClientInformation);
            if (hr == E_ACCESSDENIED)
            {
                // Attempt to open for read-only access
                pClientInformation->SetUnsignedIntegerValue(
                    WPD_CLIENT_DESIRED_ACCESS,
                    GENERIC_READ);
                hr = pDevice->Open(wszPnPDeviceID, pClientInformation);
                isOpen = true;
            }
            if (SUCCEEDED(hr))
            {
                // The device successfully opened, obtain an instance of the Device into
                // ppDevice so the caller can be returned an opened IPortableDevice.
                hr = pDevice->QueryInterface(IID_IPortableDevice, (VOID**)ppDevice);
                isOpen = true;
                if (FAILED(hr))
                {
                    // Failed to QueryInterface the opened IPortableDevice
                }         
        }
        else
        {
            // Failed to CoCreateInstance CLSID_PortableDevice
        }
    }

    // Release the IPortableDeviceValues that contains the client information when finished
    if (pClientInformation != NULL)
    {
    }

    return hr;
}
JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_openN
(JNIEnv* env, jobject obj) {
    HRESULT hr;
    IPortableDevice* pDevice;
    LPWSTR wszDeviceID;
    jfieldID fid;
    jstring jsDeviceID;
    releasePortableDeviceValues();
    pDevice = getPortableDevice();
    fid = env->GetFieldID(env->GetObjectClass(obj), "deviceID", "Ljava/lang/String;");
    jsDeviceID = (jstring)env->GetObjectField(obj, fid);
    wszDeviceID = (WCHAR*)env->GetStringChars(jsDeviceID, NULL);
    if (isOpen) {
        return;
    }
    hr = OpenDevice(wszDeviceID, &pDevice, L"Unknown-MtpLibJava", 1, 0, 0);
    if (FAILED(hr))
    {
        cout << "couldnt open device" << endl;
    }
}

JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_closeN
(JNIEnv* env, jobject obj) {
    IPortableDevice* pDevice;
    LPWSTR wszDeviceID;
    jfieldID fid;
    jstring jsDeviceID;

    pDevice = getPortableDevice();
    fid = env->GetFieldID(env->GetObjectClass(obj), "deviceID", "Ljava/lang/String;");
    jsDeviceID = (jstring)env->GetObjectField(obj, fid);
    wszDeviceID = (WCHAR*)env->GetStringChars(jsDeviceID, NULL);
    pDevice->Close();
    isOpen = false;
   
}

JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getRootObjectsN
(JNIEnv* env, jobject cls) {
    IPortableDeviceContent* pContent;

    // prop variant collections of ids
    IPortableDevicePropVariantCollection* pPropCollections;

    // device id
    jfieldID deviceIDField;
    // java device id
    jstring jdeviceID;
    // wide string device id
    LPWSTR wszDeviceID;
    // portable device object stuff
    IPortableDevice* pDevice;
    pDevice = getPortableDevice();

    jclass mapClass = env->FindClass("java/util/HashMap");
    jmethodID init = env->GetMethodID(mapClass, "<init>", "()V");
    jobject hashMap = env->NewObject(mapClass, init);
    jmethodID put = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    // initalize device id
    deviceIDField = env->GetFieldID(env->GetObjectClass(cls), "deviceID", "Ljava/lang/String;");
    jdeviceID = (jstring)env->GetObjectField(cls, deviceIDField);
    wszDeviceID = (WCHAR*)env->GetStringChars(jdeviceID, nullptr);

    // initalaize prop variant collections

            //jobject portableDeviceObject = env->NewObject(portableObjectClass, init);
    
    // get root objects
    HRESULT hr = pDevice->Content(&pContent);
    if (FAILED(hr)) {
        cout << "pDevice->Content failed: " << hr << endl;
        // Handle the error
        return nullptr;
    }
    
    IEnumPortableDeviceObjectIDs* pEnum = nullptr;
    hr = pContent->EnumObjects(0, WPD_DEVICE_OBJECT_ID, nullptr, &pEnum);
    if (FAILED(hr)) {
        cout << "pDeviceContent->EnumObjects failed: " << hr << endl;
        // Handle the error        pContent->Release();
        return nullptr;
    }
    DWORD dwFetched = 0;
    LPWSTR szObjectID = nullptr;
    jobjectArray strarr = env->NewObjectArray(1, env->FindClass("com/github/hms11rn/mtp/win32/PortableDeviceObjectWin32"), nullptr);
    while (SUCCEEDED(pEnum->Next(1, &szObjectID, &dwFetched)) && (dwFetched > 0)) {
        IPortableDeviceValues* contentTypeValue;
        pProperties->GetValues(szObjectID, getContentTypeKey(), &contentTypeValue);
        GUID contentType;
        contentTypeValue->GetGuidValue(WPD_OBJECT_CONTENT_TYPE, &contentType);
        jstring contentTypeJava = env->NewStringUTF("UNKNOWN");
        if (contentType == WPD_CONTENT_TYPE_FOLDER) {
            contentTypeJava = env->NewStringUTF("CONTENT_TYPE_FOLDER");
        }
        else if (contentType == WPD_CONTENT_TYPE_FUNCTIONAL_OBJECT) {
            contentTypeJava = env->NewStringUTF("CONTENT_TYPE_FUNCTIONAL_OBJECT");
            GUID functionalType;
            contentTypeValue->GetGuidValue(WPD_FUNCTIONAL_OBJECT_CATEGORY, &functionalType);
            if (functionalType == WPD_FUNCTIONAL_CATEGORY_STORAGE) {
                contentTypeJava = env->NewStringUTF("WPD_FUNCTIONAL_CATERGORY_STORAGE");
            }
            else {
                contentTypeJava = env->NewStringUTF("CONTENT_TYPE_FILE");
            }
        }
        else {
            contentTypeJava = env->NewStringUTF("CONTENT_TYPE_FILE");
        }

        jstring idJava = env->NewString((jchar*)szObjectID, wcslen(szObjectID));
        env->CallObjectMethod(hashMap, put, idJava, contentTypeJava);
        
        env->SetObjectArrayElement(strarr, 0, content->getObject(szObjectID, env));
        CoTaskMemFree(szObjectID);
        szObjectID = nullptr;
    }
    pEnum->Release();
    return hashMap;
}

/*
 PROPVARIANT varPUIID = {};
        PropVariantInit(&varPUIID);
        varPUIID.vt = VT_LPWSTR;
        varPUIID.pwszVal = id;
        pPropCollections->Add(&varPUIID);

*/
