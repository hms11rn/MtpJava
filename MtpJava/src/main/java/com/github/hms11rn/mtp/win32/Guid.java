package com.github.hms11rn.mtp.win32;

/**
 * Com interface Guid
 */
class Guid {
    String guid;
    int pid;
    public Guid(String guid, int pid) {
        this.guid = guid;
        this.pid = pid;
    }

    @Override
    public String toString() {
        return guid + pid;
    }


}
