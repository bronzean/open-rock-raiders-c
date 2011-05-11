/* Copyright the ORR-C Dev Team */
#include "tcp_client_socket_wrapper.hpp"
#include <stdio.h>
#include <string.h>
using namespace std;

/*void *ServerNetworking(void *param) //TODO: Write this function.
{
	TCPsocket sd; //The socket used for the server.
	SDLNet_SocketSet sd_set; //The socket set used for the server.
	sd_set = SDLNet_AllocSocketSet(max_clients); //Sets the size of sd_set.

	cout << "\nBinding to port...\n";
	//Resolving the host using NULL make network interface to listen
	if(SDLNet_ResolveHost(&ip, NULL, port_number) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return false;
	}

	cout << "Port number: " << port_number << "\n";
	//Open a connection with the IP provided (listen on the host's port)
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		return false;
	}
	SDLNet_TCP_AddSocket(sd_set, sd);
	cout << "Done, son.\n";

	while(!gameover)
	{
		cout << "\nNetwork update tick.\n";
		SDL_Delay(client_update_interval);

		//This checks the sd if there is a pending connection. If there is one, accept that, and open a new socket for communicating
		//if((csd = SDLNet_TCP_Accept(sd)))
		//{
			//Now we can communicate with the client using csd socket sd will remain opened waiting other connections
 
			//Get the remote address
			//if((remoteIP = SDLNet_TCP_GetPeerAddress(csd)))
			//{
			//	//Print the address, converting in the host format
			//	printf("Client connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
			//}
			//else
			//{
			//	fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
			//}
		//}

		//Alright, here's what happens.


		if((csd = SDLNet_TCP_Accept(sd))) //This calculates as true if there's a pending connection.
		{
			cout << "Client connected\n";

			int len,result;
			string msg = "Hello, new client!";

			len=msg.size() + 1; // add one for the terminating NULL
			result=SDLNet_TCP_Send(csd,msg.c_str(),len);
			if(result<len)
			{
    				printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
   				SDLNet_TCP_Close(csd); //Close the socket, since something done borked.
				cout << "Disconnected client, seeing that something done borked.\n";
			}
			else
			{
				//Now a new member is added to the connected_clients vector.
				client new_client; //This is the new client.
				new_client.csd = csd; //Copy over the client socket descriptor.
				connected_clients.push_back(new_client); //Here is where the new member is added into connected_clients.
				//csd = NULL;
			}
		}

		bool redo_loop = false;
		do
		{
			redo_loop = false;
			for(int i = 0; i < connected_clients.size(); i++)
			{
				if(!redo_loop)
				{
					connected_clients[i].update(); //Update the client.

					//if(connected_clients[i].client_disconnect == true) //If the client wants to disconnect...
					//{
						//cout << "Removing from connected clients list...\n";
						//connected_clients.erase(connected_clients.begin() + i); //Disconnect the client.
						//i = connected_clients.size();
						//redo_loop = true;
					//}
				}
			}
		}
		while(redo_loop);
	}
 
	//Close the client socket
	//SDLNet_TCP_Close(csd);

	pthread_exit(NULL);
}*/

void *ServerNetworking(void *param)
{
	bool server_activity = false; //Server socket receieved any data?

	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(max_clients); //This socket set contains all the sockets...
	if(socketSet == NULL) //Checks if allocating the socketSet was successful or not.
	{
		//Error! Error!
		cout << "Failed to allocate the socket set: " << SDLNet_GetError() << "\n";
		out_string << "Failed to allocate the socket set: " << SDLNet_GetError() << "\n";
		gameover = true; //Makes the entire game quit.
		pthread_exit(NULL); //ERROR! CLOSE THIS THREAD.
	}

	//Yay, it was successful. Let the user know that.
	cout << "Allocated socket set with size:  " << max_clients << "\n";
	out_string << "Allocated socket set with size: " << max_clients << "\n";

	cout << "\nBinding to port...\n"; //Blablabla, debugging output.
	if(SDLNet_ResolveHost(&serverIP, NULL, port_number)) //Resolve the host.
	{
		//Error! Error! Abort! Abort!
		cout << "Failed to bind to port: " << SDLNet_GetError() << "\n";
		out_string << "Failed to bind to port: " << SDLNet_GetError() << "\n";
		gameover = true; //Makes the entire game quit.
		pthread_exit(NULL); //ERROR! CLOSE THIS THREAD.
	}
	Uint8 * dotQuad = (Uint8*)&serverIP.host; //Splits the IP of the host into something readable.
	cout << "\nSuccessfully resolved server host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3] << " port " << SDLNet_Read16(&serverIP.port) << "\n";
	out_string << "\nSuccessfully resolved server host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3] << " port " << SDLNet_Read16(&serverIP.port) << "\n";
	cout << "Done, son.\n"; //Yay, all done with the bind to port stuff. Let the user know that.

	serverSocket = SDLNet_TCP_Open(&serverIP); //Open the server socket.
	if(!serverSocket) //Error checking.
	{
		//ERROR! ERROR! FLY AWAY!
		cout << "Failed to open the server socket: " << SDLNet_GetError() << "\n";
		out_string << "Failed to open the server socket: " << SDLNet_GetError() << "\n";
		gameover = true; //Makes the entire game quit.
		pthread_exit(NULL); //ERROR! FLY FLY FLY AWAY!
	}

	SDLNet_TCP_AddSocket(socketSet, serverSocket);

	while(!gameover)
	{
		cout << "\nNetwork update tick.\n"; //Lets the user know this thread is still running.
		SDL_Delay(client_update_interval); //Delay...Don't want this thread to eat the CPU.

		//TODO: What needs to be done?
		//1. Check if a new client connected.
		//2. Check what clients have disconnected
		//3. Update all clients.
		//How will this be done? Let's see...

		SDLNet_CheckSockets(socketSet, 0); //Magical line that makes it all work.

		if(SDLNet_SocketReady(serverSocket) != 0) //Check if the server socket has received any data.
		{
			server_activity = true;
			cout << "Something happened.\n";
		}

		if(server_activity) //Check if something happened.
		{
			cout << "Client connected.\n";
			//Ok. That means somebody connected. Add the new client to the client list.
			client new_client; //The new client.
			connected_clients.push_back(new_client); //Add it to the connected_clients vector.
			connected_clients[connected_clients.size() - 1].client_socket = SDLNet_TCP_Accept(serverSocket); //Accept the new connection.
			SDLNet_TCP_AddSocket(connected_clients[connected_clients.size() - 1].socketSet, connected_clients[connected_clients.size() - 1].client_socket); //Makes stuff work.

			//Alright, now send the welcome message.
			int len,result; //len: the length of the string. result: used for error checking.
			string msg = "Hello, new client!"; //The string sent to the client on connect. Doesn't need identifier.

			len=msg.size(); //Get the length of the string.
			result=SDLNet_TCP_Send(connected_clients[connected_clients.size() - 1].client_socket,msg.c_str(),len); //Send the message and save the result.

			//Error checking here.
			if(result<len)
			{
    				printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError()); //ERROR! ERROR! MUST TELL USER!
   				SDLNet_TCP_Close(connected_clients[connected_clients.size() - 1].client_socket); //Close the socket, since something done borked.
				cout << "Disconnected client, seeing that something done borked.\n";
				out_string << "Disconnected client, seeing that something done borked.\n";
				connected_clients.pop_back(); //Remove this client, since it done failed.
			}
			server_activity = false;
		}

		for(int i = 0; i < connected_clients.size(); i++) //Here the clients are updated.
		{
			cout << "\nUpdating client: " << i << "\n";
			connected_clients[i].update(); //Calls the function that updates that specific client.

			if(connected_clients[i].client_disconnect) //Checks if the client has disconnected...
			{
				//Client has disconnected. Get rid of it.
				cout << "Removing " << i << " from connected clients list...\n"; //Debugging output.
				connected_clients.erase(connected_clients.begin() + i); //Remove the client from connected_clients.
				i--; //Since a member has just been erased, we gotta account for that. The vector shrunk in size by one. If this isn't done, the loop will skip the member after the one that was just removed.
				cout << "Done!\n"; //Yay, done. Let the user know.
			}
		}
	}

	SDLNet_FreeSocketSet(socketSet); //Free the socket set.
	SDLNet_TCP_Close(serverSocket); // Close the server socket.
	SDLNet_Quit(); //Quit SDL net...
	pthread_exit(NULL);
}
