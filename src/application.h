#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "./stateServer.h"
#include "./stateClient.h"
#include <tr1/memory>

class Application {
    public:
        void startServer(const std::string &serverListenPort);
        void startClient(const std::string &clientNick,
                const std::string &clientListenPort,
                const std::string &serverHost,
                const std::string &serverListenPort);
        static Application& getInstance();

    private:
        Application();
        static Application* instance_;
        std::tr1::shared_ptr<StateServer> server_;        // FIXME: these should live somewhere else
        std::tr1::shared_ptr<StateClient> client_;
};

#endif // _APPLICATION_H_
