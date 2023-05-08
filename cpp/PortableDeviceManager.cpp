#include "pch.h"

#include "mtp.h"

#include <iostream>
#include "PortableDeviceManager.h"

using namespace std;

IPortableDeviceManager* pDeviceManager = nullptr;

HRESULT cHr = S_OK;
IPortableDeviceManager* getDeviceManager()
{
    HRESULT hr = InitializeDeviceManager();
    if (FAILED(hr)) {
        handleException("COM", "Failed to initialize device manager", hr);
        cHr = hr;
    }
    else
        cHr = S_OK;
    return pDeviceManager;
}

HRESULT InitializeDeviceManager()
{
    CoInitialize(nullptr);
    if (pDeviceManager == nullptr)
    {
        HRESULT hr = CoCreateInstance(CLSID_PortableDeviceManager,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&pDeviceManager));

        if (FAILED(hr))
        {
            return hr;
        }
    }

    return S_OK;
}

void ReleaseDeviceManager()
{
    if (pDeviceManager != nullptr) {
        pDeviceManager->Release();
        pDeviceManager = nullptr;
    }
}

 int getDeviceCount() {
    // obtain amount of devices
    DWORD deviceCount = 0;
    HRESULT hr;
    IPortableDeviceManager* pManager;


    pManager = getDeviceManager();

    if (FAILED(cHr)) {
        handleException("COM", "Failed to initialize device manager", cHr);
        return 0;
    }
    hr = pManager->GetDevices(nullptr, &deviceCount);
       if (FAILED(hr)) {
            handleException("DEVICE_MGR", "Failed to get the number of devices on the system", hr);
            return 0;
       } 
    // Uninitialize
    return deviceCount;
}

 jobjectArray getDeviceHWID(JNIEnv *env) {     
     jobjectArray deviceNames;
     DWORD size;
     HRESULT hr;
     IPortableDeviceManager* pManager;

     pManager = getDeviceManager();
     if (FAILED(cHr)) {
         handleException("COM", "Failed to initialize device manager", cHr);
         return nullptr;
     }
     hr = pManager->GetDevices(nullptr, &size);
     if (FAILED(hr)) {
         handleException("DEVICE_MGR", "Failed to get the number of devices on the system", hr);
         return nullptr;
     }
     LPWSTR* wszDeviceIDs = new LPWSTR[size];
     hr = getDeviceManager()->GetDevices(wszDeviceIDs, &size);
     if (FAILED(hr)) {
         handleException("DEVICE_MGR", "Failed to get the device IDs" , hr);
         return nullptr;
     }

     if (SUCCEEDED(hr)) {
         deviceNames = env->NewObjectArray(size, env->FindClass("java/lang/String"), NULL);
         for (DWORD i = 0; i < size; i++) {
              env->SetObjectArrayElement(deviceNames, i, env->NewString((jchar*)wszDeviceIDs[i], wcslen(wszDeviceIDs[i])));
              CoTaskMemFree(wszDeviceIDs[i]);
         }
         delete[] wszDeviceIDs;
         return deviceNames;
     }
   
     return nullptr;
 }
 JNIEXPORT jint JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32_getDeviceCount
 (JNIEnv* env)
 {  

     jint ji = getDeviceCount();
     return ji;
 }

 JNIEXPORT jobjectArray JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32_getDeviceID
 (JNIEnv* env)
 {

     return getDeviceHWID(env);
 }
