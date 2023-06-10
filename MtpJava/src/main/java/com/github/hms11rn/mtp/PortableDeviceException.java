package com.github.hms11rn.mtp;

/**
 * General exception for portable devices
 * Used by Native Code
 */
public class PortableDeviceException extends RuntimeException {
    PortableDeviceException(String error) {
        super(error);
    }
}
