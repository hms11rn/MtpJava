package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.content.PortableDeviceStorageObject;
import static com.github.hms11rn.mtp.win32.PropertiesWin32.*;
import java.math.BigInteger;

public class PortableDeviceStorageObjectWin32 extends PortableDeviceContainerObjectWin32 implements PortableDeviceStorageObject {
    protected PortableDeviceStorageObjectWin32(String id, PortableDeviceContentWin32 content) {
        super(id, content);
    }

    @Override
    public String getFileSystemType() {
        DeviceProperties.PropertyValue  ret = properties.get(WPD_STORAGE_FILE_SYSTEM_TYPE.toString());
        if (ret == null)
            return null;
        return ret.getStringValue();
    }

    @Override
    public String getDescription() {
        DeviceProperties.PropertyValue  ret = properties.get(WPD_STORAGE_DESCRIPTION.toString());
        if (ret == null)
            return null;
        return ret.getStringValue();
    }

    @Override
    public String getSerialNumber() {
        DeviceProperties.PropertyValue  ret = properties.get(WPD_STORAGE_SERIAL_NUMBER.toString());
        if (ret == null)
            return null;
        return ret.getStringValue();
    }

    @Override
    public BigInteger getCapacity() {
        DeviceProperties.PropertyValue  ret = properties.get(WPD_STORAGE_CAPACITY.toString());
        if (ret == null)
            return null;
        return ret.getBigIntergerValue();
    }

    @Override
    public BigInteger getCapacityInObjects() {
        DeviceProperties.PropertyValue  ret = properties.get(WPD_STORAGE_CAPACITY_IN_OBJECTS.toString());
        if (ret == null)
            return null;
        return ret.getBigIntergerValue();
    }

    @Override
    public BigInteger getFreeSpace() {
        DeviceProperties.PropertyValue  ret = properties.get(WPD_STORAGE_FREE_SPACE_IN_BYTES.toString());
        if (ret == null)
            return null;
        return ret.getBigIntergerValue();
    }

    @Override
    public BigInteger getFreeSpaceInObjects() {
        DeviceProperties.PropertyValue  ret = properties.get(WPD_STORAGE_FREE_SPACE_IN_OBJECTS.toString());
        if (ret == null)
            return null;
        return ret.getBigIntergerValue();
    }

    @Override
    public BigInteger getMaximumObjectSize() {
        DeviceProperties.PropertyValue  ret = properties.get(WPD_STORAGE_MAX_OBJECT_SIZE.toString());
        if (ret == null)
            return null;
        return ret.getBigIntergerValue();
    }
}
