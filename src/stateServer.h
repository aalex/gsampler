#ifndef _STATE_SERVER_H_
#define _STATE_SERVER_H_

#include <string>
#include <map>
#include "lo/lo.h"
#include "./oscSender.h"
#include "./oscReceiver.h"

class StateServer {
    public:
        StateServer();
        void start();
    private:
        static int subscribeCb(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data);
        
        static int listClientsCb(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);

        static int positionCb(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);

        void listClients();

        std::map<std::string, OscSender> clients_;
        OscReceiver receiver_;
        static int portCount_;
        const static int BASE_PORT = 7770;
};

#endif // _STATE_SERVER_H_
