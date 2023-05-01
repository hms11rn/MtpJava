package com.github.hms11rn.mtp.content;

import com.github.hms11rn.mtp.DeviceProperties;

import java.math.BigInteger;
import java.util.Date;
import java.util.Map;

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

      // dk what these do, just saw them in jmtp, will update
      String getFormat();
      String getContentType();
      Map<String, DeviceProperties.PropertyValue> getProperties();

      boolean delete();
}
