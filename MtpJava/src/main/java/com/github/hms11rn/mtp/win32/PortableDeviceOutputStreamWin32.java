package com.github.hms11rn.mtp.win32;

import java.io.ByteArrayOutputStream;
import java.nio.file.AccessDeniedException;

class PortableDeviceOutputStreamWin32 extends ByteArrayOutputStream {
    String objectID;

    PortableDeviceOutputStreamWin32(String objectID) {
        super();
        this.objectID = objectID;
    }

    PortableDeviceOutputStreamWin32(int initialCapacity, String objectID) {
        super(initialCapacity);
        this.objectID = objectID;
    }

    private native int writeBuffer(String objectID, byte[] buffer, boolean append, boolean deleteAndRewrite);

    @Override
    public void flush() throws AccessDeniedException {
        int bytesWritten = writeBuffer(objectID, super.buf, false, false);
        System.out.println(bytesWritten);
        if (bytesWritten == -3)
            throw new AccessDeniedException("Object: "  + objectID + " does not support this operation");
    }

    @Override
    public void close() {
    }

}
