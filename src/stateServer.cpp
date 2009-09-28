#include "./stateServer.h"
#include <iostream>

StateServer::StateServer() : 
    port_("7770"), 
    server_(lo_server_new(port_.c_str(), error)), 
    done_(false)
{
    /* add method that will match any path and args */
    lo_server_add_method(server_, NULL, NULL, generic_handler, this);
}

void StateServer::start()
{
    std::cout << "Starting state server on port " << port_ << std::endl;
    while (!done_)
    {
        lo_server_recv_noblock(server_, 0);
        usleep(1000);
    }
}

void StateServer::error(int num, const char *msg, const char *path)
{
    std::cerr << "liblo server error " << num << " in path " << path 
        << ": " << msg << std::endl;
}


/* catch any incoming messages and display them. returning 1 means that the 
 *  * message has not been fully handled and the server should try other methods */
int StateServer::generic_handler(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    StateServer *context = static_cast<StateServer*>(user_data);
    int i; 

    printf("path: <%s>\n", path); 
    for (i = 0; i < argc; ++i) 
    { 
        printf("arg %d '%c' ", i, types[i]); 
        //lo_arg_pp(types[i], argv[i]); 
        printf("\n"); 
    } 
    printf("\n"); 
    fflush(stdout); 

    return 1; 
} 

