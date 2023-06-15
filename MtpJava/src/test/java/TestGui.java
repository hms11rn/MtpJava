import com.github.hms11rn.mtp.DeviceProperties;
import com.github.hms11rn.mtp.PortableDevice;
import com.github.hms11rn.mtp.PortableDeviceManager;

import javax.swing.*;
import java.awt.*;
import java.util.Map;

public class TestGui extends JFrame {
    PortableDeviceManager manager = PortableDeviceManager.getDeviceManager();

    JButton reload;
    JButton[] devices;
    JPanel buttonPanel;

    public TestGui() {
        init();
    }

    void init() {
        setPreferredSize(new Dimension(400, 400));
        pack();
        reload = new JButton("Refresh Device List");
        buttonPanel = new JPanel();
        reload.addActionListener(e -> {
            manager.refresh();
            buttonPanel.removeAll();
            updateButtons();
            SwingUtilities.updateComponentTreeUI(this);
        });
        updateButtons();
        reload.setBounds(30, getHeight() - 80, getWidth() - 70, 30);
        add(reload);
        buttonPanel.setBounds(20, 10, getWidth() - 60, (devices == null) ? 30 : devices.length * 30);
        add(buttonPanel);
        setLayout(null);

        setLocationRelativeTo(null);
        setVisible(true);
    }
    void updateButtons() {
        PortableDevice[] portableDevices = manager.getDevices();
        if (portableDevices.length == 0) {
            buttonPanel.setLayout(new GridLayout(1,1));
            buttonPanel.add(new JLabel("No Devices Where Found on current Device"));
            return;
        }
        devices = new JButton[portableDevices.length];
        buttonPanel.setLayout(new GridLayout(devices.length, 1));
        int i =0;
        for (PortableDevice p :  portableDevices) {
            devices[i] = new JButton(p.getFriendlyName());
            devices[i].addActionListener(e -> {
                setCurrentDevice(p);
                System.out.println(p.getFriendlyName() + " was pressed!");

            });
            buttonPanel.add(devices[i]);
            i++;
        }
    }

    public void setCurrentDevice(PortableDevice p) {
        remove(buttonPanel);
        remove(reload);
        SwingUtilities.updateComponentTreeUI(this);
        JPanel bPanel = new JPanel();
        bPanel.setBackground(Color.WHITE);
        bPanel.setBounds(0, 0, getWidth(), getHeight());
        bPanel.setLayout(null);
        JButton menu = new JButton("<- Main Menu");
        menu.setBounds(5, 5, 120, 30);
        menu.addActionListener(e -> {
            remove(bPanel);
            remove(menu);
            init();
            SwingUtilities.updateComponentTreeUI(this);
        });
        bPanel.add(menu);
        JButton properties = new JButton("Properties");
        properties.setBounds(130, 5, 100, 30);
        properties.addActionListener(e -> {
            openPropertyWindow(p);
        });
        bPanel.add(properties);
        add(bPanel);
    }

    public void openPropertyWindow(PortableDevice p) {
        p.open();
        Map<String, DeviceProperties.PropertyValue> map = p.getProperties();
        p.close();
    }
 }
