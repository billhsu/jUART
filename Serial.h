#ifndef H_Serial
#define H_Serial
#include "asio.hpp"

class Serial
{
public:
    Serial(std::string port, unsigned int baud_rate)
        : io(), serial(io,port)
    {
        serial.set_option(asio::serial_port_base::baud_rate(baud_rate));
    }
    ~Serial(void);
private:
    asio::io_service io;
    asio::serial_port serial;
};

#endif //H_Serial