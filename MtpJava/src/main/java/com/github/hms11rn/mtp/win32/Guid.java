package com.github.hms11rn.mtp.win32;

/**
 * Com interface Guid
 */
class Guid {
    final String guid;
    final int pid;
    public Guid(String guid, int pid) {
        this.guid = guid;
        this.pid = pid;
    }

    public Guid(String guid) {
        this.guid = guid;
        this.pid = -1;
    }
    @Override
    public String toString() {
        if (pid == -1)
            return guid;
        return guid + pid;
    }


}
