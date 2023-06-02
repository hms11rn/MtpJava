package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.PortableDevice;
import com.github.hms11rn.mtp.content.PortableDeviceContainerObject;
import com.github.hms11rn.mtp.content.PortableDeviceObject;


import static com.github.hms11rn.mtp.win32.PropertiesWin32.*;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.math.BigInteger;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

class PortableDeviceObjectWin32 implements PortableDeviceObject {

    Map<String, DeviceProperties.PropertyValue> properties;
    final String id;
    final PortableDeviceContentWin32 content;
    /**
     * Used to convert c++ string date to {@link java.util.Date}
     */
    final DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd:HH:mm:sss", Locale.ENGLISH);
    protected PortableDeviceObjectWin32(String id, PortableDeviceContentWin32 content) {
        this.id = id;
        this.content = content;
        loadProperties();
    }

    /**
     * static method to avoid async between jni and constructor call
     * @param id device id
     * @return map of Strings and PropertyValue
     */
    public static native Map<String, Object> getPropertiesN(String id);

    @Override
    public PortableDevice getDevice() {

        return content.device;
    }
    private void loadProperties() {
        if (properties == null)
            reloadProperties();
    }

    @Override
    public void reloadProperties() {
        Map<String, Object> nativeProperties = getPropertiesN(id);
        Map <String, DeviceProperties.PropertyValue> ret = new HashMap<>();

        for (int i = 0; i < nativeProperties.size(); i++) {
            String key = new ArrayList<>(nativeProperties.keySet()).get(i);
            Object obj = nativeProperties.get(key);
            ret.put(key, new DeviceProperties.PropertyValue(obj.getClass(), key, obj));
        }
        properties = ret;
    }
    @Override
    public Map<String, DeviceProperties.PropertyValue> getProperties() {
       loadProperties();
        return properties;
    }

    @Override
    public String getId() {
        return id;
    }

    @Override
    public String getName() {
        loadProperties();
        return properties.get(DeviceProperties.OBJECT_NAME).getStringValue();
    }

    @Override
    public String getOriginalFileName() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_ORIGINAL_FILE_NAME.toString());
        if (ret == null)
            return null;
        return ret.getStringValue();
    }

    @Override
    public boolean canDelete() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_CAN_DELETE.toString());
        if (ret == null)
            return false;
        return ret.getBooleanValue();
    }

    @Override
    public boolean isHidden() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_ISHIDDEN.toString());
        if (ret == null)
            return false;
        return ret.getBooleanValue();
    }

    @Override
    public boolean isSystemObject() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_ISSYSTEM.toString());
        if (ret == null)
            return false;
        return ret.getBooleanValue();
    }

    @Override
    public boolean isDrmProtected() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_IS_DRM_PROTECTED.toString());
        if (ret == null)
            return false;
        return ret.getBooleanValue();
    }

    @Override
    public Date getDateModified() {
            DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_DATE_MODIFIED.toString());
            if (ret == null)
                return null;
            try {
                return dateFormat.parse(ret.getStringValue());
            } catch (ParseException e) {
                throw new RuntimeException(e);
        }
    }

    @Override
    public Date getDateCreated() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_DATE_CREATED.toString());
        if (ret == null)
            return null;
        try {
            return dateFormat.parse(ret.getStringValue());
        } catch (ParseException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Date getDateAuthored() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_DATE_AUTHORED.toString());
        if (ret == null)
            return null;
        try {
            return dateFormat.parse(ret.getStringValue());
        } catch (ParseException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public PortableDeviceContainerObject getParent() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_PARENT_ID.toString());
        if (ret == null)
            return null;
        return new PortableDeviceContainerObjectWin32(ret.getStringValue(), content);
    }

    @Override
    public BigInteger getSize() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_SIZE.toString());
        if (ret == null)
            return null;
        return ret.getBigIntegerValue();
    }

    @Override
    public String getPersistentUniqueIdentifier() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_PERSISTENT_UNIQUE_ID.toString());
        if (ret == null)
            return null;
        return ret.getStringValue();
    }

    @Override
    public String getSyncID() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_SYNC_ID.toString());
        if (ret == null)
            return null;
        return ret.getStringValue();    }

    @Override
    public String getFormat() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_FORMAT.toString());
        if (ret == null)
            return null;
        return ret.getStringValue();
    }

    @Override
    public String getContentType() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_CONTENT_TYPE.toString());
        if (ret == null)
            return null;
        return ret.getStringValue();
    }

    @Override
    public void delete() {
        content.delete(id, 0);
    }

    @Override
    public void copy(String path) {
        content.copyFile(id, path);
    }
    @Override
    public void rename(String newName) {
        content.rename(id, newName);
    }
    @Override
    public InputStream getInputStream() {
        return new ByteArrayInputStream(content.getBytes(id));
    }

    /**
     * OutputStream of this object to write data into
     */
    @Override
    public OutputStream getOutputStream() {
        return new PortableDeviceOutputStreamWin32(id, getDevice().getOutputStreamWriteMethod());
    }

    /**
     * Get OutputStream of this object with initial capacity of buffer (if you want to write a known amount of bytes call this)
     */
    @Override
    public OutputStream getOutputStream(int initialCapacity) {
        return new PortableDeviceOutputStreamWin32(initialCapacity, id, getDevice().getOutputStreamWriteMethod());
    }
}
