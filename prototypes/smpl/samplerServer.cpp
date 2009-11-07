#include "./samplerServer.h"
#include <iostream>

int SamplerServer::portCount_ = 0;

SamplerServer::SamplerServer(const std::string &listenPort) : receiver_(listenPort.c_str()), done_(false) 
{
    /* add methods */
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

static int SamplerServer::pingCb(
        const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data);
{
    std::cout << "Got /ping" << std::endl;
    client->second.sendMessage("/pong", "", LO_ARGS_END);
}

static int SamplerServer::pongCb(
        const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data);
{
    std::cout << "Got /pong" << std::endl;
}

static int SamplerServer::quitCb(
        const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data);
{
    std::cout << "Got /quit" << std::endl;
}

