package com.github.hms11rn.mtp.win32.content;

import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.math.BigInteger;
import java.util.Date;

class PortableDeviceObjectWin32 implements PortableDeviceObject {

    String id;
    protected PortableDeviceObjectWin32(String id) {
        this.id = id;
    }

    @Override
    public String getId() {
        return id;
    }

    @Override
    public String getName() {
        return null;
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
