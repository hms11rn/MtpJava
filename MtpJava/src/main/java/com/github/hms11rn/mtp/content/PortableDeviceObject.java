package com.github.hms11rn.mtp.content;

import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.PortableDevice;

import java.io.InputStream;
import java.io.OutputStream;
import java.math.BigInteger;
import java.util.Date;
import java.util.Map;

/**
 * Basic Portable Device Object, This Object is similar to a file - It contains data,
 * but instead of being identified by its name, it's identified by a unique ID.
 *<br>
 * Folder Or Storage Objects can be found in {@link PortableDeviceContainerObject}
 */
@SuppressWarnings("unused")
public interface PortableDeviceObject {

    PortableDevice getDevice();

  /**
   * MTP Device Objects are identified by their name, rather by a unique id
   * assigned to every object in the device.
   * @return Unique ID of the object
   */
      String getId();

      /**
       * Displayable name
       * @return Displayable name
       */
      String getName();

      /**
       * Original File Name
       * @return Full object name including file extensions
       */
      String getOriginalFileName();

      /**
       * MTP Devices have a lot of control over operations done on the device,
       * therefor you need to check if the device allows the deletion of a file
       * before deleting it
       * @return if the device allows this object to be deleted
       */
      boolean canDelete();

      /**
       * @return if the object should be hidden
       */
      boolean isHidden();
      boolean isSystemObject();
      boolean isDrmProtected();

      /**
       * Returns false since if this was a {@link PortableDeviceContainerObject}
       * this method would be overwritten to return true
       * @return if the object is a container
       */
      default boolean isContainer() {
       return false;
      }

      /**
       * Not supported by all objects
       * @return Date Modified
       */
      Date getDateModified();
     /**
      * Not supported by all objects
      * @return Date Created
      */
      Date getDateCreated();
     /**
      * Note: not supported by <b>most</b> objects
      * @return Date Authored (?)
      */
      Date getDateAuthored();

      /**
       * @return {@link PortableDeviceContainerObject} of the parent container
       */
      PortableDeviceContainerObject getParent();
      BigInteger getSize();
      String getPersistentUniqueIdentifier();
      String getSyncID();

      String getFormat();
      String getContentType();
      Map<String, DeviceProperties.PropertyValue> getProperties();
      void reloadProperties();

      /**
       * Delete object<br>
       * in Windows do to a bug, the first deletion after the device was connected it's going
       * to take 5-15 seconds to after deletion until the device is available again
       */
      void delete();

      /**
       * copy the object to a file outside.
       * @param path to output device
       */
      void copy(String path);
      void rename(String newName);
      /**
       * Get input stream of Object
       * @return Input Stream with object data
       */
      InputStream getInputStream();
      OutputStream getOutputStream();

 OutputStream getOutputStream(int initialCapacity);
}
