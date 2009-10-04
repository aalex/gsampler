#ifndef _STATE_CLIENT_H_
#define _STATE_CLIENT_H_

#include <string>
#include "./oscSender.h"

class StateClient {
    private:
        std::string nick_;
        OscSender sender_;
        void subscribe();
        void unsubscribe();
        void tellServerToListClients();
    public:
        StateClient(const std::string &nick, 
                const std::string &serverHost, 
                const std::string &serverPort);
        void start();
};

#endif // _STATE_CLIENT_H_
