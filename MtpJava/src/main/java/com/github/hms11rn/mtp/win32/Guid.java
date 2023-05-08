package com.github.hms11rn.mtp.win32;

/**
 * Com interface GUID
 */
class Guid {
    final String guid;
    final int pid;

    /**
     * @param guid unique Guid
     * @param pid pid
     */
    public Guid(String guid, int pid) {
        this.guid = guid;
        this.pid = pid;
    }

    /**
     * Guid with no pid
     * @param guid unique Guid
     */
    public Guid(String guid) {
        this.guid = guid;
        this.pid = -1; // -1 is no pid
    }

    /**
     * converts guid type to String<br>
     * if there is no pid (pid == -1) it is going to return just the guid string
     * @return guid with pid
     */
    @Override
    public String toString() {
        if (pid == -1)
            return guid;
        return guid + pid;
    }


}
