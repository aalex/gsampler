#include "./oscReceiver.h"
#include <iostream>

OscReceiver::OscReceiver(const std::string &host, const std::string &port) :
    host_(host), port_(port), 
    server_(lo_server_thread_new(port_.c_str(), error)), 
    done_(false)
{
    /* add method that will match any path and args */
    lo_server_thread_add_method(server_, NULL, NULL, genericHandler, this);
    /* add method that will quit (eventually only the client) */
    lo_server_thread_add_method(server_, "/quit", "", quitHandler, this);
}

void OscReceiver::addHandler(const char *path, const char *types, lo_method_handler handler, void *userData)
{
    lo_server_thread_add_method(server_, path, types, handler, userData);
}

void OscReceiver::start()
{
    std::cout << "Starting state server on port " << port_ << std::endl;
    lo_server_thread_start(server_);

    while (!done_)
    {
        usleep(1000);
    }
    lo_server_thread_free(server_);
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


int OscReceiver::quitHandler(const char *path, const char *types, 
        lo_arg **argv, int argc,
        void *data, void *user_data)
{
    OscReceiver *context = static_cast<OscReceiver*>(user_data);
    // we have to ref to this otherwise?
    std::cout << ("quitting\n\n");
    context->done_ = true;
    return 0;
}


std::string OscReceiver::toString() const
{
    return "host:" + host_ + ", port:" + port_;
}

