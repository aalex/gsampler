/**
 *    Boomers : 3D War Game 
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
//            ("server-mode,s", "Runs as server. Default is to run as client.")
//            ("client-name,c", po::value<string>()->default_value(std::getenv("USER")), "name of client")
//            ("server-host,H", po::value<string>()->default_value("127.0.0.1"), "server host address")
            ("listen-port,p", po::value<string>()->default_value("7770"), "server listen port")
//            ("client-listen-port,p", po::value<string>()->default_value("7771"), "client listen port")
            ;
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if (vm.count("help")) 
        {
            std::cout << desc << "\n";
            return 1;
        }
        std::cout << "Welcome to Smpl !" << std::endl;
        Application::getInstance().startServer(vm["listen-port"].as<string>());
        //Application::reset();
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
    }
    return 0;
}
