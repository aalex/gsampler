#ifndef _STATE_CLIENT_H_
#define _STATE_CLIENT_H_

#include <string>
#include "./oscSender.h"
#include "./oscReceiver.h"
#include "./dystViewer.h"

class StateClient {
    private:
        std::string nick_;
        OscSender sender_;
        OscReceiver receiver_;
        DystViewer viewer_;
    public:
        StateClient(const std::string &nick, 
                const std::string &listenPort,
                const std::string &serverHost, 
                const std::string &serverListenPort);
        ~StateClient();
        void start();
};

#endif // _STATE_CLIENT_H_
