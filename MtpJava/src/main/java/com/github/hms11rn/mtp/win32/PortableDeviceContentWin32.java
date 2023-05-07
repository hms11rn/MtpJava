package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
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
        String type = probeContentType(file);
        return device.addFileObjectN(file.getName(), parent, file, getFileType(type), getFileFormat(type));
    }
    protected String addFileFromInputStream(String name, String parentID, InputStream inStream) {

        return device.addFileFromInputStreamN(name, parentID, inStream, PropertiesWin32.WPD_CONTENT_TYPE_DOCUMENT.toString(),
                        PropertiesWin32.WPD_OBJECT_FORMAT_UNSPECIFIED.toString());
    }

    /**
     * Use {@link Files#probeContentType(Path)} to obtain mime  of file,
     * or a library like Apache Tika
     * @return newly craeted object ID
     */
    protected String addFileFromInputStream(String name, String parentID, InputStream inStream, String mimeType) {
        String type = getFileType(mimeType);
        String format = getFileFormat(mimeType);
        return device.addFileFromInputStreamN(name, parentID, inStream, type, format);
    }
    protected String createFolder(String name, String parent) {
        return device.addFolderObjectN(name, parent);
    }
    protected void copyFile(String id, String path) {
        device.copyFileN(id, path);
    }

    protected HashMap<String, Boolean> b = new HashMap<>();

    /**
     *  There is a bug with WPD Api that causes weird hanging, TODO attempt to fix it
     */
    protected boolean delete(String id, int recursive) {
      boolean did =  device.deleteFileN(id, recursive);
      b.put(id, did);
      return false;
    }
    protected List<String> getObjectsIDs(String id) {
        Map<String, String> objectIDs;
        objectIDs = device.getObjectsN(id);
        return new ArrayList<>(objectIDs.keySet());
    } // TODO implement getObjectIDs
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

    protected void rename(String id, String newName) {
        device.updatePropertyN(id, PropertiesWin32.WPD_OBJECT_NAME.guid, PropertiesWin32.WPD_OBJECT_NAME.pid, newName);
        device.updatePropertyN(id, PropertiesWin32.WPD_OBJECT_ORIGINAL_FILE_NAME.guid, PropertiesWin32.WPD_OBJECT_ORIGINAL_FILE_NAME.pid, newName);
    }

    protected byte[] getBytes(String id) {
        return device.getBytesN(id);
    }

    private String getFileType(String type) {
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
     * @param type Files.probeContentType()
     * @return type of object
     */
    private String getFileFormat(String type) {
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

    /**
     * Single method to probe content type to avoid probing the content twice for both file format and file type
     */
    private String probeContentType(File file) throws IOException {

        return Files.probeContentType(file.toPath());
    }
    }


