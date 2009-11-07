#include "./application.h"
#include <iostream>

Application* Application::instance_ = 0;

Application::Application() 
{}

void Application::startServer(const std::string &serverListenPort)
{
    std::cout << "Starting server\n";
    server_ = std::tr1::shared_ptr<SamplerServer>(new SamplerServer(serverListenPort));
    server_->start();
}

Application& Application::getInstance()
{
    if (!instance_)
        instance_ = new Application();
    return *instance_;
}

