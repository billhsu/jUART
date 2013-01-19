#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for jUART
#
#\**********************************************************/

set(PLUGIN_NAME "jUART")
set(PLUGIN_PREFIX "JUART")
set(COMPANY_NAME "ShipengXu")

# ActiveX constants:
set(FBTYPELIB_NAME jUARTLib)
set(FBTYPELIB_DESC "jUART 1.0 Type Library")
set(IFBControl_DESC "jUART Control Interface")
set(FBControl_DESC "jUART Control Class")
set(IFBComJavascriptObject_DESC "jUART IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "jUART ComJavascriptObject Class")
set(IFBComEventSource_DESC "jUART IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 4cc6f707-689f-571b-b683-a9bee26b5075)
set(IFBControl_GUID a12272f3-f0aa-5cfe-a77f-74df0fd69cc1)
set(FBControl_GUID 8dbb56d7-b0c0-5927-b59b-7025d0694647)
set(IFBComJavascriptObject_GUID a3e83665-1117-5c62-b1c2-9ce06f82637d)
set(FBComJavascriptObject_GUID 26f4300f-c089-5f29-b8e7-ade448999758)
set(IFBComEventSource_GUID 3f9d0e8b-746b-5661-add0-bb5f2f72ebca)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 02cdaea1-eaa9-5fdc-bb8e-5085f5336565)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 5faace0b-0e7d-56b1-ab88-89106f37eb23)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "ShipengXu.jUART")
set(MOZILLA_PLUGINID "BillHsu.me/jUART")

# strings
set(FBSTRING_CompanyName "Shipeng Xu")
set(FBSTRING_PluginDescription "Serial Port for JavaScript")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2013 Shipeng Xu")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "jUART")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "jUART")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "jUART_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-juart")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
