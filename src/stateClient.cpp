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

StateClient::StateClient(const std::string &nick) :
    nick_(nick),
    sender_("127.0.0.1","7770") 
{}

void StateClient::start()
{
    std::map<std::string, std::string> msg;
    msg["nick"] = nick_;
    sender_.sendStuff(msg);
}

