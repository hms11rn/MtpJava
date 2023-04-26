import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.Mtp;
import com.github.hms11rn.mtp.PortableDevice;
import com.github.hms11rn.mtp.PortableDeviceManager;

import java.util.ArrayList;
import java.util.Map;

public class Test {

    public static void main(String[] args) {
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

        System.out.println(pd.getSerialNumber());
        System.out.println(pd.getFirmwareVersion());
        System.out.println(pd.getPowerSource());
        System.out.println(pd.getPowerLevel());
        System.out.println(pd.getProtocol());
        System.out.println(pd.IsNonConsumableSupported());
        System.out.println(pd.getSyncPartner());

    }
}
