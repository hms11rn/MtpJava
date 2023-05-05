package com.github.hms11rn.mtp;

/**
 * General exception for portable devices
 * Used by Jni
 */
public class PortableDeviceException extends RuntimeException {
    PortableDeviceException(String error) {
        super(error);
    }
}
