package com.github.hms11rn.mtp;

/**
 * Com exceptions when creating Com Objects using the com interface in c++
 * If this error occurs Open an Issue on Github (This is a fatal exception)
 */
public class ComException extends RuntimeException  {

    ComException(String str) {
        throw new ComException(str, 0);
    }

    protected ComException(String str, int i) {
        super(str);
    }

}
