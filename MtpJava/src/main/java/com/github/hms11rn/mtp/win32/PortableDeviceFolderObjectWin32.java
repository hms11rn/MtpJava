package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.content.PortableDeviceFolderObject;

class PortableDeviceFolderObjectWin32 extends PortableDeviceContainerObjectWin32 implements PortableDeviceFolderObject {
    protected PortableDeviceFolderObjectWin32(String id, PortableDeviceContentWin32 content) {
        super(id, content);
    }
}
