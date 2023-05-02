package com.github.hms11rn.mtp.win32;

class PropertiesWin32 {

    protected static Guid WPD_DEVICE_MANUFACTURER = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 7);
    protected static Guid WPD_DEVICE_FIRMWARE_VERSION = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 9);
    protected static Guid WPD_DEVICE_POWER_SOURCE = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 5);
    protected static Guid WPD_DEVICE_SERIAL_NUMBER = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 3);
    protected static Guid WPD_DEVICE_POWER_LEVEL = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 4);
    protected static Guid WPD_DEVICE_PROTOCOL = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 6);
    protected static Guid WPD_DEVICE_SUPPORTS_NON_CONSUMABLE = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}",10);
    protected static Guid WPD_DEVICE_SYNC_PARTNER = new Guid("{26D4979A-E643-4626-9E2B-736DC0C92FDC}", 2);

    // object
    protected static Guid WPD_OBJECT_ID = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 2);
    protected static Guid WPD_OBJECT_CONTAINER_FUNCTIONAL_OBJECT_ID = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 23);
    protected static Guid WPD_OBJECT_PERSISTENT_UNIQUE_ID = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 5);
    protected static Guid WPD_OBJECT_NAME = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 4);
    protected static Guid WPD_OBJECT_CONTENT_TYPE = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 7);
    protected static Guid WPD_OBJECT_CAN_DELETE = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 26);
    protected static Guid WPD_OBJECT_ORIGINAL_FILE_NAME = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 12); // TODO
    protected static Guid WPD_OBJECT_PARENT_ID = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 3);
    // Date
    protected static Guid WPD_OBJECT_DATE_CREATED = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 18);
    protected static Guid WPD_OBJECT_DATE_MODIFIED = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 19);
    protected static Guid WPD_OBJECT_DATE_AUTHORED = new Guid("{EF6B490D-5CD8-437A-AFFC-DA8B60EE4A3C}", 20);


    // functional storage object
    protected static Guid WPD_STORAGE_FILE_SYSTEM_TYPE = new Guid("{01A3057A-74D6-4E80-BEA7-DC4C212CE50A}", 3);
    protected static Guid WPD_STORAGE_DESCRIPTION = new Guid("{01A3057A-74D6-4E80-BEA7-DC4C212CE50A}", 7);
    protected static Guid WPD_STORAGE_SERIAL_NUMBER = new Guid("{01A3057A-74D6-4E80-BEA7-DC4C212CE50A}", 8);
    protected static Guid WPD_STORAGE_CAPACITY = new Guid("{01A3057A-74D6-4E80-BEA7-DC4C212CE50A}", 4);
    protected static Guid WPD_STORAGE_CAPACITY_IN_OBJECTS = new Guid("{01A3057A-74D6-4E80-BEA7-DC4C212CE50A}", 10);
    protected static Guid WPD_STORAGE_FREE_SPACE_IN_BYTES = new Guid("{01A3057A-74D6-4E80-BEA7-DC4C212CE50A}", 5);
    protected static Guid WPD_STORAGE_FREE_SPACE_IN_OBJECTS = new Guid("{01A3057A-74D6-4E80-BEA7-DC4C212CE50A}", 6);
    protected static Guid WPD_STORAGE_MAX_OBJECT_SIZE = new Guid("{01A3057A-74D6-4E80-BEA7-DC4C212CE50A}", 9);

    //============= Portable Device Content Type =============\\
    protected static Guid WPD_CONTENT_TYPE_IMAGE = new Guid("{EF2107D5-A52A-4243-A26B-62D4176D7603}");
    protected static Guid WPD_CONTENT_TYPE_VIDEO = new Guid("{9261B03C-3D78-4519-85E3-02C5E1F50BB9}");
    protected static Guid WPD_CONTENT_TYPE_AUDIO = new Guid("{4AD2C85E-5E2D-45E5-8864-4F229E3C6CF0}");
    protected static Guid WPD_CONTENT_TYPE_DOCUMENT = new Guid("{680ADF52-950A-4041-9B41-65E393648155}");
    protected static Guid WPD_CONTENT_TYPE_GENERIC_FILE = new Guid("{0085E0A6-8D34-45D7-BC5C-447E59C73D48}");
    protected static Guid WPD_CONTENT_TYPE_FOLDER = new Guid("{27E2E392-A111-48E0-AB0C-E17705A05F85}");
    //============= Portable Device Content Format =============\\
    protected static Guid WPD_OBJECT_FORMAT_UNSPECIFIED = new Guid("{30000000-AE6C-4804-98BA-C57B46965FE7}");
    protected static Guid WPD_OBJECT_FORMAT_M4A = new Guid("{30ABA7AC-6FFD-4C23-A359-3E9B52F3F1C8}");
    protected static Guid WPD_OBJECT_FORMAT_MP3 = new Guid("{30090000-AE6C-4804-98BA-C57B46965FE7}");

    protected static Guid WPD_OBJECT_FORMAT_WAVE = new Guid("{30080000-AE6C-4804-98BA-C57B46965FE7}");
    protected static Guid WPD_OBJECT_FORMAT_AUDIBLE = new Guid("{B9040000-AE6C-4804-98BA-C57B46965FE7}");

    protected static Guid WPD_OBJECT_FORMAT_XML = new Guid("{BA820000-AE6C-4804-98BA-C57B46965FE7}");
    protected static Guid WPD_OBJECT_FORMAT_TEXT = new Guid("{30040000-AE6C-4804-98BA-C57B46965FE7}");
    protected static Guid WPD_OBJECT_FORMAT_MP4 = new Guid("{B9820000-AE6C-4804-98BA-C57B46965FE7}");




    protected static String getGuid(String name) {
        if (name.equals("WPD_DEVICE_MANUFACTURER"))
            return WPD_DEVICE_MANUFACTURER.toString();
        if (name.equals("WPD_DEVICE_FIRMWARE_VERSION"))
            return WPD_DEVICE_SERIAL_NUMBER.toString();
        if (name.equals("WPD_DEVICE_POWER_SOURCE"))
            return WPD_DEVICE_POWER_SOURCE.toString();
        if (name.equals("WPD_DEVICE_SERIAL_NUMBER"))
            return WPD_DEVICE_FIRMWARE_VERSION.toString();
        if (name.equals("WPD_DEVICE_POWER_LEVEL"))
            return WPD_DEVICE_POWER_LEVEL.toString();
        if (name.equals("WPD_DEVICE_PROTOCOL"))
            return WPD_DEVICE_PROTOCOL.toString();
        if (name.equals("WPD_DEVICE_SUPPORTS_NON_CONSUMABLE"))
            return WPD_DEVICE_SUPPORTS_NON_CONSUMABLE.toString();
        if (name.equals("WPD_DEVICE_SYNC_PARTNER"))
            return WPD_DEVICE_SYNC_PARTNER.toString();

        // Portable device Object information
        if (name.equals("WPD_OBJECT_CONTENT_TYPE"))
            return WPD_OBJECT_CONTENT_TYPE.toString();
        if (name.equals(("WPD_OBJECT_PERSISTENT_UNIQUE_ID")))
            return WPD_OBJECT_PERSISTENT_UNIQUE_ID.toString();
        if (name.equals("WPD_OBJECT_CONTAINER_FUNCTIONAL_OBJECT_ID"))
            return WPD_OBJECT_CONTAINER_FUNCTIONAL_OBJECT_ID.toString();
        if (name.equals("WPD_OBJECT_NAME"))
            return WPD_OBJECT_NAME.toString();
        if (name.equals("WPD_OBJECT_ID"))
            return WPD_OBJECT_ID.toString();
        if (name.equals("WPD_OBJECT_CAN_DELETE"))
            return WPD_OBJECT_CAN_DELETE.toString();
        // TODO implement in DeviceProperties
        if (name.equals("WPD_OBJECT_PARENT_ID"))
            return WPD_OBJECT_PARENT_ID.toString();
        if (name.equals("WPD_OBJECT_ORIGINAL_FILE_NAME"))
            return WPD_OBJECT_ORIGINAL_FILE_NAME.toString();


        if (name.equals("WPD_STORAGE_FILE_SYSTEM_TYPE"))
            return WPD_STORAGE_FILE_SYSTEM_TYPE.toString();
        if (name.equals("WPD_STORAGE_DESCRIPTION"))
            return WPD_STORAGE_DESCRIPTION.toString();
        if (name.equals("WPD_STORAGE_SERIAL_NUMBER"))
            return WPD_STORAGE_SERIAL_NUMBER.toString();
        if (name.equals("WPD_STORAGE_CAPACITY"))
            return WPD_STORAGE_CAPACITY.toString();
        if (name.equals("WPD_STORAGE_CAPACITY_IN_OBJECTS"))
            return WPD_STORAGE_CAPACITY_IN_OBJECTS.toString();
        if (name.equals("WPD_STORAGE_FREE_SPACE_IN_BYTES"))
            return WPD_STORAGE_FREE_SPACE_IN_BYTES.toString();
        if (name.equals("WPD_STORAGE_FREE_SPACE_IN_OBJECTS"))
            return WPD_STORAGE_FREE_SPACE_IN_OBJECTS.toString();
        if (name.equals("WPD_STORAGE_MAX_OBJECT_SIZE"))
            return WPD_STORAGE_MAX_OBJECT_SIZE.toString();
        return null;
    }
}

/*
TODO
WPD_OBJECT_FORMAT
 */