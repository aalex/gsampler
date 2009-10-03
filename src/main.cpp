#include "./application.h"
#include <iostream>

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
    //OptionArgs options;
    //addOptions(options);
    //options.parse(argc, argv);
    //if (options["server"])
    
    try 
    {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("client-name", po::value<std::string>(), "name of client")
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
            Application::getInstance().startClient(vm["client-name"].as<std::string>());
        } 
        else 
        {
            std::cout << "Running as server.\n";
            Application::getInstance().startServer();
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

