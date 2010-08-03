#ifndef _STATE_SERVER_H_
#define _STATE_SERVER_H_

#include <string>
#include <map>
#include "lo/lo.h"
#include "./oscReceiver.h"
#include "./oscSender.h"

// TODO: remove this class and use the one in player.h
class SoundPlayer {
    public:
        SoundPlayer();
        void start(const std::string &fileName);
        void stop();
    private:
        //
        std::string file_name_;
        bool is_playing_;
};

class SamplerServer {
    public:
        SamplerServer(
            const std::string &listenPort, 
            const std::string &sendHost, 
            const std::string &sendPort
            );

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

        static int playStartCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);

        static int playStopCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);

        static int recordStartCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);

        static int recordStopCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
#if 0
        static int saveCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);

        static int loadCb(
                const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
#endif
        OscReceiver receiver_;
        OscSender sender_;

        bool done_;
};

#endif // _STATE_SERVER_H_
