[![jUART](https://github.com/billhsu/jUART/raw/master/doc/jUART_Logo.png)](http://github.com/billhsu/jUART/)

jUART, Cross platform browser plugin for serial port communication from JavaScript

##Supported Platforms:
* **Browsers:** Chrome, Firefox, Safari, IE(IE version not released yet)

* **OS:** Windows, Linux and Mac

##Install Plugin

###Windows:
Copy the /bin/Windows/npjUART.dll into your browser's plugin directory.

Take FireFox for example:

###Linux:
Copy the ./bin/Linux/npjUART.so into your browser's plugin directory.

Take FireFox for example:

```
sudo cp npjUART.so ~/.mozilla/plugins/
```

Restart FireFox

###Mac:
Mac version not released yet, I don't have a Mac to build and test the project. Sorry :-(

##To Test

##To Build
* 1. Install FireBreath
* 2. Run `python fbgen.py`, please set "Plugin Name" to jUART
* 3. Goto firebreath-dev/projects, delete the jUART directory
* 4. Same in firebreath-dev/projects, run ``git clone git@github.com:billhsu/jUART.git``
* 5. **Windows:**: `prep2008.cmd` (or `prep2005.cmd` / `prep2010.cmd`if you have VS2005/2010) **Linux:**: `./prepmake.sh` **Mac:**: `./prepmac.sh`
* 6. **Windows:**: open build/Firebreath.xxx **Linux:**``cd build/`` then ``make``
