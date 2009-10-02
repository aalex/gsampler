#ifndef _OSC_SENDER_H_
#define _OSC_SENDER_H_

#include "lo/lo.h"
#include <string>
#include <map>

class OscSender {
    public:
        OscSender();
        OscSender(const std::string &host, const std::string &port);
        void sendStuff(std::map<std::string, std::string> &msg);
        std::string toString() const;
    private:
        std::string host_;
        std::string port_;
        lo_address address_;
};

#endif // _OSC_SENDER_H_
