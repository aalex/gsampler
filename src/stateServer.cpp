#include "./stateServer.h"
#include <iostream>

int StateServer::portCount_ = 0;

StateServer::StateServer() : clients_(), receiver_("127.0.0.1", "7770") {}

void StateServer::start()
{
    receiver_.start(); 
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

        context->clients_[nick] = OscSender(host, port);
        // argv[1]->i 
    }
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

