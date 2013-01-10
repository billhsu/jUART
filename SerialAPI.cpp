/****************************************************************/
// By Bill Hsu
// Shanghai University
// My Blog:        http://BillHsu.me
// jUART Project:  http://BillHsu.github.com/jUART/
// Created on:     2013-01-09
/****************************************************************/

#include "SerialAPI.h"
#include <boost/thread.hpp> 

SerialAPI::SerialAPI(const FB::BrowserHostPtr& host) : m_host(host),io(), serial(io)
{
    boost::thread m_thread(boost::bind(&boost::asio::io_service::run, &io)); 
}

SerialAPI::~SerialAPI(void)
{
    m_thread.interrupt();
    m_thread.join();
}

bool SerialAPI::open(std::string _device)
{
    serial.open(device);
    if(serial.is_open())device = _device;
    return serial.is_open();
}

bool SerialAPI::set_option(unsigned int baud, unsigned int parity,
    unsigned int csize, unsigned int flow, unsigned int stop)
{
    if(!serial.is_open())   return false;

    boost::asio::serial_port_base::baud_rate opt_baud(baud);
    boost::asio::serial_port_base::parity opt_parity(static_cast<boost::asio::serial_port_base::parity::type>(parity));
    boost::asio::serial_port_base::character_size opt_csize(csize);
    boost::asio::serial_port_base::flow_control opt_flow(static_cast<boost::asio::serial_port_base::flow_control::type>(flow));
    boost::asio::serial_port_base::stop_bits opt_stop(static_cast<boost::asio::serial_port_base::stop_bits::type>(stop));

    serial.set_option(opt_baud);
    serial.set_option(opt_parity);
    serial.set_option(opt_csize);
    serial.set_option(opt_flow);
    serial.set_option(opt_stop);
    recv_start();

    return true;
}

void SerialAPI::recv_start(void) 
{ // Start an asynchronous read and call read_complete when it completes or fails 
    serial.async_read_some(boost::asio::buffer(recv_msg, max_buffer_length), 
        boost::bind(&SerialAPI::recv_complete, 
        this, 
        boost::asio::placeholders::error, 
        boost::asio::placeholders::bytes_transferred)); 
}

void SerialAPI::recv_complete(const boost::system::error_code& error, size_t bytes_transferred) 
{ // the asynchronous read operation has now completed or failed and returned an error 
    if (!error) 
    { // read completed, so process the data 
        //cout.write(recv_msg, bytes_transferred); // echo to standard output 
        recv_start(); // start waiting for another asynchronous read again 
    } 
    else 
        do_close(error); 
} 

void SerialAPI::do_send(const char msg) 
{
    bool write_in_progress = !send_msg.empty(); // is there anything currently being written? 
    send_msg.push_back(msg); // store in write buffer 
    if (!write_in_progress) // if nothing is currently being written, then start 
        send_start(); 
} 

void SerialAPI::send_start(void)
{ // Start an asynchronous write and call write_complete when it completes or fails 
    boost::asio::async_write(serial, 
        boost::asio::buffer(&send_msg.front(), 1), 
        boost::bind(&SerialAPI::send_complete, 
        this, 
        boost::asio::placeholders::error)); 
} 

void SerialAPI::send_complete(const boost::system::error_code& error) 
{ // the asynchronous read operation has now completed or failed and returned an error 
    if (!error) 
    { // write completed, so send next write data 
        send_msg.pop_front(); // remove the completed data 
        if (!send_msg.empty()) // if there is anthing left to be written 
            send_start(); // then start sending the next item in the buffer 
    } 
    else 
        do_close(error); 
} 

void SerialAPI::do_close(const boost::system::error_code& error) 
{
    if (error == boost::asio::error::operation_aborted) // if this call is the result of a timer cancel() 
        return; // ignore it because the connection cancelled the timer 
    serial.close(); 
}