#include "./oscSender.h"

OscSender::OscSender() :
    nick_(""), host_(""), port_(""), 
    address_(0)
{}

OscSender::OscSender(const std::string &nick, const std::string &host, const std::string &port) :
    nick_(nick), host_(host), port_(port), 
    address_(lo_address_new(host.c_str(), port_.c_str()))
{
}

std::string OscSender::toString() const
{
    return "nick:" + nick_ + ", host:" + host_ + ", port:" + port_;
}

