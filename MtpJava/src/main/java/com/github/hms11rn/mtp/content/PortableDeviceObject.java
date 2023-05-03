package com.github.hms11rn.mtp.content;

import com.github.hms11rn.mtp.DeviceProperties;

import java.math.BigInteger;
import java.util.Date;
import java.util.Map;

@SuppressWarnings("unused")
public interface PortableDeviceObject {

     String getId();
     String getName();
      String getOriginalFileName();
      boolean canDelete();
      boolean isHidden();
      boolean isSystemObject();
      boolean isDrmProtected();
      Date getDateModified();
      Date getDateCreated();
      Date getDateAuthored();
      PortableDeviceObject getParent();
      BigInteger getSize();
      String getPersistentUniqueIdentifier();
      String getSyncID();

      String getFormat();
      String getContentType();
      Map<String, DeviceProperties.PropertyValue> getProperties();
      boolean delete();
      void copy(String path);
}
