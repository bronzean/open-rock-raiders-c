/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Header file for the client socket wrapper.
 * ----------------------------------------------------------- */

#pragma once
#include "../../Engine.hpp"

class client_udp
{
public:
	UDPsocket client_socket; //This is the socket.
	bool client_disconnect; //Does the client want to disconnect?
	char* buffer; //Stores the last message recieved from the client.
	SDLNet_SocketSet socketSet; //Makes it all work.
	bool activity; //Is there any need to update stuff?
	IPaddress ip; //The IPAddress of...The client?

	client_udp()
	{
		client_disconnect = false;
		buffer = NULL;
		activity = false;
		socketSet = SDLNet_AllocSocketSet(1);
		client_socket = NULL;
	}
	~client_udp()
	{
	}

	void update();
};

static std::vector<client_udp> connected_clients; //This vector contains all of the connected clients.
