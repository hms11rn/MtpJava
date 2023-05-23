package com.github.hms11rn.mtp.win32;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

public class PortableDeviceOutputStreamWin32 extends OutputStream {

    byte[] buffer;
    @Override
    public void write(int b) throws IOException {
        // write to buffer
    }

    @Override
    public void flush() {
        // Commit Buffer
    }

    @Override
    public void close() {
    }
}
