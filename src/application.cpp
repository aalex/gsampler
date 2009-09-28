#include "./application.h"
#include "./physics.h"
#include <iostream>

Application* Application::instance_ = 0;

Application::Application() : server_()
{}

void Application::start()
{
    std::cout << "Starting application\n";
    server_.start();
}

Application& Application::getInstance()
{
    if ( !instance_ )
        instance_ = new Application();
    return *instance_;
}

