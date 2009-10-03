#ifndef _OSC_SENDER_H_
#define _OSC_SENDER_H_

#include "lo/lo.h"
#include <string>
#include <map>

class OscSender {
    // FIXME: ideally, this would have a wrapper to lo_send, but it seems to be 
    // too much of a pain to wrap a function with a variable number of arguments
    friend class StateClient;
    public:
        OscSender();
        OscSender(const std::string &host, const std::string &port);
        std::string toString() const;
        const char * host() { return host_.c_str(); }
        const char * port() { return port_.c_str(); }
    private:
        std::string host_;
        std::string port_;
        lo_address address_;
};

#endif // _OSC_SENDER_H_
