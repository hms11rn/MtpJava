package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.PortableDevice;
import com.github.hms11rn.mtp.content.PortableDeviceContainerObject;
import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.io.File;
import java.io.InputStream;
import java.nio.file.InvalidPathException;
import java.util.*;
import java.util.regex.Pattern;

class PortableDeviceWin32 implements PortableDevice {
    private final String deviceID;

    private Map<String, Object> nativeProperties;
    private Map<String, DeviceProperties.PropertyValue> properties;
    private final PortableDeviceContentWin32 content;
    private boolean rewrite = false;

    PortableDeviceWin32(String deviceID) {
        this.deviceID = deviceID;
        this.content = new PortableDeviceContentWin32(this);
        //   reloadProperties(); // Don't open device yet
    }
    private static native String getFriendlyName(String deviceID);
    private static native String getManufacturer(String deviceID);
    private static native String getDescription(String deviceID);
    protected native Map<String, Object> getProperties(String objectID);


    @Override
    public String getID() {
        return deviceID;
    }

    @Override
    public void reloadProperties() {
        nativeProperties = getProperties(DeviceProperties.DEVICE_ROOT_ID);
        if (nativeProperties == null) {
            System.err.println("Native Properties are Null");
        }

        Map<String, DeviceProperties.PropertyValue> ret;
        ret = PortableDeviceContentWin32.convertNativePropertiesToJava(nativeProperties);
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
        return getProperties().get(PropertiesWin32.WPD_DEVICE_SERIAL_NUMBER.toString()).getStringValue();
    }

    @Override
    public String getProtocol() {
        DeviceProperties.PropertyValue protocol = getProperties().get(PropertiesWin32.WPD_DEVICE_PROTOCOL.toString());
        return getNoNullValue(protocol);
    }

    @Override
    public String getSyncPartner() {
        DeviceProperties.PropertyValue partner = getProperties().get(PropertiesWin32.WPD_DEVICE_SYNC_PARTNER.toString());
        return getNoNullValue(partner);
    }

    @Override
    public int getPowerLevel() {
        DeviceProperties.PropertyValue powerL = getProperties().get(PropertiesWin32.WPD_DEVICE_POWER_LEVEL.toString());
        if (powerL == null)
            return -1;
        return powerL.getValue(0); // 0 is just an indicator of object type, in this case Integer

    }

    @Override
    public boolean IsNonConsumableSupported() {
        DeviceProperties.PropertyValue supportsNonConsumable = getProperties().get(PropertiesWin32.WPD_DEVICE_SUPPORTS_NON_CONSUMABLE.toString());
        if (supportsNonConsumable == null)
            return false;
        return supportsNonConsumable.getValue(true);
    }


    @Override
    public void open() {
        openN();
      //  reloadProperties();
    }

    @Override
    public void close() {
        closeN();
    }

    protected native void openN();

    protected native void closeN();

    protected native Map<String, String> getObjectsN(String objId);
    protected native String addFileObjectN(String name, String parentID, File file, String contentType, String format);
    protected native String addFileFromInputStreamN(String name, String parentID, InputStream inStream, String contentType, String format);
    protected native String addFolderObjectN(String id, String parentId);
    protected native void copyFileN(String id, String path);
    protected native boolean deleteFileN(String id, int recursion);
    protected native void updatePropertyN(String id, String fmtid, int pid, int varType, String value);
    protected native byte[] getBytesN(String id);

    @Override
    public PortableDeviceObject[] getRootObjects() {
        Map<String, String> objectsMap = getObjectsN(DeviceProperties.DEVICE_ROOT_ID);
        PortableDeviceObject[] objects = new PortableDeviceObject[objectsMap.size()];
        int i = 0;
        for (String id : objectsMap.keySet()) {
            objects[i] = content.getObjectFromID(id, objectsMap.get(id));
            i++;
        }
        return objects;
    }

    @Override
    public PortableDeviceObject getObjectByID(String id) {
        return content.getObjectFromID(id, null);
    }

    @Override
    public PortableDeviceObject getObject(String namePath) {
        namePath = namePath.replace("\\", "/"); // Reassigning parameter since it's only for constituency
        String[] objects = namePath.split(Pattern.quote("/"));
        // Recursive reading
        PortableDeviceObject[] rootObjects = getRootObjects(); // Obtain root Objects first
        PortableDeviceContainerObject nextObject = null;
        for (PortableDeviceObject p : rootObjects) {
            if (p.getName().equalsIgnoreCase(objects[0])) {
                if (objects.length == 1)
                    return p;
                if (!(p instanceof PortableDeviceContainerObject))
                    throw new IllegalArgumentException("Path contains object that is not a container object");
                nextObject = (PortableDeviceContainerObject) p;
            }
        }
        if (nextObject == null)
            throw new InvalidPathException(namePath, "Failed to find first object in path");
        for (int i = 1; i < objects.length; i++) {
            if (!nextObject.contains(objects[i]))
                throw new InvalidPathException(namePath, "Invalid Portable Device Path");
            Map<String, String> idsAndNames = nextObject.getChildNames();
            Map<String,String> treeIDsAndNames = new TreeMap(String.CASE_INSENSITIVE_ORDER);
            treeIDsAndNames.putAll(idsAndNames);
            if (i == objects.length - 1) {
                PortableDeviceObject pObj = content.getObjectFromID(treeIDsAndNames.get(objects[i]), null); // Return before exception gets thrown
                return pObj;
            }
            try {
                nextObject = new PortableDeviceContainerObjectWin32(treeIDsAndNames.get(objects[i]), content);
            } catch (IllegalStateException e) {
                throw new IllegalArgumentException("Path contains object that is not a container object");
            }
        }
        return null;
    }

    @Override
    public void setOutputStreamWriteMethod(boolean rewrite) {
        this.rewrite = rewrite;
    }

    @Override
    public boolean getOutputStreamWriteMethod() {
        return rewrite;
    }

    @Override
    public PowerSource getPowerSource() {
        int powerSource = properties.get(PropertiesWin32.WPD_DEVICE_POWER_SOURCE.toString()).getValue(0);
        if (powerSource == 0)
            return PowerSource.BATTERY;
        if (powerSource == 1)
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
