/****************************************************************/
// By Bill Hsu
// Shanghai University
// My Blog:        http://BillHsu.me
// jUART Project:  http://BillHsu.github.com/jUART/
// Created on:     2013-01-09
/****************************************************************/

#ifndef H_Serial
#define H_Serial
#include "asio.hpp"

class Serial: private boost::noncopyable
{
public:
    Serial() : io(), serial(io)
    {
        
    }
    ~Serial(void)
    {

    }

    //Open serial device. e.g. "COM1" in Windows or "/dev/ttyS0" in Linux
    bool open(std::string _device)
    {
        serial.open(device);
        if(serial.is_open())device = _device;
        return serial.is_open();
    }

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

private:
    asio::io_service io;
    asio::serial_port serial;

    std::string device;
    static const int max_buffer_length = 512;
};

#endif //H_Serial