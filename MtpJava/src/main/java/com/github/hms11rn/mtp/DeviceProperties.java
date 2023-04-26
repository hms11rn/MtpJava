package com.github.hms11rn.mtp;

import com.github.hms11rn.mtp.win32.MtpWin32;

public class DeviceProperties {

    public static String MANUFACTURE;
    public static String SERIAL_NUMBER;
    public static String POWER_SOURCE;
    public static String FIRMWARE_VERSION;
    public static String POWER_LEVEL;
    public static String PROTOCOL;
    public static String SUPPORTS_NON_CONSUMABLE;
    public static String SYNC_PARTNER;

    static {
        // if windows ...
        MANUFACTURE = MtpWin32.getGuid("WPD_DEVICE_MANUFACTURER");
        SERIAL_NUMBER = MtpWin32.getGuid("WPD_DEVICE_SERIAL_NUMBER");
        POWER_SOURCE = MtpWin32.getGuid("WPD_DEVICE_POWER_SOURCE");
        FIRMWARE_VERSION = MtpWin32.getGuid("WPD_DEVICE_FIRMWARE_VERSION");
        POWER_LEVEL = MtpWin32.getGuid("WPD_DEVICE_POWER_LEVEL");
        PROTOCOL = MtpWin32.getGuid("WPD_DEVICE_PROTOCOL");
        SUPPORTS_NON_CONSUMABLE = MtpWin32.getGuid("SUPPORTS_NON_CONSUMABLE");
        SYNC_PARTNER = MtpWin32.getGuid("WPD_DEVICE_SYNC_PARTNER");
    }
    @SuppressWarnings("unused")
    public static class PropertyValue {
        private Object value;
        private String key;
        private Class type;
        public PropertyValue(Class type, String key,  Object value) {
            this.type = type;
            this.key = key;
            this.value = value;
        }

        @Override
        public String toString() {
            return value.toString();
        }
        public String getStringValue() {

            return value.toString();
        }
        public <T> T getValue() {

            return (T) value;
        }

        public <T> T getValue(T type) {

            return (T) value;
        }

        public <T> T[] getArrayValue(T type) {

            return (T[]) value;
        }

        public <T> T[] getArrayValue() {

            return (T[]) value;
        }
    }
}
