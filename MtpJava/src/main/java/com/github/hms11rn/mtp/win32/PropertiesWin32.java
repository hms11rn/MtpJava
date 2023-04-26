package com.github.hms11rn.mtp.win32;

class PropertiesWin32 {

    protected static Guid WPD_DEVICE_MANUFACTURER = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 7);
    protected static Guid WPD_DEVICE_FIRMWARE_VERSION = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 9);
    protected static Guid WPD_DEVICE_POWER_SOURCE = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 5);
    protected static Guid WPD_DEVICE_SERIAL_NUMBER = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 3);
    protected static Guid WPD_DEVICE_POWER_LEVEL = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 4);
    protected static Guid WPD_DEVICE_PROTOCOL = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 6);
    protected static Guid WPD_DEVICE_SUPPORTS_NON_CONSUMABLE = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}",10);
    protected static Guid WPD_DEVICE_SYNC_PARTNER = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 2);

    protected static String getGuid(String name) {
        if (name.equals("WPD_DEVICE_MANUFACTURER"))
            return WPD_DEVICE_MANUFACTURER.toString();
        if (name.equals("WPD_DEVICE_FIRMWARE_VERSION"))
            return WPD_DEVICE_SERIAL_NUMBER.toString();
        if (name.equals("WPD_DEVICE_POWER_SOURCE"))
            return WPD_DEVICE_POWER_SOURCE.toString();
        if (name.equals("WPD_DEVICE_SERIAL_NUMBER"))
            return WPD_DEVICE_FIRMWARE_VERSION.toString();
        if (name.equals("WPD_DEVICE_POWER_LEVEL"))
            return WPD_DEVICE_POWER_LEVEL.toString();
        if (name.equals("WPD_DEVICE_PROTOCOL"))
            return WPD_DEVICE_PROTOCOL.toString();
        if (name.equals("WPD_DEVICE_SUPPORTS_NON_CONSUMABLE"))
            return WPD_DEVICE_SUPPORTS_NON_CONSUMABLE.toString();
        if (name.equals("WPD_DEVICE_SYNC_PARTNER"))
            return WPD_DEVICE_SYNC_PARTNER.toString();
        return null;
    }
}
