#include "pch.h"
#include "mtp.h"
#include "PortableDevice.h"

#include "PortableDeviceManager.h"
#include "PortableDeviceContentJ.h"
#include "PortableDeviceServiceManager.h"

#include <PortableDevice.h>
#include <iostream>

using namespace std;

jstring deviceID;
LPWSTR wsDeviceID;

IPortableDevice* pPortableDevice;
IPortableDeviceProperties* pProperties;

IPortableDeviceValues* pClientValues;
IPortableDeviceKeyCollection* pKeyCollection;
IPortableDevicePropVariantCollection* propVariantCollections;
IPortableDeviceService* pService;
IPortableDeviceContent2* pContent2;

PortableDeviceContentJ* content;


IPortableDeviceKeyCollection* getKeyCollection() {
    HRESULT hr;
    if (pKeyCollection == nullptr) {
        hr = CoCreateInstance
        (CLSID_PortableDeviceKeyCollection, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pKeyCollection));
        if (FAILED(hr)) {
            handleException("COM", "Failed to create IPortableDeviceServer", hr);
        }
    }
    return pKeyCollection;
}

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

IPortableDeviceProperties* getPortableDeviceProperties() {

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
    wszDeviceFriendlyName = new WCHAR[length];
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
    wszDeviceDescription = new WCHAR[length];
    hr = pDeviceManager->GetDeviceDescription(wszDeviceID, wszDeviceDescription, &length);

    description = env->NewString((jchar*)wszDeviceDescription, length);

    env->ReleaseStringChars(deviceID, (jchar*)wszDeviceID);
    delete[] wszDeviceDescription;

    return description;

}

JNIEXPORT jobject JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_getProperties
(JNIEnv* env, jclass, jstring objectID) {

    HRESULT hr;

    IPortableDeviceContent* pContent;
    IPortableDevice* pDevice;
    LPWSTR wsObjectID;
    wsObjectID = (WCHAR*) env->GetStringChars(objectID, nullptr);
    pDevice = getPortableDevice();
    pContent = content->getContent();
    hr = pContent->Properties(&pProperties);
    if (FAILED(hr)) {
        if (hr == E_WPD_DEVICE_NOT_OPEN || hr == E_POINTER) {
            jclass deviceClosedException = env->FindClass("com/github/hms11rn/mtp/DeviceClosedException");
            string devIdChar = env->GetStringUTFChars(getFriendlyName(env, deviceID), nullptr);
            env->ThrowNew(deviceClosedException, devIdChar.append(" is not opened. use PortableDevice#open() to open").c_str());
            
            return nullptr;
        }
        cout << "Failed to get device properties, hr = " << std::hex << hr << endl;
        return nullptr;
    }
    IPortableDeviceKeyCollection* deviceKeys{};
    hr = pProperties->GetSupportedProperties(wsObjectID, &deviceKeys);
    if (FAILED(hr)) {
        cout << "Failed to get supported properties of the device, hr = " << std::hex << hr << endl;
        return nullptr;
    }
    IPortableDeviceValues* deviceValues{};
    hr = pProperties->GetValues(wsObjectID, deviceKeys, &deviceValues);
    if (FAILED(hr)) {
        cout << "Failed to get device Property Values, hr = " << std::hex << hr << endl;
        return nullptr;
    }
    env->ReleaseStringChars(objectID, (jchar*)wsObjectID);
    jobject map = GetKeyAndValuesMap(env, deviceKeys, deviceValues);
    deviceKeys->Release();
    deviceValues->Release();
    return map;
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
        }
        if (SUCCEEDED(hr)) {
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
    
    hr = OpenDevice(wszDeviceID, &pDevice, L"Unknown-MtpLibJava", 1, 0, 0);
    if (FAILED(hr))
    {      
        handleException("DEVICE", "Failed to open Portable Device", hr);
        return;
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
    LPWSTR wszDeviceID;
    jfieldID deviceIdField;
    jstring jsDeviceID;

    deviceIdField = env->GetFieldID(env->GetObjectClass(obj), "deviceID", "Ljava/lang/String;");
    jsDeviceID = (jstring)env->GetObjectField(obj, deviceIdField);
    wszDeviceID = (WCHAR*)env->GetStringChars(jsDeviceID, nullptr);
    pPortableDevice->Close();
    pPortableDevice->Release();
    pPortableDevice = nullptr;

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
    if (pClientValues != nullptr)
    {
        pClientValues->Release();
        pClientValues = nullptr;
    }
    if (pKeyCollection != nullptr) {
        pKeyCollection->Release();
        pKeyCollection = nullptr;
    }
    if (pProperties != nullptr) {
        pProperties->Release();
        pProperties = nullptr;
    }
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

    jstring returnID;

    wszParent = (WCHAR*)env->GetStringChars(parent, nullptr);

    returnID = content->addObjectFromFile(env, wszParent, name, file, type, format, &hr);

    if (hr == E_POINTER || hr == E_WPD_DEVICE_NOT_OPEN) {
        jfieldID fid = env->GetFieldID(env->GetObjectClass(cls), "deviceID", "Ljava/lang/String;");
        jstring jsDeviceID = (jstring)env->GetObjectField(cls, fid);
        jclass deviceClosedException = env->FindClass("com/github/hms11rn/mtp/DeviceClosedException");
        jstring friendlyName = getFriendlyName(env, jsDeviceID);
        string devIdChar = env->GetStringUTFChars(friendlyName, nullptr);
        env->ThrowNew(deviceClosedException, devIdChar.append(" is not opened. use PortableDevice#open() to open").c_str());
        env->DeleteLocalRef(jsDeviceID);
    }

    if (returnID == nullptr) {
        return env->NewStringUTF("");
    }

    env->ReleaseStringChars(parent, (jchar*)wszParent);
    return returnID;
}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFileFromInputStreamN(JNIEnv* env, jobject, jstring name, jstring parent, jobject inputStream, jstring type, jstring format)
{
    LPWSTR wszName;
    LPWSTR wszParent;
    LPWSTR wszType;
    LPWSTR wszFormat;

    jstring returnID;

    wszName = (WCHAR*)env->GetStringChars(name, nullptr);
    wszParent = (WCHAR*)env->GetStringChars(parent, nullptr);
    wszType = (WCHAR*)env->GetStringChars(type, nullptr);
    wszFormat = (WCHAR*)env->GetStringChars(format, nullptr);

    returnID = content->addObjectFromInputStream(env, wszParent, wszName, inputStream, wszType, wszFormat);

    env->ReleaseStringChars(name, (jchar*)wszName);
    env->ReleaseStringChars(parent, (jchar*)wszParent);
    env->ReleaseStringChars(type, (jchar*)wszType);
    env->ReleaseStringChars(format, (jchar*)wszFormat);
    return returnID;
}

JNIEXPORT jstring JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceWin32_addFolderObjectN(JNIEnv* env, jobject, jstring name, jstring parent)
{
    LPWSTR wszParent;
    LPWSTR wszName;

    jstring returnID;

    wszParent = (WCHAR*)env->GetStringChars(parent, nullptr);
    wszName = (WCHAR*)env->GetStringChars(name, nullptr);

    returnID = content->addFolderObject(env, wszName, wszParent);

    if (returnID == nullptr)
        return env->NewStringUTF(""); // Avoid crash
    env->ReleaseStringChars(parent, (jchar*)wszParent);
    env->ReleaseStringChars(name, (jchar*)wszName);
    return returnID;
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
    return success;
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
