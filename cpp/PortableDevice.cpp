#include "pch.h"
#include "PortableDevice.h"
#include "PortableDeviceManager.h"
#include "PortableDeviceContentJ.h"

#include "PortableDeviceServiceManager.h"
#include <PortableDeviceApi.h>
#include <PortableDevice.h>
#include <iostream>
#include <string>
#include "mtp.h"

using namespace std;

jstring deviceID;
LPWSTR wsDeviceID;

IPortableDeviceProperties* pProperties;

BOOL isOpen = false;
IPortableDevice* pPortableDevice;
IPortableDeviceValues* pClientValues;
IPortableDevicePropVariantCollection* propVariantCollections = nullptr;
//
PortableDeviceContentJ* content;
IPortableDeviceService* pService; // future
IPortableDeviceContent2* pContent2; // future

IPortableDeviceService* getService() {
    HRESULT hr;
    if (pService == nullptr) {
        hr = CoCreateInstance
        (CLSID_PortableDeviceService, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pService));
        if (FAILED(hr)) {
            handleException("COM", "Failed to create IPortableDeviceServer", hr);
        }
    }
    return pService;
}
IPortableDeviceContent2* getContent2() {

    HRESULT hr;

    LPWSTR* wsPnPServiceID;
    DWORD servicesSize;

    IPortableDeviceService* service = getService();
    IPortableDeviceValues* pClientInformation = getPortableDeviceValues();

    pClientInformation->SetStringValue(WPD_CLIENT_NAME, L"Mtp Java"); 
    pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_MAJOR_VERSION, 0);
    pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_MINOR_VERSION, 0);
    pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_REVISION, 1);
    hr = pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_SECURITY_QUALITY_OF_SERVICE, SECURITY_IMPERSONATION);
    
    wsPnPServiceID = getService(wsDeviceID, &servicesSize);
    if (servicesSize == 0)
        return nullptr;
    
    hr = service->Open(wsPnPServiceID[0], pClientInformation); // todo currently just first service
    if (FAILED(hr)) {
        cout << " ! Failed to open Device Services, HRESULT = " << std::hex << hr << endl;
        return nullptr;
    }
    hr = service->Content(&pContent2);
    if (FAILED(hr)) {
        cout << " ! Failed to get IPortableDeviceContent2, HRESULT = " << std::hex << hr << endl;
        return nullptr;
    }
    pClientInformation->Release();

    return pContent2;
}

IPortableDeviceProperties* getPDProperties() {

    return pProperties;
}

IPortableDevicePropVariantCollection* getPropVariantCollection() {
    if (propVariantCollections == nullptr) {
        HRESULT hr = CoCreateInstance(CLSID_PortableDevicePropVariantCollection, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&propVariantCollections));
        if (FAILED(hr)) {
            handleException("COM", "Failed to create IPortableDevicePropVariantCollection", hr);
        }
    }
    propVariantCollections->Clear();
    return propVariantCollections;
    
}
IPortableDeviceValues* getPortableDeviceValues()
{    
    HRESULT hr = S_OK;
    if (pClientValues == nullptr)
    {
        HRESULT hr = CoCreateInstance(CLSID_PortableDeviceValues,
            nullptr, CLSCTX_INPROC_SERVER, IID_IPortableDeviceValues, (VOID**)&pClientValues);
    }
    if (FAILED(hr)) {
        handleException("COM", "Failed to create IPortableDeviceValues", hr);
    }
    pClientValues->Clear();
    return pClientValues;
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
    HRESULT hr = S_OK;
    if (pPortableDevice == nullptr)
    {
        HRESULT hr = CoCreateInstance(CLSID_PortableDeviceFTM,
            nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableDevice));
    }
    if (FAILED(hr)) {
        handleException("COM", "Failed to create IPortableDevice", hr);
    }
    return pPortableDevice;
}


jstring getFriendlyName(JNIEnv* env, jstring deviceID) {
    IPortableDeviceManager* pDeviceManager;
    LPWSTR wszDeviceID;
    LPWSTR wszDeviceFriendlyName;
    DWORD length{};
    HRESULT hr;
    jstring friendlyName;

    pDeviceManager = getDeviceManager();
    wszDeviceID = (WCHAR*)env->GetStringChars(deviceID, NULL);

    pDeviceManager->GetDeviceFriendlyName(wszDeviceID, NULL, &length);
    wszDeviceFriendlyName = new WCHAR[length + 1];
    hr = pDeviceManager->GetDeviceFriendlyName(wszDeviceID, wszDeviceFriendlyName, &length);

    friendlyName = env->NewString((jchar*)wszDeviceFriendlyName, length);

    env->ReleaseStringChars(deviceID, (jchar*)wszDeviceID);
    delete[] wszDeviceFriendlyName;

    return friendlyName;
}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getFriendlyName
(JNIEnv* env, jclass, jstring deviceID) {
    return getFriendlyName(env, deviceID);
}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getManufacturer
(JNIEnv* env, jclass, jstring deviceID) {

    IPortableDeviceManager* pDeviceManager;
    LPWSTR wszDeviceID;
    LPWSTR wszDeviceManufacturer;
    DWORD length{};
    jstring manufacturer;

    pDeviceManager = getDeviceManager();
    wszDeviceID = (WCHAR*)env->GetStringChars(deviceID, nullptr);
    pDeviceManager->GetDeviceManufacturer(wszDeviceID, nullptr, &length);
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
    HRESULT hr;
    jstring description;

    pDeviceManager = getDeviceManager();
    wszDeviceID = (WCHAR*)env->GetStringChars(deviceID, nullptr);

    pDeviceManager->GetDeviceDescription(wszDeviceID, nullptr, &length);
    wszDeviceDescription = new WCHAR[length + 1];
    hr = pDeviceManager->GetDeviceDescription(wszDeviceID, wszDeviceDescription, &length);

    description = env->NewString((jchar*)wszDeviceDescription, length);

    env->ReleaseStringChars(deviceID, (jchar*)wszDeviceID);
    delete[] wszDeviceDescription;

    return description;

}

JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getProperties
(JNIEnv* env, jclass, jstring deviceID) {

    IPortableDeviceContent* pContent;
    LPWSTR wszDeviceID;
    HRESULT hr;
    IPortableDevice* pDevice;

    wszDeviceID = (WCHAR*)env->GetStringChars(deviceID, nullptr);
    pDevice = getPortableDevice();

    
   
    pContent = content->getContent();

    if (pProperties != nullptr) {
        pProperties->Release();
        pProperties = nullptr;
    }
  
    hr = pContent->Properties(&pProperties);
    if (FAILED(hr)) {
        if (FAILED(hr)) {
            if (hr == E_WPD_DEVICE_NOT_OPEN || hr == E_POINTER) {
                jclass deviceClosedException = env->FindClass("com/github/hms11rn/mtp/DeviceClosedException");
                string devIdChar = env->GetStringUTFChars(getFriendlyName(env, deviceID), nullptr);
                env->ThrowNew(deviceClosedException, devIdChar.append(" is not opened. use PortableDevice#open() to open").c_str());
            }
            return nullptr;
        }
        cout << "Failed to get device properties, hr = " << std::hex << hr << endl;
        return nullptr;
    }

    IPortableDeviceKeyCollection* deviceKeys{};
    hr = pProperties->GetSupportedProperties(WPD_DEVICE_OBJECT_ID, &deviceKeys);
    if (FAILED(hr)) {
        cout << "Failed to get supported properties of the device, hr = " << std::hex << hr << endl;
    }
    IPortableDeviceValues* deviceValues{};
    hr = pProperties->GetValues(WPD_DEVICE_OBJECT_ID, deviceKeys, &deviceValues);
    if (FAILED(hr)) {
        cout << "Failed to get device Property Values, hr = " << std::hex << hr << endl;
        pProperties->Release();
        return nullptr;
    }
    jobject map = GetKeyAndValuesMap(env, deviceKeys, deviceValues);
    deviceKeys->Release();
    deviceValues->Release();
    return map;
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

HRESULT OpenDevice(LPCWSTR wszPnPDeviceID, IPortableDevice** ppDevice, LPCWSTR clientName, int majorV, int minorV, int clientRevision)
{
    HRESULT                hr = S_OK;
    IPortableDeviceValues* pClientInformation = nullptr;
    IPortableDevice* pDevice = nullptr;

    if ((wszPnPDeviceID == nullptr) || (ppDevice == nullptr))
    {
        hr = E_INVALIDARG;
        return hr;
    }

    pClientInformation = getPortableDeviceValues();
        HRESULT ClientInfoHR = S_OK;

        ClientInfoHR = pClientInformation->SetStringValue(WPD_CLIENT_NAME, clientName);
        if (FAILED(ClientInfoHR))
        {
            cout << "Failed to set WPD_CLIENT_NAME" << endl;
        }

        ClientInfoHR = pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_MAJOR_VERSION, majorV);
        if (FAILED(ClientInfoHR))
        {
            cout << "Failed to set WPD_CLIENT_MAJOR_VERSION" << endl;
        }

        ClientInfoHR = pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_MINOR_VERSION, minorV);
        if (FAILED(ClientInfoHR))
        {
            cout << "Failed to set WPD_CLIENT_MINOR_VERSION" << endl;
        }

        ClientInfoHR = pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_REVISION, clientRevision);
        if (FAILED(ClientInfoHR))
        {
            cout << "Failed to set WPD_CLIENT_REVISION" << endl;
        }

    ClientInfoHR = pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_SECURITY_QUALITY_OF_SERVICE, SECURITY_IMPERSONATION);
    if (FAILED(ClientInfoHR))
    {
        cout << "Failed to set WPD_CLIENT_SECURITY_QUALITY_OF_SERVICE" << endl;
    }

    if (SUCCEEDED(hr))
    {
        pDevice = getPortableDevice();      
        hr = pDevice->Open(wszPnPDeviceID, pClientInformation);
        if (hr == E_ACCESSDENIED)
        {
            cerr << "Failed to open Device in Read and Write, attempting to open in read only" << endl;
            // Attempt to open for read-only access
            pClientInformation->SetUnsignedIntegerValue(
                WPD_CLIENT_DESIRED_ACCESS,
                GENERIC_READ);
            hr = pDevice->Open(wszPnPDeviceID, pClientInformation);
            isOpen = true;
        }
        if (SUCCEEDED(hr)) {
            isOpen = true;                 
        }
        else
        {
            cerr << "Failed to open portable device" << endl;
        }
    }

    return hr;
}
JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_openN
(JNIEnv* env, jobject obj) {
    HRESULT hr;

    IPortableDevice* pDevice;
    IPortableDeviceContent* pContent;

    LPWSTR wszDeviceID;

    jfieldID fid;
    jstring jsDeviceID;

    pDevice = getPortableDevice();
    fid = env->GetFieldID(env->GetObjectClass(obj), "deviceID", "Ljava/lang/String;");
    jsDeviceID = (jstring)env->GetObjectField(obj, fid);
    wszDeviceID = (WCHAR*)env->GetStringChars(jsDeviceID, NULL);

    wsDeviceID = wszDeviceID;
    if (isOpen) {
        env->ReleaseStringChars(jsDeviceID, (jchar*)wszDeviceID);
        return;
    }
    hr = OpenDevice(wszDeviceID, &pDevice, L"Unknown-MtpLibJava", 1, 0, 0);
    if (FAILED(hr))
    {      
        handleException("DEVICE", "Failed to open Portable Device", hr);
    }
    wcout << L"WPD: Opened Device: " << wszDeviceID << L" , Attempting to create and open Service" << endl;
    hr = pDevice->Content(&pContent);
    if (FAILED(hr)) {
        if (hr == E_WPD_DEVICE_NOT_OPEN || hr == E_POINTER) {
            jclass deviceClosedException = env->FindClass("com/github/hms11rn/mtp/DeviceClosedException");
            string devIdChar = env->GetStringUTFChars(getFriendlyName(env, deviceID), nullptr);
            env->ThrowNew(deviceClosedException, devIdChar.append(" is not opened. use PortableDevice#open() to open").c_str());
        }
    }
    content = new PortableDeviceContentJ(pContent);
    
    env->ReleaseStringChars(jsDeviceID, (jchar*)wszDeviceID);;
}

JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_closeN
(JNIEnv* env, jobject obj) {
    IPortableDevice* pDevice;
    LPWSTR wszDeviceID;
    jfieldID deviceIdField;
    jstring jsDeviceID;

    pDevice = getPortableDevice();
    deviceIdField = env->GetFieldID(env->GetObjectClass(obj), "deviceID", "Ljava/lang/String;");
    jsDeviceID = (jstring)env->GetObjectField(obj, deviceIdField);
    wszDeviceID = (WCHAR*)env->GetStringChars(jsDeviceID, nullptr);
    pDevice->Close();
    pDevice->Release();
    pDevice = nullptr;
    if (pClientValues != nullptr) {
        pClientValues->Release();
        pClientValues = nullptr;
    }
    if (propVariantCollections != nullptr) {
        propVariantCollections->Release();
        propVariantCollections = nullptr;
    }
    if (content != nullptr) {
        content->release();
        delete content;
        content = nullptr;
    }
    if (pService != nullptr) {
        pService->Release();
        pService = nullptr;
    }
    if (pContent2 != nullptr) {
        pContent2->Release();
        pContent2 = nullptr;
    }
    isOpen = false;
    env->ReleaseStringChars(jsDeviceID, (jchar*)wszDeviceID);
}

JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getObjectsN
(JNIEnv* env, jobject cls, jstring objIdJava) {

    return content->getObjects(env, cls, objIdJava);

}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFileObjectN
(JNIEnv* env, jobject cls, jstring name, jstring parent, jobject file, jstring type, jstring format) {
    HRESULT hr = S_OK;
    LPWSTR wszParent;

    wszParent = (WCHAR*)env->GetStringChars(parent, nullptr);

    jstring s = content->addObjectFromFile(env, wszParent, name, file, type, format, &hr);

    if (hr == E_POINTER || hr == E_WPD_DEVICE_NOT_OPEN) {
        jfieldID fid = env->GetFieldID(env->GetObjectClass(cls), "deviceID", "Ljava/lang/String;");
        jstring jsDeviceID = (jstring)env->GetObjectField(cls, fid);
        jclass deviceClosedException = env->FindClass("com/github/hms11rn/mtp/DeviceClosedException");
        jstring friendlyName = getFriendlyName(env, jsDeviceID);
        string devIdChar = env->GetStringUTFChars(friendlyName, nullptr);
        env->ThrowNew(deviceClosedException, devIdChar.append(" is not opened. use PortableDevice#open() to open").c_str());
        env->DeleteLocalRef(jsDeviceID);
    }

    if (s == nullptr) {
        return env->NewStringUTF("");
    }

    env->ReleaseStringChars(parent, (jchar*)wszParent);
    return s;
}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFileFromInputStreamN(JNIEnv* env, jobject, jstring name, jstring parent, jobject inputStream, jstring type, jstring format)
{
    LPWSTR wszName;
    LPWSTR wszParent;
    LPWSTR wszType;
    LPWSTR wszFormat;

    wszName = (WCHAR*)env->GetStringChars(name, nullptr);
    wszParent = (WCHAR*)env->GetStringChars(parent, nullptr);
    wszType = (WCHAR*)env->GetStringChars(type, nullptr);
    wszFormat = (WCHAR*)env->GetStringChars(format, nullptr);

    jstring s = content->addObjectFromInputStream(env, wszParent, wszName, inputStream, wszType, wszFormat);

    env->ReleaseStringChars(name, (jchar*)wszName);
    env->ReleaseStringChars(parent, (jchar*)wszParent);
    env->ReleaseStringChars(type, (jchar*)wszType);
    env->ReleaseStringChars(format, (jchar*)wszFormat);
    return s;
}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFolderObjectN(JNIEnv* env, jobject, jstring name, jstring parent)
{
    LPWSTR wszParent;
    LPWSTR wszName;

    wszParent = (WCHAR*)env->GetStringChars(parent, nullptr);
    wszName = (WCHAR*)env->GetStringChars(name, nullptr);

    jstring s = content->addFolderObject(env, wszName, wszParent);

    if (s == nullptr)
        return env->NewStringUTF("");
    env->ReleaseStringChars(parent, (jchar*)wszParent);
    env->ReleaseStringChars(name, (jchar*)wszName);
    return s;
}

JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_copyFileN(JNIEnv* env, jobject, jstring id, jstring path)
{
    LPWSTR wszObjectID;
    LPWSTR wszPath;

    wszObjectID = (WCHAR*)env->GetStringChars(id, nullptr);
    wszPath = (WCHAR*)env->GetStringChars(path, nullptr);
    content->copyObjectToFile(env, wszObjectID, wszPath);
    env->ReleaseStringChars(id, (jchar*)wszObjectID);
    env->ReleaseStringChars(path, (jchar*)wszPath);

}

                                                                  
JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_updatePropertyN(JNIEnv* env, jobject, jstring id, jstring fmtid, jint pid, jint varType, jstring value)
{
    LPWSTR wszObjectID;
    LPWSTR wszGuid;
    LPWSTR wszValue;

    GUID guid;
    wszObjectID = (WCHAR*)env->GetStringChars(id, nullptr);
    wszGuid = (WCHAR*)env->GetStringChars(fmtid, nullptr);
    wszValue = (WCHAR*)env->GetStringChars(value, nullptr);
    CLSIDFromString(wszGuid, &guid);
    content->updateProperty(env, wszObjectID, guid, pid, varType, wszValue);
    env->ReleaseStringChars(id, (jchar*)wszObjectID);
    env->ReleaseStringChars(fmtid, (jchar*)wszGuid);
    env->ReleaseStringChars(value, (jchar*)wszValue);

}

    
JNIEXPORT jboolean JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_deleteFileN(JNIEnv* env, jobject, jstring id, jint recursion)
{
    LPWSTR wszObjectID;
    wszObjectID = (WCHAR*)env->GetStringChars(id, nullptr);
    BOOL success = content->deleteFile(wszObjectID, recursion);
    env->ReleaseStringChars(id, (jchar*) wszObjectID);
    return 0;
}

JNIEXPORT jbyteArray JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getBytesN(JNIEnv* env, jobject, jstring id) {
    LPWSTR wszObjectID;
    wszObjectID = (WCHAR*)env->GetStringChars(id, nullptr);
    
    BYTE* b = nullptr;
    b = content->getBytes(env, wszObjectID, nullptr);

    jbyteArray bArr = env->NewByteArray(sizeof(b));
    env->SetByteArrayRegion(bArr, 0, sizeof(b), (jbyte*)b);

    env->ReleaseStringChars(id, (jchar*)wszObjectID);

    return bArr;
}

JNIEXPORT jint JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceOutputStreamWin32_writeBuffer(JNIEnv* env, jobject, jstring id, jbyteArray buffer, jint bufferSize, jboolean append, jboolean rewrite)
{
    LPWSTR wszObjectID;
    wszObjectID = (WCHAR*)env->GetStringChars(id, nullptr);

    jbyte* elements = env->GetByteArrayElements(buffer, nullptr);
    DWORD bytesWritten = content->writeBytes(env, wszObjectID, (BYTE*) elements, bufferSize, append, rewrite);
    env->ReleaseStringChars(id, (jchar*)wszObjectID);
    return bytesWritten;
}
