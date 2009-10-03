#ifndef _STATE_CLIENT_H_
#define _STATE_CLIENT_H_

#include <string>
#include "./oscSender.h"

class StateClient {
    private:
        std::string nick_;
        OscSender sender_;
    public:
        StateClient(const std::string &nick);
        void start();
};

#endif // _STATE_CLIENT_H_
