package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.content.PortableDeviceObject;


import static com.github.hms11rn.mtp.win32.PropertiesWin32.*;

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
        init(id);

    }

    /**
     * static method to avoid async between jni and constructor call
     * @param id device id
     * @return map of Strings and PropertyValue
     */
    public static native Map<String, DeviceProperties.PropertyValue> getPropertiesN(String id);

    private void loadProperties() {
        if (properties == null)
            reloadProperties();
    }
    public void reloadProperties() {
        Map nativeProperties = getPropertiesN(id);
        Map <String, DeviceProperties.PropertyValue> ret = new HashMap<>();

        for (int i = 0; i < nativeProperties.size(); i++) {
            String key = (String) new ArrayList(nativeProperties.keySet()).get(i);
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


    public native void init(String id);

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
        return false;
    }

    @Override
    public boolean isSystemObject() {
        return false;
    }

    @Override
    public boolean isDrmProtected() {
        return false;
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
        }    }

    @Override
    public PortableDeviceObject getParent() {
        DeviceProperties.PropertyValue ret = properties.get(WPD_OBJECT_PARENT_ID.toString());
        if (ret == null)
            return null;
        return new PortableDeviceObjectWin32(ret.getStringValue(), content);
    }

    @Override
    public BigInteger getSize() {
        return null;
    }

    @Override
    public String getPersistentUniqueIdentifier() {
        return null;
    }

    @Override
    public String getSyncID() {
        return null;
    }

    @Override
    public String getFormat() {
        return null;
    }

    @Override
    public String getContentType() {
        return null;
    }

    @Override
    public boolean delete() {
        return content.delete(id);
    }
}
