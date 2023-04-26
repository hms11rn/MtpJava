package com.github.hms11rn.mtp.win32;

public class MtpWin32 {


    public static PortableDeviceManagerWin32 getWin32Manager() {
        return new PortableDeviceManagerWin32();
    }

    public static String getGuid(String name) {
        return PropertiesWin32.getGuid(name);
    }
}
