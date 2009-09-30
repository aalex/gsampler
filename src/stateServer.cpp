#include "./stateServer.h"
#include <iostream>

StateServer::StateServer() : 
    port_("7770"), 
    server_(lo_server_thread_new(port_.c_str(), error)), 
    done_(false)
{
    /* add method that will match any path and args */
    lo_server_thread_add_method(server_, NULL, NULL, genericHandler, this);
    /* add method that will match subscribe path and string and int args */
    lo_server_thread_add_method(server_, "/subscribe", "sss", subscribeHandler, this);
    lo_server_thread_add_method(server_, "/position", "sfff", positionHandler, this);
    /* add method that will quit (eventually only the client) */
    lo_server_thread_add_method(server_, "/quit", "", quitHandler, this);
}

void StateServer::start()
{
    std::cout << "Starting state server on port " << port_ << std::endl;
    lo_server_thread_start(server_);

    while (!done_)
    {
        usleep(1000);
    }
    lo_server_thread_free(server_);
}

void StateServer::error(int num, const char *msg, const char *path)
{
    std::cerr << "liblo server error " << num << " in path " << path 
        << ": " << msg << std::endl;
}

/* catch any incoming messages and display them. returning 1 means that the 
 *  * message has not been fully handled and the server should try other methods */
int StateServer::genericHandler(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    //StateServer *context = static_cast<StateServer*>(user_data);
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


/* catch subscribe message and display its values. */

int StateServer::subscribeHandler(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    //StateServer *context = static_cast<StateServer*>(user_data);
    // TODO: make a lo_address for sending to based on this info
    if (argc != 3) {
        std::cout << "/subscribe : Bad number of arguments." << std::endl;
    } else {
    std::cout << "Got " << path 
        << " nick: " << (const char *)argv[0] 
        << " <- host: " << (const char *)argv[1] 
        << ", port:" << (const char *)argv[2] 
        << std::endl << std::endl;
    // argv[1]->i 
    }
    return 0;
} 
int StateServer::positionHandler(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    // seems never called..
    std::cout << "Got " << path 
        << " nick: " << (const char *)argv[0]
        << " xyz: " << argv[1]->f 
        << argv[2]->f << " "
        << argv[3]->f << " "
        << std::endl << std::endl;
    return 0;
} 

int StateServer::quitHandler(const char *path, const char *types, 
        lo_arg **argv, int argc,
        void *data, void *user_data)
{
    StateServer *context = static_cast<StateServer*>(user_data);
    // we have to ref to this otherwise?
    std::cout << ("quitting\n\n");
    context->done_ = true;
    return 0;
}

