#include "pch.h"

#include <iostream>
#include "PortableDeviceManager.h"

using namespace std;

IPortableDeviceManager* pDeviceManager = nullptr;

IPortableDeviceManager* getDeviceManager()
{
    HRESULT hr = InitializeDeviceManager();
    if (FAILED(hr)) {
        cout << "Failed to initialize device manager" << endl;
    }
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
    DWORD pnp_device_id_count = 0;
    HRESULT hr = getDeviceManager()->GetDevices(nullptr, &pnp_device_id_count);

       if (FAILED(hr)) {
            std::cout << "! Failed to get number of devices on the system, hr = " << std::hex << hr << std::endl;
            return 0;
       }
    

    // Uninitialize
    return pnp_device_id_count;
}

 jobjectArray getDeviceHWID(JNIEnv *env) {     
     jobjectArray deviceNames;
     DWORD size;

     HRESULT hr = getDeviceManager()->GetDevices(nullptr, &size);
     if (FAILED(hr)) {
         std::cout << "hr2 failed, hr = " << std::hex << hr << std::endl;
         return nullptr;
     }
     LPWSTR* deviceIDs = new LPWSTR[size];
     hr = getDeviceManager()->GetDevices(deviceIDs, &size);
     if (FAILED(hr)) {
         std::cout << "hr2 failed, hr = " << std::hex << hr << std::endl;
         return nullptr;
     }

     if (SUCCEEDED(hr)) {
         deviceNames = env->NewObjectArray(size, env->FindClass("java/lang/String"), NULL);
         for (DWORD i = 0; i < size; i++) {
              env->SetObjectArrayElement(deviceNames, i, env->NewString((jchar*)deviceIDs[i], wcslen(deviceIDs[i])));
              CoTaskMemFree(deviceIDs[i]);
         }
         delete[] deviceIDs;
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
