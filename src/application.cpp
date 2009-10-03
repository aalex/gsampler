#include "./application.h"
#include <iostream>

Application* Application::instance_ = 0;

Application::Application() 
{}

void Application::startServer()
{
    std::cout << "Starting server\n";
    server_ = std::tr1::shared_ptr<StateServer>(new StateServer());
    server_->start();
}


void Application::startClient(const std::string &clientName)
{
    std::cout << "Starting client\n";
    client_ = std::tr1::shared_ptr<StateClient>(new StateClient(clientName));
    client_->start();
}

Application& Application::getInstance()
{
    if (!instance_)
        instance_ = new Application();
    return *instance_;
}

