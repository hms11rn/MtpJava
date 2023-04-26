package com.github.hms11rn.mtp;

import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.util.Map;

public interface PortableDevice {

    String getFriendlyName();

    String getDescription();

    String getManufacture();

    Map<String, DeviceProperties.PropertyValue> getProperties();

    String getFirmwareVersion();
    String getSerialNumber();
    String getProtocol();
    String getSyncPartner();
    int getPowerLevel();
    boolean IsNonConsumableSupported();
    PowerSource getPowerSource();

    // device content

     void open();
     void close();
     PortableDeviceObject[] getRootObjects();

     enum PowerSource {
        BATTERY,
         EXTERNAL,
        UNKNOWN
    }

    enum PortableDeviceType {
        GENERIC,
        CAMERA,
        MEDIA_PLAYER,
        PHONE,
        VIDEO,
        PERSONAL_INFORMATION_MANAGER,
        AUDIO_RECORDER
    }

}
