package com.github.hms11rn.mtp.win32;

import java.io.ByteArrayOutputStream;
import java.nio.file.AccessDeniedException;

class PortableDeviceOutputStreamWin32 extends ByteArrayOutputStream {
    private final String objectID;
    private boolean append = false;
    private final boolean rewrite;

    PortableDeviceObjectWin32 object;
    PortableDeviceOutputStreamWin32(String objectID, PortableDeviceObjectWin32 object, boolean rewrite) {
        super();
        this.objectID = objectID;
        this.rewrite = rewrite;
        this.object = object;
    }

    PortableDeviceOutputStreamWin32(int initialCapacity, String objectID, boolean rewrite) {
        super(initialCapacity);
        this.objectID = objectID;
        this.rewrite = rewrite;
    }

    private native int writeBuffer(String objectID, byte[] buffer, int size, boolean append, boolean rewrite, StringBuilder newObjectID);

    @Override
    public void flush() throws AccessDeniedException {
        StringBuilder b = new StringBuilder();
        int bytesWritten = writeBuffer(objectID, super.toByteArray(), super.count, append, rewrite, b);
        if (rewrite) {
           object.setID(b.toString());

        }
        if (bytesWritten == -3)
            throw new AccessDeniedException("Object: "  + objectID + " does not support this operation, try calling PortableDevice#setOutputStreamWriteMethod(true)");
    }

    @Override
    public void close() {
    }

    public void setAppend(boolean append) {
        this.append = append;
    }

}
