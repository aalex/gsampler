#ifndef _STATE_CLIENT_H_
#define _STATE_CLIENT_H_

#include <string>
#include <boost/thread.hpp>
#include "./oscSender.h"
#include "./oscReceiver.h"
#include "./sceneViewer.h"

class StateClient {
    private:
        std::string nick_;
        OscReceiver receiver_;
        OscSender sender_;
        SceneViewer viewer_;
        bool tryToSubscribe_;   // FIXME: should this be protected by a mutex?
        void subscribe();
        static int positionCb(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
        static int subscribeAcknowledgedCb(const char *path, 
                const char *types, lo_arg **argv, 
                int argc, void *data, void *user_data);
    public:
            StateClient(const std::string &nick, 
                    const std::string &listenPort,
                    const std::string &serverHost, 
                    const std::string &serverListenPort);
            ~StateClient();
            void start();
            void publishPosition(float x, float y, float z) const;
};

#endif // _STATE_CLIENT_H_
