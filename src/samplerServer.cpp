#include "./samplerServer.h"
#include <iostream>

//int SamplerServer::portCount_ = 0;

SamplerServer::SamplerServer(
        const std::string &listenPort, 
        const std::string &sendHost, 
        const std::string &sendPort) : 
    receiver_(listenPort.c_str()), 
    sender_(sendHost, sendPort), 
    done_(false) 
{
    /* add methods */
    std::cout << "Started sender to " << sendHost << " on port " << sendPort << "." << std::endl;
    receiver_.addHandler("/ping", "", pingCb, this);
    receiver_.addHandler("/pong", "", pongCb, this);
    receiver_.addHandler("/quit", "", quitCb, this);
}

void SamplerServer::start()
{
    receiver_.listen(); 
    while (!done_)
    {
        usleep(1000);
    }
}

int SamplerServer::pingCb(
        const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data)
{
    std::cout << "Got /ping" << std::endl;
    SamplerServer *context = static_cast<SamplerServer*>(user_data);
    context->sender_.sendMessage("/pong", "", LO_ARGS_END);
    return 0;
}

int SamplerServer::pongCb(
        const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data)
{
    std::cout << "Got /pong" << std::endl;
    return 0;
}

int SamplerServer::quitCb(
        const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data)
{
    std::cout << "Got /quit" << std::endl;
    return 0;
}

