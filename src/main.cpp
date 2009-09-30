#include "./application.h"

int main(int argc, const char* argv[])  
{
    if (argc > 1)   // FIXME: some kind of argument here?
        Application::getInstance().startClient();
    else 
        Application::getInstance().startServer();
    return 0;
}

