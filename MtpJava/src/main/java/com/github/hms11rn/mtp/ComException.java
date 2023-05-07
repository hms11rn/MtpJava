package com.github.hms11rn.mtp;

/**
 * Com exceptions when creating Com Objects in c++
 */
public class ComException extends RuntimeException  {

    ComException(String str) {
        super(str);
    }

}
