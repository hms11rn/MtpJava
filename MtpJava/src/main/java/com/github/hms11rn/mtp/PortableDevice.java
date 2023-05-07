package com.github.hms11rn.mtp;

import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.util.Map;

public interface PortableDevice {

    /**
     * Name of the device that is Human Readable
     * @return friendly name
     */
    String getFriendlyName();

    String getDescription();

    String getManufacture();

    /**
     * Get all properties of the device with a UUID as a key (uuid, pid) and PropertyValue as a result
     * @return map of UUIDs and PropertyValue
     */
    Map<String, DeviceProperties.PropertyValue> getProperties();

    String getFirmwareVersion();
    String getSerialNumber();

    /**
     * @return Protocol used to connect to the device
     */
    String getProtocol();
    String getSyncPartner();

    /**
     * @return Battery level of the device from 1-100
     */
    int getPowerLevel();
    boolean IsNonConsumableSupported();
    PowerSource getPowerSource();
    /**
     * Reloads the properties of the device from the device itself
     */
    void reloadProperties();

    /**
     * Open the device, required for all operations on the device, apart from
     * getFriendlyName, getDescription, getManufacturer.
     */
     void open();
    /**
     * Close the device, after the device is closed any operations on the device will fail,
     * Getting properties about the device will still work since they are cashed.
     */
    void close();

    /**
     * Get Root Objects of Device, Typically these are going to be some type of container
     * object, usually Storage Object
     * @return Array of Root Objects
     */
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
