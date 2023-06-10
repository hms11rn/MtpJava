package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.Mtp;

public class MtpWin32 {
    private static PortableDeviceManagerWin32 manager;

    private static boolean flag = false;
    public static PortableDeviceManagerWin32 getWin32Manager() {
        if (!flag) {
            System.loadLibrary("mtpjava");
            flag = true;
        }
        if (manager == null) {
            Mtp.registerJNI();
            manager =  new PortableDeviceManagerWin32();
        }
        return manager;
    }

    public static String getGuid(String name) {
        return PropertiesWin32.getGuid(name);
    }
}
