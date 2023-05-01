package com.github.hms11rn.mtp.content;

import java.math.BigInteger;

public interface PortableDeviceStorageObject extends PortableDeviceObject {

    // TODO function interface
    String getFileSystemType();
    String getDescription();
    String getSerialNumber();
    BigInteger getCapacity();
    BigInteger getCapacityInObjects();
    BigInteger getFreeSpace() ;
    BigInteger getFreeSpaceInObjects();
    BigInteger getMaximumObjectSize();


    }
