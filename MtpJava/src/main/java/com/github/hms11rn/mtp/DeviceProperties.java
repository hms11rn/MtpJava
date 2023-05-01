package com.github.hms11rn.mtp;

import com.github.hms11rn.mtp.win32.MtpWin32;

import java.math.BigInteger;

public class DeviceProperties {

    public static String MANUFACTURE;
    public static String SERIAL_NUMBER;
    public static String POWER_SOURCE;
    public static String FIRMWARE_VERSION;
    public static String POWER_LEVEL;
    public static String PROTOCOL;
    public static String SUPPORTS_NON_CONSUMABLE;
    public static String SYNC_PARTNER;

    public static String OBJECT_ID;
    public static String OBJECT_CONTAINER_FUNCTIONAL_OBJECT_ID;
    public static String OBJECT_PERSISTENT_UNIQUE_ID;
    public static String OBJECT_NAME;
    public static String OBJECT_CAN_DELETE;
    public static String OBJECT_CONTENT_TYPE; // not sure yet how to implement it
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
        // object
        OBJECT_ID = MtpWin32.getGuid("WPD_OBJECT_ID");
        OBJECT_CONTAINER_FUNCTIONAL_OBJECT_ID = MtpWin32.getGuid("WPD_OBJECT_CONTAINER_FUNCTIONAL_OBJECT_ID");
        OBJECT_PERSISTENT_UNIQUE_ID = MtpWin32.getGuid("WPD_OBJECT_PERSISTENT_UNIQUE_ID");
        OBJECT_NAME = MtpWin32.getGuid("WPD_OBJECT_NAME");
        OBJECT_CAN_DELETE = MtpWin32.getGuid("WPD_OBJECT_CAN_DELETE");
        // to be figured out
        OBJECT_CONTENT_TYPE = MtpWin32.getGuid("WPD_OBJECT_CONTENT_TYPE");
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

        public boolean getBooleanValue() {

            return (Boolean) value;
        }
        public BigInteger getBigIntergerValue() {
            return (BigInteger) value;
        }
    }
}
