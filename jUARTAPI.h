/****************************************************************/
// By Bill Hsu
// Shanghai University
// My Blog:        http://BillHsu.me
// jUART Project:  http://github.com/billhsu/jUART
// Created on:     2013-01-04
/****************************************************************/

/**********************************************************\

  Auto-generated jUARTAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "jUART.h"
#include "FBPointers.h"

#ifndef H_jUARTAPI
#define H_jUARTAPI


FB_FORWARD_PTR(SerialAPI);

class jUARTAPI : public FB::JSAPIAuto
{
public:
    //
    jUARTAPI(const jUARTPtr& plugin, const FB::BrowserHostPtr& host);

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn jUARTAPI::~jUARTAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~jUARTAPI() {};
    jUARTPtr getPlugin();
    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Event helpers
    FB_JSAPI_EVENT(test, 0, ());
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));

    // Method test-event
    void testEvent();
    boost::weak_ptr<SerialAPI> get_Serial();

private:
    jUARTWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;

    SerialAPIPtr m_Serial;
};

#endif // H_jUARTAPI

