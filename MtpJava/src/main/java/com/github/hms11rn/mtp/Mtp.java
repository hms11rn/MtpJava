package com.github.hms11rn.mtp;

public class Mtp {

    /**
     * Register natives, in the future this will be done automatically
     */
    public static void register() {
        System.loadLibrary("mtpjava");
        registerJNI();

    }
    public static native void registerJNI();
}