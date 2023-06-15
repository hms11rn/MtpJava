#include "pch.h"
#include "PortableDeviceServiceManager.h"

#include "PortableDeviceManager.h"
#include <iostream>
#include <PortableDevice.h>

using namespace std;

IPortableDeviceServiceManager* pSManager;

IPortableDeviceServiceManager* getSManager() {
	if (pSManager == nullptr) {
		HRESULT hr;
        IPortableDeviceManager* pManager;
        pManager = getDeviceManager();
        hr = pManager->QueryInterface(IID_IPortableDeviceServiceManager, (VOID**) &pSManager);
    }
    return pSManager;
}

LPWSTR* getService(LPWSTR wsDeviceID, DWORD* services) {
    HRESULT hr;
    IPortableDeviceServiceManager* pManager;
    IPortableDeviceService* pService;
    LPWSTR* pServices = nullptr; 
    DWORD max = 0;
    pManager = getSManager();

    hr = pManager->GetDeviceServices(wsDeviceID, GUID_DEVINTERFACE_WPD_SERVICE, nullptr, &max);
    if (FAILED(hr)) {
        cout << "Failed to get device services (IPortableDeviceServiceManager::GetDeviceServices), HRESULT = " << std::hex << hr << endl;
        return nullptr;
    }
    (*services) = max;
    pServices = new LPWSTR[max];
    hr = pManager->GetDeviceServices(wsDeviceID, GUID_DEVINTERFACE_WPD_SERVICE, pServices, &max);

    return pServices;
}