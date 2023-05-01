package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.content.PortableDeviceObject;
import com.github.hms11rn.mtp.content.PortableDeviceStorageObject;

import java.io.File;
import java.util.Map;

class PortableDeviceContentWin32 {

    PortableDeviceWin32 device;
    protected PortableDeviceContentWin32(PortableDeviceWin32 device) {
        this.device = device;
    }
    protected PortableDeviceObject getObjectFromID(String id, String type) {
        if (type.equals("FUNCTIONAL_CATERGORY_STORAGE")) {
            return new PortableDeviceStorageObjectWin32(id, this);
        } else if (type.equals("CONTENT_TYPE_FOLDER"))
            return new PortableDeviceContainerObjectWin32(id, this);
        return new PortableDeviceObjectWin32(id,  this);
    }

    protected String createObject(File file, String parent) {
        return device.addFileObjectN(file.getName(), parent, file);
    }

    protected boolean delete(String id) {
        return device.deleteFileN(id);
    }
    protected PortableDeviceObject[] getObjects(String containerId) {
        Map<String, String> objects;
        objects = device.getObjectsN(containerId);
        PortableDeviceObject[] retObjs = new PortableDeviceObject[objects.size()];
        int i = 0;
        for (String id : objects.keySet()) {
            retObjs[i] = getObjectFromID(id, objects.get(id));
            i++;
        }
        return retObjs;
    }
}
