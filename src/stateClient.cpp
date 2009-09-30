/*
 *  Copyright (C) 2004 Steve Harris, Uwe Koloska
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

StateClient::StateClient() :
    r_port_("1000"), r_addr_("127.0.0.1"), s_port_("7770"), s_addr_("127.0.0.1"), nick_("default")
{}

void StateClient::start()
{
    /* an address to send messages to. sometimes it is better to let the server
     * pick a port number for you by passing NULL as the last argument */
    lo_address t = lo_address_new(0, s_port_.c_str());

    if (lo_send(t, "/subscribe", "sss", nick_.c_str(), r_addr_.c_str(), r_port_.c_str()) == -1)
    {
        printf("OSC error %d: %s\n", lo_address_errno(t), lo_address_errstr(t));
    }
    lo_send(t, "/position", "sfff", "default", 0.12345678f, 1.2123f, 9.43434f);
    lo_send(t, "/attr/set", "ssfff", "default", "color", 1.0f, 0.8f, 0.2f);
    
    /* send a message with no arguments to the path /listClients */
    if (lo_send(t, "/list_clients", 0) == -1)
    {
        // pass
    }
    /* send a message with no arguments to the path /quit */
    if (lo_send(t, "/quit", 0) == -1)
    {
        printf("osc error %d: %s\n", lo_address_errno(t), lo_address_errstr(t));
    }
}

