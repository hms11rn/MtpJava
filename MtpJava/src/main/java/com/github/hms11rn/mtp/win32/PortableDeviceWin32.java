package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.PortableDevice;
import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

class PortableDeviceWin32 implements PortableDevice {
    private String deviceID;

    private boolean isOpened;

    private Map nativeProperties;
    private Map<String, DeviceProperties.PropertyValue> properties;
    private PortableDeviceContentWin32 content;

    PortableDeviceWin32(String deviceID) {

        this.deviceID = deviceID;
        PortableDeviceContentWin32 content = new PortableDeviceContentWin32(this);
        this.content = content;
        reloadProperties(); // load in properties
    }
    /**
     * 0: name
     * 1: manufacture
     * 2:firmware version
     * 3:serial number
     * 4: power source
     * @return
     */



    private static native String getFriendlyName(String deviceID);
    private static native String getManufacturer(String deviceID);
    private static native String getDescription(String deviceID);
    private static native Map getProperties(String deviceID);


    @Override
    public void reloadProperties() {
        nativeProperties = getProperties(deviceID);
        if (nativeProperties == null) {
            System.err.println("Native Properties are Null");
        }

        Map<String, DeviceProperties.PropertyValue> ret = new HashMap<>();
        for (int i = 0; i < nativeProperties.size(); i++) {
            String key = (String) new ArrayList(nativeProperties.keySet()).get(i);
            Object obj = nativeProperties.get(key);
            ret.put(key, new DeviceProperties.PropertyValue(obj.getClass(), key, obj));
        }
        if (!isOpened)
            close();
        this.properties = ret;
    }

    public Map<String, DeviceProperties.PropertyValue> getProperties() {
        if (nativeProperties == null)
            reloadProperties();
        return this.properties;
    }
    @Override
    public String getFriendlyName() {
        return getFriendlyName(deviceID);
    }

    @Override
    public String getManufacture() {
        return getManufacturer(deviceID);
    }

    @Override
    public String getDescription() {

        return getDescription(deviceID);
    }

    @Override
    public String getFirmwareVersion() {
        return getProperties().get(PropertiesWin32.WPD_DEVICE_FIRMWARE_VERSION.toString()).getStringValue();
    }

    @Override
    public String getSerialNumber() {
        return properties.get(PropertiesWin32.WPD_DEVICE_SERIAL_NUMBER.toString()).getStringValue();
    }

    @Override
    public String getProtocol() {
        DeviceProperties.PropertyValue protocol = properties.get(PropertiesWin32.WPD_DEVICE_PROTOCOL.toString());
        return getNoNullValue(protocol);
    }

    @Override
    public String getSyncPartner() {
        DeviceProperties.PropertyValue partner = properties.get(PropertiesWin32.WPD_DEVICE_SYNC_PARTNER.toString());
        return getNoNullValue(partner);
    }

    @Override
    public int getPowerLevel() {
        DeviceProperties.PropertyValue powerL = properties.get(PropertiesWin32.WPD_DEVICE_POWER_LEVEL.toString());
        if (powerL == null)
            return -1;
        return powerL.getValue(0); // 0 is just an indicator of object type, in this cade Integer

    }

    @Override
    public boolean IsNonConsumableSupported() {
        DeviceProperties.PropertyValue supportsNonConsumable = properties.get(PropertiesWin32.WPD_DEVICE_SUPPORTS_NON_CONSUMABLE.toString());
        if (supportsNonConsumable == null)
            return false;
        return supportsNonConsumable.getValue(true);
    }


    @Override
    public void open() {
        openN();
        isOpened = true;
    }

    @Override
    public void close() {
        closeN();
        isOpened = false;
    }

    protected native void openN();

    protected native void closeN();

    protected native Map<String, String> getObjectsN(String objId);
    protected native String addFileObjectN(String name, String parentId, File file);

    @Override
    public PortableDeviceObject[] getRootObjects() {
        Map<String, String> objects = getObjectsN("DEVICE");
        PortableDeviceObject[] objs = new PortableDeviceObject[objects.size()];
        int i = 0;
        for (String id : objects.keySet()) {
            objs[i] = content.getObjectFromID(id, objects.get(id));
            i++;
        }
        return objs;
    }

    @Override
    public PowerSource getPowerSource() {
        String powerSource = properties.get(PropertiesWin32.WPD_DEVICE_POWER_SOURCE.toString()).getStringValue();
        if (powerSource.equals("0"))
            return PowerSource.BATTERY;
        if (powerSource.equals("1"))
            return PowerSource.EXTERNAL;
        else
            return PowerSource.UNKNOWN;
    }

    private static String getNoNullValue(DeviceProperties.PropertyValue p) {
        if (p == null)
            return null;
        return p.getStringValue();
    }


}