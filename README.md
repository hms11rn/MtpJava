# Media Transfer Protocol Library for java

<b>MtpJava</b> is a Java library that provides a way to communicate with MTP devices using the [Windows Protocol Devices](https://learn.microsoft.com/en-us/windows/win32/windows-portable-devices) (WPD) API and Java Native Interface (JNI).

## Requirements
 * JDK Version 18 or higher
 * Windows Opreating System (Currently Linux and Mac aren't supported)
 * Windows Driver Kit (WDK) version 10 or higher
 
 ## Installation
 1. Download MtpJava.jar and add to your classpath
 2. Download MtpJava.dll
 3. In your VM Options add  ```-Djava.library.path=[Path to the directory you put MtpJava.dll]``` (No brackets) 

## Usage
To use this library you can use ```PortableDeviceManager.getDeviceManager()```. <br>
Once you obtained PortableDeviceManager you can use ```PortableDeviceManager#getDevices()``` to get an array of 
```PortableDevice```. <br>
The class PortableDevice has 3 methods that can be used without opening the connection with the device - ```getFriendlyName()```, ```getDescription()``` and ```getManufacture()```. <br>
Any other methods in the class require you to open the connections with the device via ```PortableDevice#open()```.

### Example
```Java
package ...;

import com.github.hms11rn.mtp.*;

class Test {

  public static void main(String[] args) {
      PortableDeviceManager mgr = PortableDeviceManager.getDeviceManager();
      IPortableDevice[] portableDeviceArray = mgr.getDevices();
      IPortableDevice device = IPortableDevice[0];
      String deviceName = device.getFriendlyName();
      String deviceManfuacture = device.getManufacture();
      String deviceDescription = device.getDescription();
      System.out.println("Name: " + deviceName);
      
      // This is really important, to access any other method in PortableDevice class you MUST call device.open(); 
      device.open();
      
      String firmwareVersion = device.getFirmwareVersion();
      
      // obtain root objects
      IPortableDeviceObject[] roots = device.getRootObjects();
      IPortableDeviceObject obj = roots[0];
      
      if (obj.isContainer()) {
            PortableDeviceContainerObject cObj = (PortableDeviceContainerObject) obj;
            IPortableDeviceObject[] childs = cObj.getChildObjects(); // Get child objects
            InputStream is = childs[0].getInputStream(); // NOTE: getInputStream does not work on a container object, this line is assuming childs[0] is not a PortableDeviceContainerObject
            // There are many more methods in PortableDeivceObject, you can take a look inside the class to see all available methods 
      }
  }
}
```

### Credits
I would like to thank the creator of the [JMtp](https://code.google.com/archive/p/jmtp/) Library for providing me with a basic understanding of how to connect WPD to Java using JNI.
ultimately  the reason why I decided to create my own library is because JMtp is somewhat outdated and does not have all of the features I require for an upcoming project.







