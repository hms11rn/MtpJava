package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.PortableDevice;
import com.github.hms11rn.mtp.PortableDeviceManager;

class PortableDeviceManagerWin32 implements PortableDeviceManager {
    @Override
    public PortableDevice[] getDevices() {
        String[] iDs = getDeviceID();
        PortableDevice[] devices = new PortableDevice[iDs.length];
        int i = 0;
        for (String deviceID : iDs) {
            devices[i] = new PortableDeviceWin32(deviceID);
            i++;
        }
        return devices;
    }

    @Override
    public native int getDeviceCount();

    @Override
    public native String[] getDeviceID();

    // TODO refresh device list
}
