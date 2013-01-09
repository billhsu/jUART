/****************************************************************/
// By Bill Hsu
// Shanghai University
// My Blog:        http://BillHsu.me
// jUART Project:  http://BillHsu.github.com/jUART/
// Created on:     2013-01-09
/****************************************************************/

#include "Serial.h"


bool Serial::set_option(unsigned int baud, unsigned int parity,
    unsigned int csize, unsigned int flow, unsigned int stop)
{
    if(!serial.is_open())   return false;

    asio::serial_port_base::baud_rate opt_baud(baud);
    asio::serial_port_base::parity opt_parity(static_cast<asio::serial_port_base::parity::type>(parity));
    asio::serial_port_base::character_size opt_csize(csize);
    asio::serial_port_base::flow_control opt_flow(static_cast<asio::serial_port_base::flow_control::type>(flow));
    asio::serial_port_base::stop_bits opt_stop(static_cast<asio::serial_port_base::stop_bits::type>(stop));

    serial.set_option(opt_baud);
    serial.set_option(opt_parity);
    serial.set_option(opt_csize);
    serial.set_option(opt_flow);
    serial.set_option(opt_stop);

    return true;
}
