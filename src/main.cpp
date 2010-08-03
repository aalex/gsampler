/**
 *    gsampler
 *    Copyright (C) 2009 Tristan Matthews and Alexandre Quessy
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/
#include "./application.h"
#include "config.h"
#include <iostream>
#include <cstdlib> // for getenv
#include <boost/program_options.hpp>

// argv can't be const for program options to work
int main(int argc, char* argv[])  
{
    namespace po = boost::program_options;
    using std::string;
    
    try 
    {
        po::options_description desc("Allowed options");
        
        // TODO: use boost::program_options::parse_environment instead of getenv
        desc.add_options()
            ("help,h", "produce help message")
            ("version,V", "Prints version and exits.")
            ("listen-port,p", po::value<string>()->default_value("7770"), "listen port")
            ("send-host,H", po::value<string>()->default_value("127.0.0.1"), "send address")
            ("send-port,s", po::value<string>()->default_value("7771"), "send port")
            ;
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if (vm.count("help")) 
        {
            std::cout << desc << "\n";
            return 0;
        }
        if (vm.count("version")) 
        {
            std::cout << PACKAGE_VERSION << "\n";
            return 0;
        }
        std::cout << "Welcome to " << PACKAGE << " " << VERSION << "!" << std::endl;
        Application::getInstance().startServer(vm["listen-port"].as<string>(), vm["send-host"].as<string>(), vm["send-port"].as<string>());
        std::cout << "Exiting." << std::endl;
    }
    catch(const std::exception& e) 
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...) 
    {
        std::cerr << "Exception of unknown type!\n";
        return 1;
    }
    return 0;
}

