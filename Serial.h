#ifndef H_Serial
#define H_Serial
#include "asio.hpp"

class Serial: private boost::noncopyable
{
public:
    Serial()
        : io(), serial(io)
    {
        
    }
    ~Serial(void);
private:
    asio::io_service io;
    asio::serial_port serial;
};

#endif //H_Serial