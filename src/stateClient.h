#ifndef _STATE_CLIENT_H_
#define _STATE_CLIENT_H_

#include <string>
#include "./oscSender.h"
#include "./oscReceiver.h"

class StateClient {
    private:
        std::string nick_;
        OscSender sender_;
        OscReceiver receiver_;
    public:
        StateClient(const std::string &nick, 
                const std::string &listenPort,
                const std::string &serverHost, 
                const std::string &serverListenPort);
        void start();
};

#endif // _STATE_CLIENT_H_
