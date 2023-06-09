package com.github.hms11rn.mtp;

import com.github.hms11rn.mtp.win32.MtpWin32;

import java.math.BigInteger;

/**
 * A device property is a unique UUID for a property, these UUIDs are the way
 * the Computer connects to the Portable Device
 */
public class DeviceProperties {

    /**
     * Default Device ID
     */
    public static final String DEVICE_ROOT_ID = "DEVICE";
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
        if (System.getProperty("os.name").contains("Windows")) {
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
    }
    @SuppressWarnings({"unused", "unchecked"})
    public static class PropertyValue {
        private final Object value;
        private final String key;
        private final Class<?> type;
        public PropertyValue(Class<?> type, String key,  Object value) {
            this.type = type;
            this.key = key;
            this.value = value;
        }

        public String getKey() {
            return key;
        }
        public Class<?> getType() {
            return type;
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
        public BigInteger getBigIntegerValue() {
            return (BigInteger) value;
        }
    }
}
