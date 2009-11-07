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
    receiver_.addHandler("/sampler/quit", "", quitCb, this);
    receiver_.addHandler("/sampler/play/start", "", playStartCb, this);
    receiver_.addHandler("/sampler/play/stop", "", playStopCb, this);
    receiver_.addHandler("/sampler/record/start", "", recordStartCb, this);
    receiver_.addHandler("/sampler/record/stop", "", recordStopCb, this);
    receiver_.addHandler("/sampler/load", "", loadCb, this);
    receiver_.addHandler("/sampler/save", "", saveCb, this);

    std::cout << "OSC message handlers:" << std::endl;
    std::cout << " * /ping" << std::endl;
    std::cout << " * /pong" << std::endl;
    std::cout << " * /sampler/quit" << std::endl;
    std::cout << " * /sampler/play/start" << std::endl;
    std::cout << " * /sampler/play/stop" << std::endl;
    std::cout << " * /sampler/record/start" << std::endl;
    std::cout << " * /sampler/record/stop" << std::endl;
    std::cout << " * /sampler/load" << std::endl;
    std::cout << " * /sampler/save" << std::endl;
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
    std::cout << "Got /sampler/quit" << std::endl;
    return 0;
}

int SamplerServer::playStartCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    std::cout << "Got /sampler/play/start" << std::endl;
    return 0;
}

int SamplerServer::playStopCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    std::cout << "Got /sampler/play/stop" << std::endl;
    return 0;
}

int SamplerServer::recordStartCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    std::cout << "Got /sampler/record/start" << std::endl;
    return 0;
}

int SamplerServer::recordStopCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    std::cout << "Got /sampler/record/stop" << std::endl;
    return 0;
}

int SamplerServer::saveCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    std::cout << "Got /sampler/save" << std::endl;
    return 0;
}

int SamplerServer::loadCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    std::cout << "Got /sampler/load" << std::endl;
    return 0;
}

