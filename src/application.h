#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "./stateServer.h"
#include "./stateClient.h"
#include <tr1/memory>

class Application {
    public:
        void startServer();
        void startClient(const std::string &clientName, 
                const std::string &hostName, 
                const std::string &portName);
        static Application& getInstance();

    private:
        Application();
        static Application* instance_;
        std::tr1::shared_ptr<StateServer> server_;        // FIXME: these should live somewhere else
        std::tr1::shared_ptr<StateClient> client_;
};

#endif // _APPLICATION_H_
