package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.content.PortableDeviceContainerObject;
import com.github.hms11rn.mtp.content.PortableDeviceFolderObject;
import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

public class PortableDeviceContainerObjectWin32 extends PortableDeviceObjectWin32 implements PortableDeviceContainerObject {
    protected PortableDeviceContainerObjectWin32(String id, PortableDeviceContentWin32 content) {
        super(id, content);
    }

    @Override
    public PortableDeviceObject[] getChildObjects() {
        return content.getObjects(id);
    }

    @Override
    public PortableDeviceObject addFileObject(File file) throws FileNotFoundException, IOException {
        return new PortableDeviceObjectWin32(content.createObject(file, id), content);
    }

    @Override
    public PortableDeviceFolderObject createFolderObject(String name) {
        return null;
    }
}
