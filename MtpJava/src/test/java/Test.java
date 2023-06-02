import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.PortableDevice;
import com.github.hms11rn.mtp.PortableDeviceManager;
import com.github.hms11rn.mtp.content.PortableDeviceContainerObject;
import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.io.*;
import java.util.ArrayList;
import java.util.Map;

@SuppressWarnings("all") // Suppressing all warnings since this is a test class
// TODO write proper tests
public class Test {

    @org.junit.jupiter.api.Test
    static void test() throws IOException {
        PortableDeviceManager mgr = PortableDeviceManager.getDeviceManager();
        PortableDevice pd = mgr.getDevices()[0];
        System.out.println("Friendly name: " + pd.getFriendlyName());
        System.out.println("Manufacture: " + pd.getManufacture());
        System.out.println("Description: " + pd.getDescription());
        pd.open(); // potential resource leak
        System.out.println("Opened");
        Map<String, DeviceProperties.PropertyValue> m = pd.getProperties();
        for (int i = 0; i < m.size(); i++) {
            System.out.print(new ArrayList(m.keySet()).get(i) + " :: ");
            System.out.println(new ArrayList<>(m.values()).get(i));
        }

        //
        System.out.println(pd.getSerialNumber());
        System.out.println(pd.getFirmwareVersion());
        System.out.println(pd.getPowerSource());
        System.out.println(pd.getPowerLevel());
        System.out.println(pd.getProtocol());
        System.out.println(pd.IsNonConsumableSupported());
        System.out.println(pd.getSyncPartner());

        pd.reloadProperties();
        System.out.println(pd.getPowerSource());
        pd.close();
        pd.open();
        PortableDeviceContainerObject obj = (PortableDeviceContainerObject) pd.getRootObjects()[0];
        PortableDeviceContainerObject j = (PortableDeviceContainerObject) obj.getChildObjects()[0];



        System.out.println(j.getName());
        Map<String, DeviceProperties.PropertyValue> m1 = j.getProperties();
        for (int i = 0; i < m1.size(); i++) {
            System.out.print(new ArrayList(m1.keySet()).get(i) + " :: ");
            System.out.println(new ArrayList<>(m1.values()).get(i));
        }
        System.out.println("\r\n\r\n\r\n\r\n\r\n" + j.getName());
        try {
            j.addFileObject(new File("C:\\Users\\hmsel\\Documents\\randomText2.txt"));
        } catch (Exception e) {

        }
        //  j.addFileObject(new File("C:\\Users\\hmsel\\Documents\\randomText3.txt"));

        for (PortableDeviceObject j1 :  j.getChildObjects()) {

            if (j1.getName().equals("randomText2.txt")) {
                pd.setOutputStreamWriteMethod(true);
                OutputStream s = j1.getOutputStream();
                BufferedWriter br = new BufferedWriter(new OutputStreamWriter(s));
                br.write(" : ayy");
                br.flush();

            }
        }
        for (PortableDeviceObject e : j.getChildObjects()) {
            if (e.getName().equals("name")) {
                System.out.println("Found name object");
                if (e.isContainer())
                    System.out.println(e.getName() + " is a container object");
                PortableDeviceContainerObject e1 = (PortableDeviceContainerObject) e;
                e.copy("C:\\Users\\Test\\FolderToCopy"); // this is going to copy recursively
            }
        }
        pd.close();
        System.out.println("Closed");
        pd.open();
        System.out.println("Opened");

    //    System.out.println(j.getName());
        //    System.out.println(j.getDateModified());
   //     j.copy("C:\\Users\\hmsel\\Documents\\aaaatest");
  //      j.createFolderObject("newFolder");
        pd.close();
    }
    public static void main(String[] args) throws IOException {
        test();
    }

    /*
     * to replicate bug, disconnect cable, reconnect and run the program twice TODO
     */
}