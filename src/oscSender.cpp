#include "./oscSender.h"

OscSender::OscSender() :
    host_(""), port_(""), 
    address_(0)
{}

OscSender::OscSender(const std::string &host, const std::string &port) :
    host_(host), port_(port), 
    address_(lo_address_new(host.c_str(), port_.c_str()))
{
}

std::string OscSender::toString() const
{
    return "host:" + host_ + ", port:" + port_;
}


void OscSender::sendStuff(std::map<std::string, std::string> &msg)
{
    if (lo_send(address_, "/subscribe", "sss", msg["nick"].c_str(), host_.c_str(), port_.c_str()) == -1)
        printf("OSC error %d: %s\n", lo_address_errno(address_), lo_address_errstr(address_));

    lo_send(address_, "/position", "sfff", msg["nick"].c_str(), 0.12345678f, 1.2123f, 9.43434f);
    
    /* send a message with no arguments to the path /list_clients */
    if (lo_send(address_, "/list_clients", 0) == -1)
        printf("osc error %d: %s\n", lo_address_errno(address_), lo_address_errstr(address_));
}

