package com.github.hms11rn.mtp.content;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;

/**

 This interface represents a container object in a portable device that does not contain data. <br>
 A container object is a hierarchical structure that can contain other objects.<br>
 Examples of container objects include folders ({@link PortableDeviceFolderObject})
 and storage devices ({@link PortableDeviceStorageObject}).
 */
public interface PortableDeviceContainerObject extends PortableDeviceObject {


     /**
      * @return an array of child {@link PortableDeviceObject}s.
      */
     PortableDeviceObject[] getChildObjects();

     /**
      * Adds a file object to this container object.
      *
      * @param file the file to add.
      * @return the newly added {@link PortableDeviceObject}.
      * @throws IOException if there is an I/O error while reading the file.
      */
     PortableDeviceObject addFileObject(File file) throws IOException;

     /**
      * Adds a file object to this container object.
      *
      * @param is the input stream that contains the file data.
      * @param name the name of the file.
      * @return the newly added {@link PortableDeviceObject}.
      */
     PortableDeviceObject addFileObject(InputStream is, String name);

     /**
      * Adds a file object to this container object.
      *
      * @param is the input stream that contains the file data.
      * @param name the name of the file.
      * @param mimeType the MIME type of the file.
      * @return the newly added {@link PortableDeviceObject}.
      */
     PortableDeviceObject addFileObject(InputStream is, String name, String mimeType);

     /**
      * Creates a folder object with the given name and adds it to this container object.
      *
      * @param name the name of the new folder object.
      * @return the newly created {@link PortableDeviceFolderObject}.
      */
     PortableDeviceFolderObject createFolderObject(String name);

     /**
      * @return {@code true} since this is a container object.
      */
     @Override
     default boolean isContainer() {
          return true;
     }
}
