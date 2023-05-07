package com.github.hms11rn.mtp.content;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;

public interface PortableDeviceContainerObject extends PortableDeviceObject {

     PortableDeviceObject[] getChildObjects();
     PortableDeviceObject addFileObject(File file) throws IOException;
     PortableDeviceObject addFileObject(InputStream is);
     PortableDeviceFolderObject createFolderObject(String name);

     @Override
     default boolean isContainer() {
          return true;
     }
}
