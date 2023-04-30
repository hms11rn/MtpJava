package com.github.hms11rn.mtp.content;

import java.math.BigInteger;

public interface PortableDeviceFunctionalStorageObject extends PortableDeviceObject {

    // TODO function interface
    String getFileSystemType();
    String getDescription();
    String getSerialNumber();
    BigInteger getCapacity(); // TODO figure out why BigInteger
    BigInteger getCapacityInObjects();
    BigInteger getFreeSpace() ;
    BigInteger getFreeSpaceInObjects();
    BigInteger getMaximumObjectSize();


    }
