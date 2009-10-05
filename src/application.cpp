#include "./application.h"
#include <iostream>

Application* Application::instance_ = 0;

Application::Application() 
{}

void Application::startServer(const std::string &serverListenPort)
{
    std::cout << "Starting server\n";
    server_ = std::tr1::shared_ptr<StateServer>(new StateServer(serverListenPort));
    server_->start();
}


void Application::startClient(const std::string &nick, const std::string &listenPort,
        const std::string &serverHost, const std::string &serverListenPort)
{
    std::cout << "Starting client\n";
    client_ = std::tr1::shared_ptr<StateClient>(new StateClient(nick, listenPort, 
                serverHost, serverListenPort));
    client_->start();
}

Application& Application::getInstance()
{
    if (!instance_)
        instance_ = new Application();
    return *instance_;
}

