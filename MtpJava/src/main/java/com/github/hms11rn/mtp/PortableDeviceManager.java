package com.github.hms11rn.mtp;

import com.github.hms11rn.mtp.win32.MtpWin32;

public interface PortableDeviceManager {

    PortableDevice[] getDevices();
    int getDeviceCount();

    String[] getDeviceID();

    static PortableDeviceManager getDeviceManager() {
        // if windows...
        return MtpWin32.getWin32Manager();
    }
}
