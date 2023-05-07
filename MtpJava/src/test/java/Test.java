import com.github.hms11rn.mtp.*;
import com.github.hms11rn.mtp.content.PortableDeviceContainerObject;
import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.util.ArrayList;
import java.util.Map;

@SuppressWarnings("all") // Suppressing all warnings since this is a test class
public class Test {

    @org.junit.jupiter.api.Test
    static void test() {

        Mtp.register();
        try {
            PortableDeviceManager mgr = PortableDeviceManager.getDeviceManager();
        } catch (ComException e) {
            System.out.println("Error");
        }
        if (true)
            return;
        PortableDevice pd = null;
        System.out.println("Friendly name: " + pd.getFriendlyName());
        System.out.println("Manufacture: " + pd.getManufacture());
        System.out.println("Description: " + pd.getDescription());
        pd.open();
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

        PortableDeviceContainerObject obj = (PortableDeviceContainerObject) pd.getRootObjects()[0];
        PortableDeviceContainerObject j = (PortableDeviceContainerObject) obj.getChildObjects()[0];
        System.out.println(j.getName());
        Map<String, DeviceProperties.PropertyValue> m1 = j.getProperties();
        for (int i = 0; i < m1.size(); i++) {
            System.out.print(new ArrayList(m1.keySet()).get(i) + " :: ");
            System.out.println(new ArrayList<>(m1.values()).get(i));
        }
        System.out.println("\r\n\r\n\r\n\r\n\r\n" + j.getName());
    //   j.addFileObject(new File("C:\\Users\\hmsel\\Documents\\randomText2.txt"));
        //  j.addFileObject(new File("C:\\Users\\hmsel\\Documents\\randomText3.txt"));
        for (PortableDeviceObject j1 :  j.getChildObjects()) {
            if (j1.getName().equals("randomText2.txt")) {
                j1.rename("randomText3.txt");
                //         InputStream t = j1.getInputStream();
                //         BufferedReader r = new BufferedReader(new InputStreamReader(t));
                //         System.out.println(r.readLine());
                j1.rename("randomText4.txt");

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
    public static void main(String[] args) {
        System.out.println("Pre started");
        test();
    }
    /*
     * to replicate bug, disconnect cable, reconnect and run the program twice TODO
     */
}
