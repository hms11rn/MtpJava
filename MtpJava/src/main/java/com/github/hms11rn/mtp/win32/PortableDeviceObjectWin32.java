package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

class PortableDeviceObjectWin32 implements PortableDeviceObject {

    Map<String, DeviceProperties.PropertyValue> properties;

    String id;
    protected PortableDeviceObjectWin32(String id) {
        this.id = id;
        init(id);
    }

    public native Map<String, DeviceProperties.PropertyValue> getPropertiesN();

    private void loadProperties() {
        if (properties == null)
            reloadProperties();
    }
    public void reloadProperties() {
        Map nativeProperties = getPropertiesN();
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
        return null;
    }

    @Override
    public boolean canDelete() {
        return false;
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
        return null;
    }

    @Override
    public Date getDateCreated() {
        return null;
    }

    @Override
    public Date getDateAuthored() {
        return null;
    }

    @Override
    public PortableDeviceObject getParent() {
        return null;
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

}
