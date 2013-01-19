/****************************************************************/
// By Bill Hsu
// Shanghai University
// My Blog:        http://BillHsu.me
// jUART Project:  http://github.com/billhsu/jUART
// Created on:     2013-01-04
/****************************************************************/

/**********************************************************\

  Auto-generated jUARTAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "jUARTAPI.h"
#include "SerialAPI.h"

////////////////////////////////////////////////////////////////////////////
/// @fn jUARTAPI::jUARTAPI(const jUARTPtr& plugin, const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.
///         You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
////////////////////////////////////////////////////////////////////////////
jUARTAPI::jUARTAPI(const jUARTPtr& plugin, const FB::BrowserHostPtr& host) :
m_plugin(plugin), m_host(host)
{
    registerMethod("echo",      make_method(this, &jUARTAPI::echo));
    registerMethod("testEvent", make_method(this, &jUARTAPI::testEvent));

    registerProperty("Serial",  make_property(this, &jUARTAPI::get_Serial));

    // Read-write property
    registerProperty("testString",
        make_property(this,
        &jUARTAPI::get_testString,
        &jUARTAPI::set_testString));

    // Read-only property
    registerProperty("version",
        make_property(this,
        &jUARTAPI::get_version));

    m_Serial = boost::make_shared<SerialAPI>(m_host);
}

///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant jUARTAPI::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript.
///         Go ahead and change it. See what happens!
///////////////////////////////////////////////////////////////////////////////
FB::variant jUARTAPI::echo(const FB::variant& msg)
{
    static int n(0);
    //fire_echo("So far, you clicked this many times: ", n++);
    // return "foobar";
    return msg;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn jUARTPtr jUARTAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
jUARTPtr jUARTAPI::getPlugin()
{
    jUARTPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read/Write property testString
std::string jUARTAPI::get_testString()
{
    return m_testString;
}

void jUARTAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string jUARTAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void jUARTAPI::testEvent()
{
    fire_test();
}

boost::weak_ptr<SerialAPI> jUARTAPI::get_Serial()
{
    return m_Serial;
}