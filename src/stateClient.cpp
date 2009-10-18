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
    receiver_.addHandler("/position", "sfff", positionCb, this);
}


int StateClient::positionCb(const char *path, 
        const char *types, lo_arg **argv, 
        int argc, void *data, void *user_data) 
{ 
    StateClient *context = static_cast<StateClient*>(user_data);
    std::cout << "Got " << path 
        << " nick: " << (const char *) argv[0]
        << " xyz: " << argv[1]->f 
        << argv[2]->f << " "
        << argv[3]->f << " "
        << std::endl << std::endl;
    // Move opponent
    // FIXME: should be viewer_.getScene().remoteState_
     context->viewer_.remoteState_->position_.set(argv[1]->f, argv[2]->f, argv[3]->f);
     context->viewer_.remoteState_->moveRequest_ = true;
    return 0;
} 

void StateClient::publishPosition(float x, float y, float z) const
{
    sender_.sendMessage("/position", "sfff", nick_.c_str(), x, y, z, LO_ARGS_END);
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

