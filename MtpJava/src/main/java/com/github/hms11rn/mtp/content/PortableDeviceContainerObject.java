package com.github.hms11rn.mtp.content;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

public interface PortableDeviceContainerObject extends PortableDeviceObject {

     PortableDeviceObject[] getChildObjects();
     PortableDeviceObject addFileObject(File file) throws FileNotFoundException, IOException;

     PortableDeviceFolderObject createFolderObject(String name);

}
