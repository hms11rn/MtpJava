package com.github.hms11rn.mtp.win32;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.Objects;

class PortableDeviceOutputStreamWin32 extends OutputStream {
    String objectID;
    byte[] buffer;
    int position = 0;
    int bufferGrowth = bufferGrowthGlobal;
    int initialCapacity = bufferGrowth;

    /**
     * Default growth size
     */
    static int bufferGrowthGlobal = 2048;

    PortableDeviceOutputStreamWin32(String objectID) {
        this.objectID = objectID;
        buffer = new byte[initialCapacity];
    }

    PortableDeviceOutputStreamWin32(int initialCapacity, String objectID) {
        this.objectID = objectID;
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
    private native void writeBuffer(String objectID, byte[] buffer, boolean append);

    @Override
    public void flush() {
        writeBuffer(objectID, buffer, false);
        position = 0;
        buffer = new byte[initialCapacity]; // Clear buffer
    }

    @Override
    public void close() {
    }

}
