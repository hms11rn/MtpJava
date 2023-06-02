package com.github.hms11rn.mtp;

import com.github.hms11rn.mtp.win32.MtpWin32;

public interface PortableDeviceManager {

    /**
     * @return array of all Portable Devices
     */
    PortableDevice[] getDevices();

    /**
     * Returns how many Portable Devices are connected without initializing any PortableDevice objects
     * @return Portable Device count
     */
    int getDeviceCount();

    /**
     * @return array of unique hardware IDs for each device
     */
    String[] getDeviceIDs();

    void refresh();

    /**
     * Get the Device Manager of current OS (As of now Supports only Windows)
     * @return Device Manager of current OS
     */
    static PortableDeviceManager getDeviceManager() {
        // if windows...
        return MtpWin32.getWin32Manager();
    }
}
