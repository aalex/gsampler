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
    subscribe();
    tellServerToListClients();
    lo_send(sender_.address_, "/position", "sfff", nick_.c_str(), 0.12345678f, 1.2123f, 9.43434f);
    unsubscribe();
    tellServerToListClients();
    // receiver_.listen();
    lo_send(sender_.address_, "/quit", "");
}

void StateClient::subscribe()
{
    lo_send(sender_.address_, "/subscribe", "sss", nick_.c_str(), sender_.host(), sender_.port());
}

void StateClient::unsubscribe()
{
    lo_send(sender_.address_, "/unsubscribe", "s", nick_.c_str());
}

void StateClient::tellServerToListClients()
{
    lo_send(sender_.address_, "/list_clients", "");
}

