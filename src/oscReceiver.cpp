#include "./oscReceiver.h"
#include <iostream>
#include <cstdio>

OscReceiver::OscReceiver(const std::string &port) :
    port_(port), 
    server_(lo_server_new(port_.c_str(), error))
{
    /* add method that will match any path and args */
    // if added first, will always be called for every message
    //lo_server_add_method(server_, NULL, NULL, genericHandler, this);
    std::cout << "Listening osc.udp://localhost:" << port_ << std::endl;
}

OscReceiver::~OscReceiver()
{
    std::cout << "Freeing server\n";
    lo_server_free(server_);
}

void OscReceiver::addHandler(const char *path, const char *types, lo_method_handler handler, void *userData)
{
    lo_server_add_method(server_, path, types, handler, userData);
}

void OscReceiver::receiveNonBlocking()
{
    static const int TIMEOUT = 100; // ms
    int recv = lo_server_recv_noblock(server_, TIMEOUT);
    if (recv == 0) // got nothing, sleep a bit
        usleep(1000);
}

void OscReceiver::error(int num, const char *msg, const char *path)
{
    std::cerr << "liblo server error " << num << " in path " << path 
        << ": " << msg << std::endl;
}

/* catch any incoming messages and display them. returning 1 means that the 
 *  * message has not been fully handled and the server should try other methods */
int OscReceiver::genericHandler(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    //OscReceiver *context = static_cast<OscReceiver*>(user_data);
    int i; 
    std::cout << "Generic handler." << std::endl;
    printf("path: <%s>\n", path); 
    for (i = 0; i < argc; ++i) 
    { 
        printf("arg %d '%c' ", i, types[i]); 
        lo_arg_pp(static_cast<lo_type>(types[i]), argv[i]); 
        printf("\n"); 
    } 
    printf("\n"); 
    fflush(stdout); 
    return 1; 
} 


std::string OscReceiver::toString() const
{
    return "osc.udp://localhost:" + port_;
}

