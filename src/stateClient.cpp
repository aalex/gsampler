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
#include <iostream>
#include "lo/lo.h"

StateClient::StateClient(const std::string &nick, 
        const std::string &listenPort,
        const std::string &serverHost,
        const std::string &serverListenPort) :
    nick_(nick),
    receiver_(listenPort),
    sender_(serverHost, serverListenPort),
    viewer_()
{
    sender_.sendMessage("/subscribe", "sss", nick_.c_str(), sender_.host(), listenPort.c_str(), LO_ARGS_END);
}


StateClient::~StateClient()
{
    sender_.sendMessage("/unsubscribe", "s", nick_.c_str(), LO_ARGS_END);
    std::cout << "Unsubscribed, going down...\n";
}

void StateClient::start()
{
    receiver_.listen(); // start listening in separate thread
    viewer_.run();  // our event loop is in here
}

