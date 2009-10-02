#include "./application.h"

//using namespace boost;
//void addOptions(OptionArgs &options)
//{
//    options.addBool("server", 's', "server", "Run as a server.");
//    options.addInt("client-listen-port", 'p', "clientlistenport", "Port for the client to listen to.");
//    options.addInt("client-send-port", 'q', "clientsendport", "Port for the client to send to.");
//    options.addInt("server-listen-port", 'r', "clientlistenport", "Port for the client to listen to.");
//    options.addInt("server-send-port", 't', "clientsendport", "Port for the client to send to.");
//}

int main(int argc, const char* argv[])  
{
    //OptionArgs options;
    //addOptions(options);
    //options.parse(argc, argv);
    //if (options["server"])
    if (argc > 1)   // FIXME: some kind of argument here?
    {
        Application::getInstance().startClient();
    } else {
        // FIXME: be able to start client and server?
        Application::getInstance().startServer();
    }
    return 0;
}

