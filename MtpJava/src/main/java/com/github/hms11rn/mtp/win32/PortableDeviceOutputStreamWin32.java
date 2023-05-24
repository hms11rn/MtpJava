package com.github.hms11rn.mtp.win32;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.Objects;

class PortableDeviceOutputStreamWin32 extends OutputStream {

    byte[] buffer;
    int position = 0;
    int bufferGrowth = bufferGrowthGlobal;

    /**
     * Default growth size
     */
    static int bufferGrowthGlobal = 2048;
    PortableDeviceOutputStreamWin32(String objectId) {
        buffer = new byte[bufferGrowth];
    }

    PortableDeviceOutputStreamWin32(int initialCapacity, String objectId) {
        buffer = new byte[initialCapacity];
    }
    @Override
    public void write(int b) {
        ensureCapacity();
        buffer[position] = (byte) b;
        position++;
    }

    @Override
    public void write(byte[] b, int off, int len) {
        this.buffer = b; // Set buffer to b
        flush(); // Flush changes into file
    }

    /**
     * ensure that the buffer is big enough to take to new byte
     */
    private void ensureCapacity() {
        if ((position  + 1) > buffer.length) {
            int newCapacity = buffer.length + bufferGrowth;
            buffer = Arrays.copyOf(buffer, newCapacity);
        }
    }
    private native void writeBuffer(byte[] buffer);

    @Override
    public void flush() {
        writeBuffer(buffer);
        position = 0;
    }

    @Override
    public void close() {
    }

}
