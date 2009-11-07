#include "./application.h"
#include <iostream>

Application* Application::instance_ = 0;

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
    if (!instance_)
        instance_ = new Application();
    return *instance_;
}

