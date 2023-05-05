package com.github.hms11rn.mtp.win32;

import java.io.InputStream;

class PortableDeviceInputStreamWin32 extends InputStream {
    private byte[] bytes;
    private int pos;
    protected PortableDeviceInputStreamWin32(byte[] b) {
        this.bytes = b;
    }
    @Override
    public int read() {
        if (pos >= bytes.length) {
            return -1;
        }
        return bytes[pos++];
    }
}
