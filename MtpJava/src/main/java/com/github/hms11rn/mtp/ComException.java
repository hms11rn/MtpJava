package com.github.hms11rn.mtp;

/**
 * Com exceptions when creating Com Objects using the com interface in c++
 * This error is caused by the ComInterface in c++ by the Com Interface
 */
public class ComException extends RuntimeException  {

    ComException(String str) {
        throw new ComException(str, 0);
    }

    protected ComException(String str, int i) {
        super(str);
    }

}
