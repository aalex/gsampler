#include "./application.h"

int main(int argc, const char* argv[])  
{
    if (argc > 1)
        Application::getInstance().startClient();
    else 
        Application::getInstance().startServer();
    return 0;
}

