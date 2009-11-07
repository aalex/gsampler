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

    std::cout << "Started sender to osc.udp://" << sendHost << ":" << sendPort << std::endl;
    receiver_.addHandler("/ping", "", pingCb, this);
    receiver_.addHandler("/pong", "", pongCb, this);
    receiver_.addHandler("/sampler/quit", "", quitCb, this);
    receiver_.addHandler("/sampler/play/start", "ii", playStartCb, this);
    receiver_.addHandler("/sampler/play/stop", "", playStopCb, this);
    receiver_.addHandler("/sampler/record/start", "i", recordStartCb, this);
    receiver_.addHandler("/sampler/record/stop", "i", recordStopCb, this);
    receiver_.addHandler("/sampler/load", "is", loadCb, this);
    receiver_.addHandler("/sampler/save", "is", saveCb, this);

    std::cout << "OSC message handlers:" << std::endl;
    std::cout << " * /ping" << std::endl;
    std::cout << " * /pong" << std::endl;
    std::cout << " * /sampler/quit" << std::endl;
    std::cout << " * /sampler/play/start <player_id> <buffer_id>" << std::endl;
    std::cout << " * /sampler/play/stop <player_id>" << std::endl;
    std::cout << " * /sampler/record/start <buffer_id>" << std::endl;
    std::cout << " * /sampler/record/stop" << std::endl;
    std::cout << " * /sampler/load <buffer_id> <file_name>" << std::endl;
    std::cout << " * /sampler/save <buffer_id> <file_name>" << std::endl;
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

    /*
    We can only record one sound at a time.
    We can play up to 8 (or more) sounds at a time.
    There can be many buffers, such as 50, for instance.

    * /sampler/play/start <player_id> <buffer_id> : starts playing a sound.
    * /sampler/play/stop <player_id> : stops playing a sound.
    * /sampler/record/start <buffer_id> : starts recording a sound 
    * /sampler/record/stop <buffer_id> : stops recording a sound 
    * /sampler/all/stop : stops all players and recorders. 
    * /sampler/save <buffer_id> <file_name> : saves a wav file.
    * /sampler/load <buffer_id> <file_name> : loads a wav file.
    */
int SamplerServer::playStartCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    if (argc != 2) 
    {
        std::cerr << "/sampler/play/start : Bad number of arguments." << std::endl;
    } 
    else
    {
        int player_id = argv[0]->i; // int
        int buffer_id = argv[1]->i; // int
        std::cout << "Got /sampler/play/start " <<  player_id << " " << buffer_id << std::endl;
    }
    return 0;
}

int SamplerServer::playStopCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    if (argc != 1) 
    {
        std::cerr << "/sampler/play/stop : Bad number of arguments." << std::endl;
    } 
    else
    {
        int player_id = argv[0]->i; // int
        std::cout << "Got /sampler/play/stop " <<  player_id << std::endl;
    }
    return 0;
}

int SamplerServer::recordStartCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    if (argc != 1) 
    {
        std::cerr << "/sampler/record/start : Bad number of arguments." << std::endl;
    } 
    else
    {
        int buffer_id = argv[0]->i; // int
        std::cout << "Got /sampler/record/start " <<  buffer_id << std::endl;
    }
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
    if (argc != 2) 
    {
        std::cerr << "/sampler/save : Bad number of arguments." << std::endl;
    } 
    else
    {
        int buffer_id = argv[0]->i; // int
        std::string file_name((const char *)argv[1]); // string
        std::cout << "Got /sampler/save" <<  buffer_id << " " << file_name << std::endl;
    }
    return 0;
}

int SamplerServer::loadCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data)
{
    if (argc != 2) 
    {
        std::cerr << "/sampler/load : Bad number of arguments." << std::endl;
    } 
    else
    {
        int buffer_id = argv[0]->i; // int
        std::string file_name((const char *)argv[1]); // string
        std::cout << "Got /sampler/load" <<  buffer_id << " " << file_name << std::endl;
    }
    return 0;
}

