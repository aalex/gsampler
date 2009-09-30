#ifndef _OSC_SENDER_H_
#define _OSC_SENDER_H_

#include "lo/lo.h"
#include <string>

class OscSender {
    public:
        OscSender();
        OscSender(const std::string &nick, const std::string &host, const std::string &port);
        std::string toString() const;
    private:
        std::string nick_;
        std::string host_;
        std::string port_;
        lo_address address_;
};

#endif // _OSC_SENDER_H_
