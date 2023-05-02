package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Map;

class PortableDeviceContentWin32 {

    final PortableDeviceWin32 device;
    protected PortableDeviceContentWin32(PortableDeviceWin32 device) {
        this.device = device;
    }
    protected PortableDeviceObject getObjectFromID(String id, String type) {
        if (type.equals("FUNCTIONAL_CATEGORY_STORAGE")) {
            return new PortableDeviceStorageObjectWin32(id, this);
        } else if (type.equals("CONTENT_TYPE_FOLDER"))
            return new PortableDeviceContainerObjectWin32(id, this);
        return new PortableDeviceObjectWin32(id,  this);
    }

    protected String createObject(File file, String parent) throws IOException {
        return device.addFileObjectN(file.getName(), parent, file, getFileType(file), "") ;
    }

    protected String createFolder(String name, String parent) {
        return device.addFolderObjectN(name, parent);
    }
    protected boolean delete(String id) {
        return device.deleteFileN(id, 0);
    }
    protected PortableDeviceObject[] getObjects(String containerId) {
        Map<String, String> objects;
        objects = device.getObjectsN(containerId);
        PortableDeviceObject[] retObjs = new PortableDeviceObject[objects.size()];
        int i = 0;
        for (String id : objects.keySet()) {
            retObjs[i] = getObjectFromID(id, objects.get(id));
            i++;
        }
        return retObjs;
    }

    private String getFileType(File file) throws IOException {
        String type = Files.probeContentType(file.toPath());
        if (type == null)
            type = "";

        if (type.matches("^image/.*")) {
            return PropertiesWin32.WPD_CONTENT_TYPE_IMAGE.toString();
        } else if (type.matches("^audio/.*")) {
            return PropertiesWin32.WPD_CONTENT_TYPE_AUDIO.toString();
        } else if (type.matches("^text/.*")) {
            return PropertiesWin32.WPD_CONTENT_TYPE_DOCUMENT.toString();
        } else if (type.matches("^video/.*")) {
           return PropertiesWin32.WPD_CONTENT_TYPE_VIDEO.toString();
        } else {
            return PropertiesWin32.WPD_CONTENT_TYPE_GENERIC_FILE.toString();
        }
    }

    /**
     * Jmtp lib
     * @param file
     * @return type of object
     * @throws IOException
     */
    private String getFileFormat(File file) throws IOException {
        String type = Files.probeContentType(file.toPath());
        if (type == null)
            type = "";

        if (type.matches("^image/.*")) {
            return PropertiesWin32.WPD_OBJECT_FORMAT_UNSPECIFIED.toString();
        } else if (type.matches("^audio/.*")) {
            if (type.matches(".*/m4[ab]$")) {
                return PropertiesWin32.WPD_OBJECT_FORMAT_M4A.toString();

            } else if (type.matches(".*/mp3$")) {
                return PropertiesWin32.WPD_OBJECT_FORMAT_MP3.toString();

            } else if (type.matches(".*/wav$")) {
                return PropertiesWin32.WPD_OBJECT_FORMAT_WAVE.toString();
            } else {
                return PropertiesWin32.WPD_OBJECT_FORMAT_AUDIBLE.toString();
            }
        } else if (type.matches("^text/.*")) {
            if (type.matches(".*/xml$")) {
                return PropertiesWin32.WPD_OBJECT_FORMAT_XML.toString();
            } else {
                return PropertiesWin32.WPD_OBJECT_FORMAT_TEXT.toString();
            }
        } else if (type.matches("^video/.*")) {
            if (type.matches(".*/MP4$")) {
                return PropertiesWin32.WPD_OBJECT_FORMAT_MP4.toString();
            } else {
                return PropertiesWin32.WPD_OBJECT_FORMAT_UNSPECIFIED.toString();
            }
        } else {
            return PropertiesWin32.WPD_OBJECT_FORMAT_UNSPECIFIED.toString();
        }
    }
    }


