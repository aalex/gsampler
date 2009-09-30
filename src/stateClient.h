#ifndef _STATE_CLIENT_H_
#define _STATE_CLIENT_H_

#include <string>

class StateClient {
    private:
        std::string r_port_;
        std::string r_addr_;
        std::string s_port_;
        std::string s_addr_;
        std::string nick_;
    public:
        StateClient();
        void start();
};

#endif // _STATE_CLIENT_H_
