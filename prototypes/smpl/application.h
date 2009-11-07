#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "./samplerServer.h"
#include "./oscReceiver.h"
#include <tr1/memory>

class Application {
    public:
        void startServer(const std::string &serverListenPort);
        static Application& getInstance();

    private:
        Application();
        static Application* instance_;
        std::tr1::shared_ptr<SamplerServer> server_;        // FIXME: these should live somewhere else
};

#endif // _APPLICATION_H_
