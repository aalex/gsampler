#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "./samplerServer.h"
#include "./oscReceiver.h"
#include "./gui.h"
#include <tr1/memory>

class Application {
    public:
        void startServer(
            const std::string &receivePort,
            const std::string &sendHost,
            const std::string &sendPort
            );
        static Application& getInstance();
        void quit();
        bool on_idle();
        void run();

    private:
        Application();
        std::tr1::shared_ptr<SamplerServer> server_;        // FIXME: these should live somewhere else
        SamplerWindow gui_;
        bool done_;
};

#endif // _APPLICATION_H_
