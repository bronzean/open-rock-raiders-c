/* Copyright the ORR-C Dev Team */
#include "client_socket_wrapper.hpp"
using namespace std;

void client::update()
{
	buffer = ""; //Clear the buffer.

	if (SDLNet_TCP_Recv(csd, buffer, 512) > 0)
	{
		printf("Client say: %s\n", buffer);
 
		if(strcmp(buffer, "exit") == 0)	// Terminate this connection
		{
			client_disconnect = true; //Let the game know the client wants to disconnect.
			cout << "Client disconnected.\n";
			out_string << "Client disconnected.\n";
			SDLNet_TCP_Close(csd); //Close the socket.
		}
	}
}
