package com.github.hms11rn.mtp;

/**
 * Com exceptions when creating Com Objects using the com interface in c++
 * This error is caused by the Windows ComInterface in c++ by the Com Interface
 */
public class ComException extends RuntimeException  {
    final int hresult;
    ComException(String str, int hresult) {
        throw new ComException(str, null, hresult);
    }


    protected ComException(String str, Object j, int hresult) {
        super(str);
        this.hresult = hresult;
    }
    public int getHresult() {
        return hresult;
    }
}
