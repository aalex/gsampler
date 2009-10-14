#include "./stateServer.h"
#include <iostream>

int StateServer::portCount_ = 0;

StateServer::StateServer(const std::string &listenPort) : clients_(), receiver_(listenPort.c_str()), done_(false) 
{
    /* add method that will match subscribe path and string and int args */
    receiver_.addHandler("/subscribe", "sss", subscribeCb, this);
    /* add method that will match subscribe path and string and int args */
    receiver_.addHandler("/unsubscribe", "s", unsubscribeCb, this);
    /* add method that will list clients */
    receiver_.addHandler("/list_clients", "", listClientsCb, this);
    receiver_.addHandler("/position", "sfff", positionCb, this);
    /* add method that will quit (eventually only the client) */
    receiver_.addHandler("/quit", "", quitCb, this);
}

void StateServer::start()
{
    receiver_.listen(); 
    while (!done_)
    {
        pushPositions();
        usleep(1000);
    }
}

/* catch subscribe message and display its values. */
int StateServer::subscribeCb(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    StateServer *context = static_cast<StateServer*>(user_data);

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
    }
    return 0;
} 


void StateServer::pushPositions()
{
    using std::map;
    using std::string;
    static float x = 0.0;

    // for every client, send a position update to all other clients
    for (map<string, OscSender>::const_iterator client = clients_.begin(); client != clients_.end(); ++client)
        for (map<string, OscSender>::const_iterator other = clients_.begin(); other != clients_.end(); ++other)
            if (other != client)
                client->second.sendMessage("/position", "sfff", other->first.c_str(), x, 0.0f, 0.0f, LO_ARGS_END);

    x += 0.01;
}


int StateServer::unsubscribeCb(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    StateServer *context = static_cast<StateServer*>(user_data);
    // TODO: make a lo_address for sending to based on this info
    if (argc != 1) 
        std::cout << "/unsubscribe : Bad number of arguments." << std::endl;
    else 
    {
        std::string nick((const char *)argv[0]);

        std::cout << "Got " << path 
            << " nick: " << nick
            << std::endl << std::endl;

        context->clients_.erase(nick);
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
    std::cout << std::endl;
}

int StateServer::listClientsCb(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    StateServer *context = static_cast<StateServer*>(user_data);
    context->listClients();
    return 0;
}


int StateServer::positionCb(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    std::cout << "Got " << path 
        << " nick: " << (const char *) argv[0]
        << " xyz: " << argv[1]->f 
        << argv[2]->f << " "
        << argv[3]->f << " "
        << std::endl << std::endl;
    return 0;
} 


int StateServer::quitCb(const char *path, const char *types, 
        lo_arg **argv, int argc,
        void *data, void *user_data)
{
    StateServer *context = static_cast<StateServer*>(user_data);
    // we have to ref to this otherwise?
    std::cout << "quitting\n\n";
    context->done_ = true;
    return 0;
}

