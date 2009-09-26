#include "./application.h"
#include <iostream>

Application* Application::instance_ = 0;

void Application::start()
{
    std::cout << "Starting application\n";
}

Application& Application::getInstance()
{
    if ( !instance_ )
        instance_ = new Application;
    return *instance_;
}

