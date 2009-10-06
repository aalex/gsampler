/*
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation; either version 2.1 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  $Id$
 */


#include "stateClient.h"
#include <cstdio>
#include "lo/lo.h"

StateClient::StateClient(const std::string &nick, 
        const std::string &listenPort,
        const std::string &serverHost,
        const std::string &serverListenPort) :
    nick_(nick),
    receiver_(listenPort),
    sender_(serverHost, serverListenPort) 
{}

void StateClient::start()
{
    sender_.sendMessage("/subscribe", "sss", nick_.c_str(), sender_.host(), sender_.port(), LO_ARGS_END);
    sender_.sendMessage("/list_clients", "", LO_ARGS_END);
    sender_.sendMessage("/position", "sfff", nick_.c_str(), 0.12345678f, 1.2123f, 9.43434f, LO_ARGS_END);
    sender_.sendMessage("/unsubscribe", "s", nick_.c_str(), LO_ARGS_END);
    sender_.sendMessage("/list_clients", "", LO_ARGS_END);
    // receiver_.listen();
    sender_.sendMessage("/quit", "", LO_ARGS_END);
}

