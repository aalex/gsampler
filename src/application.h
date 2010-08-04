#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "./samplerServer.h"
#include "./oscReceiver.h"
#include "./gui.h"
#include "./AudioManager.h"
#include <tr1/memory>

class Application {
    public:
        void startServer(
            const std::string &receivePort,
            const std::string &sendHost,
            const std::string &sendPort
            );
        void quit();
        bool on_idle();
        void run();
        Application();

    private:
        std::tr1::shared_ptr<SamplerServer> server_;        // FIXME: these should live somewhere else
        SamplerWindow gui_;
        AudioManager audio_;
        bool done_;
};

#endif // _APPLICATION_H_
