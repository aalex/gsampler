#ifndef _STATE_SERVER_H_
#define _STATE_SERVER_H_

#include <string>
#include <map>
#include <vector>
#include <tr1/memory>
#include "lo/lo.h"
#include "./oscReceiver.h"
#include "./oscSender.h"

using namespace std::tr1; // shared_ptr

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

// forward declaration
class Application;

class SamplerServer {
    public:
        SamplerServer(Application *owner,
            const std::string &listenPort, 
            const std::string &sendHost, 
            const std::string &sendPort
            );

        void poll();

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
        Application *owner_;
        OscReceiver receiver_;
        OscSender sender_;
        // const int num_players_ = 8;
        // TODO:2010-08-03:aalex:use this 
        std::vector< shared_ptr<SoundPlayer> > players_;
        bool done_;
};

#endif // _STATE_SERVER_H_
