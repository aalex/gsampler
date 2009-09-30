#ifndef _STATE_CLIENT_H_
#define _STATE_CLIENT_H_

#include <string>
#include "lo/lo.h"

class StateClient {
    private:
        char *r_port_;
        char *r_addr_;
        char *s_port_;
        char *s_addr_;
        char *nick_;
    public:
        void start();
};

#endif // _STATE_CLIENT_H_
