package com.github.hms11rn.mtp;

/**
 * Most functions of a portable device cant be used after it was closed,
 * if a function was called it will throw this exception<br>
 * Used by Jni
 */
@SuppressWarnings("unused")
public class DeviceClosedException extends RuntimeException {
    DeviceClosedException(String str) {
        super(str);
    }
}
