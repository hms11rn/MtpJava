package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.Mtp;

public class MtpWin32 {

    private static boolean flag = false;
    public static PortableDeviceManagerWin32 getWin32Manager() {
        if (!flag) {
            System.loadLibrary("mtpjava");
            flag = true;
        }
        Mtp.registerJNI();
        return new PortableDeviceManagerWin32();
    }

    public static String getGuid(String name) {
        return PropertiesWin32.getGuid(name);
    }
}
