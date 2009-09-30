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

void StateClient::start()
{
    r_port_ = (char *)"1000";
    r_addr_ = (char *)"127.0.0.1";
    s_port_ = (char *)"7770";
    s_addr_ = (char *)"127.0.0.1";
    nick_ = (char *)"default";
    /* an address to send messages to. sometimes it is better to let the server
     * pick a port number for you by passing NULL as the last argument */
    //    lo_address t = lo_address_new_from_url( "osc.unix://localhost/tmp/mysocket" );
    lo_address t = lo_address_new(NULL, s_port_); //"7770");


    if (lo_send(t, "/subscribe", "sss", nick_, r_addr_, r_port_) == -1)
        printf("OSC error %d: %s\n", lo_address_errno(t), lo_address_errstr(t));

    /* send a message to /a/b/c/d with a mixtrure of float and string
     * arguments */
    lo_send(t, "/a/b/c/d", "sfsff", "one", 0.12345678f, "three",
            -0.00000023001f, 1.0);

    /* send a jamin scene change instruction with a 32bit integer argument */
    lo_send(t, "/jamin/scene", "i", 2);

    /* send a message with no arguments to the path /quit */
    if (lo_send(t, "/quit", NULL) == -1)
        printf("OSC error %d: %s\n", lo_address_errno(t), lo_address_errstr(t));
}

