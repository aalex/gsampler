#ifndef _STATE_SERVER_H_
#define _STATE_SERVER_H_

#include <string>
#include <map>
#include "lo/lo.h"
#include "./oscReceiver.h"

class SamplerServer {
    public:
        SamplerServer(const std::string &listenPort);

        void start();

    private:
        static int pingCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        
        static int pongCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        
        static int quitCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);

        OscReceiver receiver_;

        bool done_;
};

#endif // _STATE_SERVER_H_
