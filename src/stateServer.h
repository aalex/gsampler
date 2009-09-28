#ifndef _STATE_SERVER_H_
#define _STATE_SERVER_H_

#include <string>
#include "lo/lo.h"

class StateServer {
    public:
        StateServer();
        void start();
    private:
        static int generic_handler(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        static void error(int num, const char *msg, const char *path);
        std::string port_;
        lo_server server_;
        bool done_;
};

#endif // _STATE_SERVER_H_
