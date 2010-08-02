#include "./application.h"
#include <iostream>

Application::Application() 
{}

void Application::startServer(
    const std::string &receivePort,
    const std::string &sendHost,
    const std::string &sendPort
    )
{
    std::cout << "Starting server\n";
    server_ = std::tr1::shared_ptr<SamplerServer>(new SamplerServer(receivePort, sendHost, sendPort));
    server_->start();
}

Application& Application::getInstance()
{
    // Meyer singleton pattern
    static Application instance;
    return instance;
}

