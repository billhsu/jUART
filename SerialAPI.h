/****************************************************************/
// By Bill Hsu
// Shanghai University
// My Blog:        http://BillHsu.me
// jUART Project:  http://github.com/billhsu/jUART
// Created on:     2013-01-09
/****************************************************************/

#ifndef H_SerialAPI
#define H_SerialAPI
#include <boost/bind.hpp> 
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/thread.hpp> 
#include <deque>
#include <boost/lexical_cast.hpp> 
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/filesystem.hpp>
#ifndef _WIN32
#include <fcntl.h>
#include <glob.h>
#include <sys/ioctl.h>
#endif
#include "JSAPIAuto.h"
#include "BrowserHost.h"


class SerialAPI: public FB::JSAPIAuto
{
public:
    SerialAPI(const FB::BrowserHostPtr& host);
    ~SerialAPI(void);

    // Open serial device. e.g. "COM1" in Windows or "/dev/ttyS0" in Linux
    bool open(std::string _device);

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn Serial::set_option()
    ///
    /// @brief  Set serial port opinions
    ///         parity:     0->none, 1->odd, 2->even
    ///         csize:      5 6 7 8
    ///         flow:       0->none, 1->software, 2->hardware
    ///         stop:       0->one,  1->onepointfive, 2->two
    ///////////////////////////////////////////////////////////////////////////////
    bool set_option(unsigned int baud, unsigned int parity = 0,
        unsigned int csize = 8, unsigned int flow = 0, unsigned int stop = 0);

	void sendmulti(const FB::JSObjectPtr& msg, int length)
	{
		unsigned char *message = new unsigned char[length];
		FB::variant v;
		for(int i = 0; i < length; i++)
		{
			v = msg->GetProperty(i);
			message[i] = v.convert_cast<unsigned char>();
		}
		io.post(boost::bind(&SerialAPI::do_multi_send, this, (unsigned char *)message, length));
	}

    // Send a byte to serial port
    void send(const unsigned char msg)
    {
        io.post(boost::bind(&SerialAPI::do_send, this, msg)); 
    }
    bool sendtest()
    {
        io.post(boost::bind(&SerialAPI::do_send, this, 'a'));
        return true;
    }

	void DetectSerialPorts(std::vector<boost::filesystem::path::string_type>& list)
	{
#if defined(_WIN32) || defined(_WIN64)
		for(int i=1; i<=255; i++)	
		{
			wchar_t buff[100];
			wsprintf(buff, TEXT("COM%d"), i);
			std::wstring wstrPort = buff;
			//strPort.Format("COM%d",i);
	
			DWORD dwSize = 0;
			LPCOMMCONFIG lpCC = (LPCOMMCONFIG) new BYTE[1];
			BOOL ret = GetDefaultCommConfig(wstrPort.c_str(), lpCC, &dwSize);
			delete [] lpCC;	

			lpCC = (LPCOMMCONFIG) new BYTE[dwSize];
			ret = GetDefaultCommConfig(wstrPort.c_str(), lpCC, &dwSize);
		
			if(ret)
				list.push_back(wstrPort);
		
			delete [] lpCC;
		}
#elif __APPLE__
		glob_t globs;
		glob("/dev/tty.*", GLOB_NOSORT, NULL, &globs);
		for (char ** portp = globs.gl_pathv; *portp != NULL; ++portp) {
			list.push_back(*portp);
		}
		globfree(&globs);
#else
		// just return all ttys with no window size for now
		glob_t globs;
		glob("/dev/tty*", GLOB_NOSORT, NULL, &globs);
		for (char ** portp = globs.gl_pathv; *portp != NULL; ++portp) {
			struct winsize ws = {0,0};
			int fd = ::open(*portp, O_RDWR | O_NOCTTY | O_NDELAY);
			if (fd == -1) continue;
			ioctl(fd, TIOCGWINSZ, &ws);
			if (ws.ws_row == 0 && ws.ws_col == 0)
				list.push_back(*portp);
			::close(fd);
		}
		globfree(&globs);
#endif
	}

	FB::VariantList getports() {
		std::vector<boost::filesystem::path::string_type> valVec;
		DetectSerialPorts(valVec);
		return FB::make_variant_list(valVec);
	}

    bool is_open()
    {
        return serial.is_open();
    }

    void close()
    {
        // check if io thread is not running yet
        if(m_thread.get_id()==boost::thread::id())
        {
            do_close(boost::system::error_code());
        }
        else
        {
            io.post(boost::bind(&SerialAPI::do_close, this, boost::system::error_code()));
            m_thread.join();
        }
    }

    void recv_callback(const FB::JSObjectPtr& callback);
    void err_callback(const FB::JSObjectPtr& callback);



private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;

    std::string device;
    static const int max_buffer_length = 512;

    unsigned char recv_msg[max_buffer_length];
    std::deque<unsigned char> send_msg;

    FB::BrowserHostPtr m_host;
    FB::JSObjectPtr m_recv_callback;
    FB::JSObjectPtr m_err_callback;

    boost::thread m_thread;

    void recv_start(void);
    void recv_complete(const boost::system::error_code& error, size_t bytes_transferred);
	void do_multi_send(const unsigned char msg[], const int length);
    void send_multi_start(int length);
    void send_multi_complete(const boost::system::error_code& error);
    void do_send(const unsigned char msg);
    void send_start(void);
    void send_complete(const boost::system::error_code& error);

    void do_close(const boost::system::error_code& error);
};

#endif //H_SerialAPI
