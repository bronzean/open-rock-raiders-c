/* Copyright the ORR-C Dev Team */
#include "../Engine.hpp"
#include <stdio.h>
#include <string.h>
#include "client_socket_wrapper.hpp"
using namespace std;

void *NetworkUpdate(void *param) //TODO: Write this function.
{
	vector<TCPsocket> sd;
	cout << "\nBinding to port...\n";
	/* Resolving the host using NULL make network interface to listen */
	if(SDLNet_ResolveHost(&ip, NULL, port_number) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return false;
	}

	cout << "Port number: " << port_number << "\n";
	TCPsocket new_socket;
	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(new_socket = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		return false;
	}
	sd.push_back(new_socket);
	cout << "Done, son.\n";

	while(!gameover)
	{
		cout << "\nNetwork update tick.\n";
		SDL_Delay(client_update_interval);

		//This checks the sd if there is a pending connection. If there is one, accept that, and open a new socket for communicating
		/*if((csd = SDLNet_TCP_Accept(sd)))
		{
			//Now we can communicate with the client using csd socket sd will remain opened waiting other connections
 
			//Get the remote address
			if((remoteIP = SDLNet_TCP_GetPeerAddress(csd)))
			{
				//Print the address, converting in the host format
				printf("Client connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
			}
			else
			{
				fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
			}
		}*/

		//Alright, here's what happens.

		for(int i = 0; i < sd.size(); i++)
		{
			if((csd = SDLNet_TCP_Accept(sd[i]))) //This calculates as true if there's a pending connection.
			{
				//Now a new member is added to the connected_clients vector.

				client new_client; //This is the new client.
				new_client.csd = csd; //Copy over the client socket descriptor.
				connected_clients.push_back(new_client); //Here is where the new member is added into connected_clients.
				cout << "Client connected\n";

				int len,result;
				char *msg="Hello, new client!";

				len=strlen(msg)+1; // add one for the terminating NULL
				result=SDLNet_TCP_Send(csd,msg,len);
				if(result<len)
				{
    					printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
   					// It may be good to disconnect sock because it is likely invalid now.
				}

				csd = NULL;
			}
		}

		for(int i = 0; i < connected_clients.size(); i++)
		{
			connected_clients[i].update(); //Update the client.

			if(connected_clients[i].client_disconnect == true) //If the client wants to disconnect...
			{
				connected_clients.erase(connected_clients.begin() + i); //Disconnect the client.
			}
		}
	}
 
	//Close the client socket
	/*SDLNet_TCP_Close(csd);*/

	pthread_exit(NULL);
}
