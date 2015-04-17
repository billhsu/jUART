[![jUART](https://github.com/billhsu/jUART/raw/master/doc/jUART_Logo.png)](http://github.com/billhsu/jUART/)

jUART, Cross platform browser plugin for serial port communication from JavaScript

[![Gitter](https://badges.gitter.im/Join Chat.svg)](https://gitter.im/billhsu/jUART?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

Digital Object Identifiers (DOI): [![citeDOI](https://zenodo.org/badge/4047/billhsu/jUART.png)](http://dx.doi.org/10.5281/zenodo.9999)

##Supported Platforms:
* **Browsers:** Chrome, Firefox, Safari, IE(IE version is not released yet)

* **OS:** Windows, Linux and Mac

##Install Plugin

###Windows:
Copy the /bin/Windows/npjUART.dll into your browser's plugin directory.

Take FireFox for example:
Copy `/bin/Windows/npjUART.dll` to `C:\Program Files (x86)\Mozilla Firefox\plugins`

For Windows 8, you need to register the DLL first.
You can copy the DLL under SYSTEM32(or SYSWOW for 64 bit systems).
After that there's no need to copy it to browser's folders.

###Linux:
Copy the ./bin/Linux/npjUART.so into your browser's plugin directory.

Take FireFox for example:

```
sudo cp npjUART.so ~/.mozilla/plugins/
```

###Mac:
Mac version is not released yet, I don't have a Mac to build and test the project. You need to build it yourself. Sorry :-(

##Usage
* `var ser = plugin().Serial;` Get a Serial object
* `ser.open("COMA");` Open a port
* `ser.set_option(baud, parity, csize, flow, stop);` Set port options

* * **baud:**       Baud rate

* * **parity:**     0->none, 1->odd, 2->even

* * **csize:**      5 6 7 8

* * **flow:**       0->none, 1->software, 2->hardware

* * **stop:**       0->one,  1->onepointfive, 2->two

* `ser.recv_callback(recv);` Bind callback function for recieve data.

* * 'recv' is a function in JavaScript,`function recv(bytes, size)`
* * 'bytes' are the data recieved, 'size' is the size of the bytes recieved

* `ser.send(char);` Send a byte to serial port

Here is an echo test example, which is contained in the /example directory.
```
<html>
  <head>
    <title>test page for object fbcontrol</title>
  </head>
  <script type="text/javascript">
    var ser;
    function plugin0()
    {
      return document.getElementById('plugin0');
    }
    plugin = plugin0;
        
    function recv(bytes, size)
    {
      for(var i=0;i<size;++i)
      {
        ser.send(bytes[i]);
      }
    }
        
    function pluginLoaded() 
    {
      ser = plugin().Serial;// Get a Serial object
      ser.open("COMA");// Open a port
      ser.set_option(115200,0,8,0,0);// Set port options 
      ser.recv_callback(recv); // Callback function for recieve data
    }

    function pluginValid()
    {
      if(plugin().valid){
        alert(plugin().echo("This plugin seems to be working!"));
      } else {
        alert("Plugin is not working :(");
      }
    }
  </script>
  <body onload="load()">
    <object id="plugin0" type="application/x-juart" width="0" height="0" >
      <param name="onload" value="pluginLoaded"  />
    </object>
    <h1>jUART Serial Port Echo Test</h1><br/>
    This test will echo the data you sent through serial port.
  </body>
</html>

```

##To Build
* 1. Install [FireBreath](http://www.firebreath.org)
* 2. Run `python fbgen.py` in firebreath-dev, please set "Plugin Name" to jUART
* 3. Goto firebreath-dev/projects, delete the jUART directory
* 4. Same in firebreath-dev/projects, run ``git clone git@github.com:billhsu/jUART.git``
* 5. **Windows:** `prep2008.cmd` (or `prep2005.cmd` / `prep2010.cmd`if you have VS2005/2010) **Linux:** `./prepmake.sh` **Mac:** `./prepmac.sh`
* 6. **Windows:** open build/Firebreath.xxx **Linux:**``cd build/`` then ``make``

##License
https://www.gnu.org/licenses/lgpl-2.1.html

##Author
**Bill Hsu**

+ http://BillHsu.me
+ http://twitter.com/1991bill
+ http://weibo.com/billhsu
