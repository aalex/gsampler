#include "./stateServer.h"
#include <iostream>

StateServer::StateServer() : 
    port_("7770"), 
    // TODO: try catch to avoid segfault when port busy
    server_(lo_server_thread_new(port_.c_str(), error)), 
    done_(false)
{
    /* add method that will match any path and args */
    lo_server_thread_add_method(server_, NULL, NULL, genericHandler, this);
    /* add method that will match subscribe path and string and int args */
    lo_server_thread_add_method(server_, "/subscribe", "sss", subscribeHandler, this);
    lo_server_thread_add_method(server_, "/position", "sfff", positionHandler, this);
    lo_server_thread_add_method(server_, "/set/3f", "ssfff", set3fHandler, this);
    /* add method that will list clients */
    lo_server_thread_add_method(server_, "/list_clients", "", listClientsHandler, this);
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
    StateServer *context = static_cast<StateServer*>(user_data);
    // TODO: make a lo_address for sending to based on this info
    if (argc != 3) 
        std::cout << "/subscribe : Bad number of arguments." << std::endl;
    else 
    {
        std::string nick((const char *)argv[0]);
        std::string host((const char *)argv[1]);
        std::string port((const char *)argv[2]);

        std::cout << "Got " << path 
            << " nick: " << nick
            << " <- host: " << host
            << ", port:" << port
            << std::endl << std::endl;

        context->clients_[nick] = OscSender(nick, host, port);
        // argv[1]->i 
    }
    return 0;
} 
int StateServer::positionHandler(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    std::cout << "Got " << path 
        << " nick: " << (const char *) argv[0]
        << " xyz: " << argv[1]->f 
        << argv[2]->f << " "
        << argv[3]->f << " "
        << std::endl;
    return 0;
} 

int StateServer::set3fHandler(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    std::cout << "Got " << path 
        << " nick: " << (const char *) argv[0]
        << " attribute: " << (const char *) argv[1]
        << " xyz: " << argv[2]->f 
        << argv[3]->f << " "
        << argv[4]->f << " "
        << std::endl;
    return 0;
} 

int StateServer::listClientsHandler(const char *path, const char *types, 
        lo_arg **argv, int argc,
        void *data, void *user_data)
{
    StateServer *context = static_cast<StateServer*>(user_data);
    context->listClients();
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

void StateServer::listClients()
{
    using std::string;
    using std::map;
    int count = 0;

    for (map<string, OscSender>::const_iterator iter = clients_.begin(); iter != clients_.end(); ++iter, ++count)
        std::cout << "Client " << count << " = " << iter->second.toString() << std::endl;    // just print the client key for now
}

