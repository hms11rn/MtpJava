package com.github.hms11rn.mtp;

public class Mtp {

    /**
     * Test method for jni
     */
    public static native String[] getMtpNames();

    public static void register() {
        System.loadLibrary("mtpjava");

    }
}