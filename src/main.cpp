#include "./application.h"
#include <iostream>
#include <cstdlib> // for getenv
#include <boost/program_options.hpp>

//using namespace boost;
//void addOptions(OptionArgs &options)
//{
//    options.addBool("server", 's', "server", "Run as a server.");
//    options.addInt("client-listen-port", 'p', "clientlistenport", "Port for the client to listen to.");
//    options.addInt("client-send-port", 'q', "clientsendport", "Port for the client to send to.");
//    options.addInt("server-listen-port", 'r', "clientlistenport", "Port for the client to listen to.");
//    options.addInt("server-send-port", 't', "clientsendport", "Port for the client to send to.");
//}

// argv can't be const for program options to work
int main(int argc, char* argv[])  
{
    namespace po = boost::program_options;
    
    try 
    {
        po::options_description desc("Allowed options");
        std::string serverHost, serverListenPort, clientListenPort, clientName;

        desc.add_options()
            ("help", "produce help message")
            ("disable-server", "disables the server. Default is to run both server and client.")
            ("disable-client", "disables the client. Default is to run both server and client.")
            ("client-name", po::value<std::string>(&serverHost)->default_value(std::getenv("USER")), "name of client")
            ("server-host", po::value<std::string>(&serverHost)->default_value("127.0.0.1"), "server host address")
            ("server-listen-port", po::value<std::string>(&serverListenPort)->default_value("7770"), "server listen port")
            ("client-listen-port", po::value<std::string>(&clientListenPort)->default_value("7771"), "client listen port")
            ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) 
        {
            std::cout << desc << "\n";
            return 1;
        }

        if (vm.count("client-name")) 
        {
            std::cout << "client-name was set to " 
                << vm["client-name"].as<std::string>() << ".\n";
        } 
        //else 
        //{
        //    char *pUser;
        //    if (pUser = std::getenv("USER"))
        //    {
        //        std::cout << "client-name will be set to " <<  pUser << ".\n";
        //        vm["client-name"] = pUser;
        //    }
        //    else 
        //    {
        //        std::cout << "No client-name provided. No $USER found. Using default." << std::endl;
        //        vm["client-name"] = "default";
        //    }

        //}
        if (!vm.count("disable-client")) 
        {
            std::cout << "Running the state client.\n";
            Application::getInstance().startClient(vm["client-name"].as<std::string>(),
                    vm["client-listen-port"].as<std::string>(),
                    vm["server-host"].as<std::string>(),
                    vm["server-listen-port"].as<std::string>());
        } 
        if (!vm.count("disable-server")) 
        {
            std::cout << "Running the state server.\n";
            Application::getInstance().startServer(vm["server-listen-port"].as<std::string>());
        }
    }
    catch(std::exception& e) 
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...) 
    {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}

