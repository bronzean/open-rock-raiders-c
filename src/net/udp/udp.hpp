/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Header file for the client socket wrapper.
 * ----------------------------------------------------------- */

#pragma once
#include "../../Engine.hpp"

int udp_send(UDPsocket sock, int channel, UDPpacket *out, UDPpacket *in, Uint32 delay, Uint8 expect, int timeout); //Send a packet.
