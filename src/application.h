#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "./stateServer.h"

class Application {
    public:
        void start();
        static Application& getInstance();

    private:
        static Application* instance_;
        StateServer server_;
};

#endif // _APPLICATION_H_
