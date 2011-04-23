/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Header file for the client socket wrapper.
 * ----------------------------------------------------------- */

#pragma once
#include "../Engine.hpp"

class client
{
public:
	TCPsocket csd; //This is the socket.
	bool client_disconnect; //Does the client want to disconnect?
	char* buffer; //Stores the last message recieved from the client.

	client()
	{
		client_disconnect = false;
		buffer = "";
	}
	~client()
	{
	}

	void update();
};

static std::vector<client> connected_clients; //This vector contains all of the connected clients.
