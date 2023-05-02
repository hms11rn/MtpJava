import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.Mtp;
import com.github.hms11rn.mtp.PortableDevice;
import com.github.hms11rn.mtp.PortableDeviceManager;
import com.github.hms11rn.mtp.content.PortableDeviceContainerObject;
import com.github.hms11rn.mtp.content.PortableDeviceObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;

@SuppressWarnings("all") // Suppressing all warnings since this is a test class
public class Test {

    static void test() {
        Mtp.register();
        PortableDeviceManager mgr = PortableDeviceManager.getDeviceManager();
        PortableDevice pd = mgr.getDevices()[0];
        System.out.println("Friendly name: " + pd.getFriendlyName());
        System.out.println("Manufacture: " + pd.getManufacture());
        System.out.println("Description: " + pd.getDescription());
        Map<String, DeviceProperties.PropertyValue> m = pd.getProperties();
        for (int i = 0; i < m.size(); i++) {
            System.out.print(new ArrayList(m.keySet()).get(i) + " :: ");
            System.out.println(new ArrayList<>(m.values()).get(i));
        }

        //
        pd.open();
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
     //    j.addFileObject(new File("C:\\Users\\*******\\Documents\\randomText2.txt"));
       //  j.addFileObject(new File("C:\\Users\\hmsel\\Documents\\randomText3.txt"));
        for (PortableDeviceObject j1 :  j.getChildObjects()) {
            if (j1.getName().equals("randomText3.txt")) {
                System.out.println(j1.getFormat());
                //    j1.delete();
            }
        }
        System.out.println(j.getName());
        System.out.println(j.getDateModified());
     //   j.createFolderObject("newFolder");
    }
    public static void main(String[] args) throws IOException {
        test();
    }
}
