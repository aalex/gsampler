#ifndef _STATE_SERVER_H_
#define _STATE_SERVER_H_

#include <string>
#include <map>
#include "lo/lo.h"
#include "./oscSender.h"

class StateServer {
    public:
        StateServer();
        void start();
    private:
        void listClients();

        static int genericHandler(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        static int subscribeHandler(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        static int positionHandler(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        static int quitHandler(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        static int listClientsHandler(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        static int set3fHandler(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        static void error(int num, const char *msg, const char *path);
        std::string port_;
        lo_server_thread server_;
        bool done_;
        std::map<std::string, OscSender> clients_;
};

#endif // _STATE_SERVER_H_
