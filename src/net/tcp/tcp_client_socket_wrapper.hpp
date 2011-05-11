/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Header file for the client socket wrapper.
 * ----------------------------------------------------------- */

#pragma once
#include "../../Engine.hpp"

class client
{
public:
	TCPsocket client_socket; //This is the socket.
	bool client_disconnect; //Does the client want to disconnect?
	char* buffer; //Stores the last message recieved from the client.
	SDLNet_SocketSet socketSet; //Makes it all work.
	bool activity; //Is there any need to update stuff?

	client()
	{
		client_disconnect = false;
		buffer = "";
		activity = false;
		socketSet = SDLNet_AllocSocketSet(1);
		client_socket = NULL;
	}
	~client()
	{
	}

	void update();
};

static std::vector<client> connected_clients; //This vector contains all of the connected clients.
