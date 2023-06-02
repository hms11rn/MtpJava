#include "pch.h"
#include "mtp.h"

#include "PortableDeviceManager.h"

IPortableDeviceManager* pDeviceManager;

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
    CoUninitialize();

}

 int getDeviceCount() {

    HRESULT hr;
    DWORD deviceCount = 0;

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

    return deviceCount;
}

 jobjectArray getDeviceHWID(JNIEnv *env) {     
     HRESULT hr;
     DWORD size = 0;

     IPortableDeviceManager* pManager;

     jobjectArray deviceNames;
     LPWSTR* wszDeviceIDs;

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

     wszDeviceIDs = new LPWSTR[size];
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

 JNIEXPORT jobjectArray JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32_getDeviceIDs
 (JNIEnv* env)
 {

     return getDeviceHWID(env);
 }

 JNIEXPORT void JNICALL Java_com_github_hms11rn_mtp_win32_PortableDeviceManagerWin32_refresh
 (JNIEnv*) {
     IPortableDeviceManager* pManager;

     pManager = getDeviceManager();
     pManager->RefreshDeviceList();
 }