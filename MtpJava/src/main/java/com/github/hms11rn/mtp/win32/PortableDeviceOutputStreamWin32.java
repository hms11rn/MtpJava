package com.github.hms11rn.mtp.win32;

import java.io.ByteArrayOutputStream;
import java.nio.file.AccessDeniedException;

class PortableDeviceOutputStreamWin32 extends ByteArrayOutputStream {
    private final String objectID;
    private boolean append = false;
    private final boolean rewrite;

    PortableDeviceOutputStreamWin32(String objectID, boolean rewrite) {
        super();
        this.objectID = objectID;
        this.rewrite = rewrite;
    }

    PortableDeviceOutputStreamWin32(int initialCapacity, String objectID, boolean rewrite) {
        super(initialCapacity);
        this.objectID = objectID;
        this.rewrite = rewrite;
    }

    private native int writeBuffer(String objectID, byte[] buffer, int size, boolean append, boolean rewrite);

    @Override
    public void flush() throws AccessDeniedException {
        int bytesWritten = writeBuffer(objectID, super.toByteArray(), super.count, append, rewrite);
        if (bytesWritten == -3)
            throw new AccessDeniedException("Object: "  + objectID + " does not support this operation");
    }

    @Override
    public void close() {
    }

    public void setAppend(boolean append) {
        this.append = append;
    }

}
