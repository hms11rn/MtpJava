import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.Mtp;
import com.github.hms11rn.mtp.PortableDevice;
import com.github.hms11rn.mtp.PortableDeviceManager;
import com.github.hms11rn.mtp.content.PortableDeviceContainerObject;
import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.io.*;
import java.util.ArrayList;
import java.util.Map;

@SuppressWarnings("all") // Suppressing all warnings since this is a test class
public class Test {

    @org.junit.jupiter.api.Test
    static void test() throws IOException {
        Mtp.register();
        PortableDeviceManager mgr = PortableDeviceManager.getDeviceManager();
        PortableDevice pd = mgr.getDevices()[0];
        System.out.println("Friendly name: " + pd.getFriendlyName());
        System.out.println("Manufacture: " + pd.getManufacture());
        System.out.println("Description: " + pd.getDescription());
        pd.open();

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

        PortableDeviceContainerObject obj = (PortableDeviceContainerObject) pd.getRootObjects()[0];
        PortableDeviceContainerObject j = (PortableDeviceContainerObject) obj.getChildObjects()[0];
        System.out.println(j.getName());
        Map<String, DeviceProperties.PropertyValue> m1 = j.getProperties();
        for (int i = 0; i < m1.size(); i++) {
            System.out.print(new ArrayList(m1.keySet()).get(i) + " :: ");
            System.out.println(new ArrayList<>(m1.values()).get(i));
        }
        System.out.println("\r\n\r\n\r\n\r\n\r\n" + j.getName());
       // j.addFileObject(new File("C:\\Users\\hmsel\\Documents\\randomText2.txt"));
      //  j.addFileObject(new File("C:\\Users\\hmsel\\Documents\\randomText3.txt"));
        for (PortableDeviceObject j1 :  j.getChildObjects()) {
            if (j1.getName().equals("randomText2.txt")) {
               System.out.println(j1.delete());
       //         InputStream t = j1.getInputStream();
       //         BufferedReader r = new BufferedReader(new InputStreamReader(t));
       //         System.out.println(r.readLine());

            }
        }
    //    System.out.println(j.getName());
        //    System.out.println(j.getDateModified());
   //     j.copy("C:\\Users\\hmsel\\Documents\\aaaatest");
  //      j.createFolderObject("newFolder");
        pd.close();
    }
    public static void main(String[] args) throws IOException {
        test();
    }
}
