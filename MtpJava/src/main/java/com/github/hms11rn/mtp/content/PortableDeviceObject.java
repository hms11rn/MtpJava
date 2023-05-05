package com.github.hms11rn.mtp.content;

import com.github.hms11rn.mtp.DeviceProperties;

import java.io.InputStream;
import java.math.BigInteger;
import java.util.Date;
import java.util.Map;

@SuppressWarnings("unused")
public interface PortableDeviceObject {

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
       * Note: not supported by all objects
       * @return Date Modified
       */
      Date getDateModified();
     /**
      * Note: not supported by all objects
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
      boolean delete();
      void copy(String path);
      void rename(String newName);
      InputStream getInputStream();
 }
