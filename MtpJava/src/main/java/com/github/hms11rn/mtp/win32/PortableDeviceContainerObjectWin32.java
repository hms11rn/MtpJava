package com.github.hms11rn.mtp.win32;

import com.github.hms11rn.mtp.content.PortableDeviceContainerObject;
import com.github.hms11rn.mtp.content.PortableDeviceFolderObject;
import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

public class PortableDeviceContainerObjectWin32 extends PortableDeviceObjectWin32 implements PortableDeviceContainerObject {
    protected PortableDeviceContainerObjectWin32(String id, PortableDeviceContentWin32 content) {
        super(id, content);
    }

    @Override
    public PortableDeviceObject[] getChildObjects() {
        return content.getObjects(id);
    }

    @Override
    public PortableDeviceObject addFileObject(File file) throws IOException {
        if (file.isDirectory())
            return createFolderObject(file.getName());
        return new PortableDeviceObjectWin32(content.createObject(file, id), content);
    }

    @Override
    public PortableDeviceObject addFileObject(InputStream is, String name) {
        // TODO implement adding file using an input stream
        return new PortableDeviceObjectWin32(content.addFileFromInputStream(name, id, is), content);
    }
    @Override
    public PortableDeviceObject addFileObject(InputStream is, String name, String mimeType) {
        // TODO implement adding file using an input stream
        return new PortableDeviceObjectWin32(content.addFileFromInputStream(name, id, is, mimeType), content);
    }

    @Override
    public PortableDeviceFolderObject createFolderObject(String name) {
        return new PortableDeviceFolderObjectWin32(content.createFolder(name, id), content);
    }

    @Override
    public void delete() {
        content.delete(id, 1);
    }

    @Override
    public void copy(String path) {
        File pathFile = new File(path);
        if (!pathFile.exists())
            throw new RuntimeException(new FileNotFoundException("File \"" + path +"\"" + "is not a valid file"));
        copyFolder(path);
    }

    @Override
    public InputStream getInputStream() {
        throw new UnsupportedOperationException("Container Objects do not have any resources attached");
    }

    private void copyFolder(String path) {
            PortableDeviceObject[] objects = getChildObjects();
            for (PortableDeviceObject obj : objects) {
                if (!(obj instanceof PortableDeviceContainerObject)) {
                    content.copyFile(obj.getId(), path + "\\" + obj.getOriginalFileName());
                } else {
                    String name = obj.getOriginalFileName();
                    File newDir = new File(path + "\\" + name);
                    newDir.mkdir();
                    obj.copy(newDir.getAbsolutePath());
                }
            }
        }

    }

