/* Copyright the ORR-C Dev Team */
#include "tcp_client_socket_wrapper.hpp"
using namespace std;

#include "tcputil.h"

void client::update()
{
	SDLNet_CheckSockets(socketSet, 0); //Magical line that makes everything work.

	if(SDLNet_SocketReady(client_socket) != 0) //Checks if stuff happened.
	{
		activity = true;
	}

	if(activity)
	{
		cout << "Something happened (client socket).\n"; //Lets the user know something happened.

		/*int result = SDLNet_TCP_Recv(client_socket, buffer, 1024);
		cout << "Result: " << result << ", Buffer: " << buffer << "\n";

		if(result > 0) //Receive the data.
		{
			printf("Client say: %s\n", buffer); //Print the data.
 
			if(strcmp(buffer, "exit") == 0)	// Terminate this connection
			{
				client_disconnect = true; //Let the game know the client wants to disconnect.
				cout << "Client disconnected.\n";
				out_string << "Client disconnected.\n";
				SDLNet_TCP_Close(client_socket); //Close the socket.
			}
		}
		else
		{
			//Oh! Time to terminate this connection.
			SDLNet_TCP_DelSocket(socketSet, 0);
			SDLNet_TCP_Close(client_socket);
			client_disconnect = true;
			cout << "Client disconnected.\n";
			out_string << "Client disconnected.\n";
		}*/

		if(getMsg(client_socket, &buffer))
		{
			printf("Client say: %s\n", buffer); //Print the data.
 
			if(strcmp(buffer, "exit") == 0)	// Terminate this connection
			{
				client_disconnect = true; //Let the game know the client wants to disconnect.
				cout << "Client disconnected.\n";
				out_string << "Client disconnected.\n";
				SDLNet_TCP_Close(client_socket); //Close the socket.
			}
		}
		else
		{
			//Oh! Time to terminate this connection.
			SDLNet_TCP_DelSocket(socketSet, 0);
			SDLNet_TCP_Close(client_socket);
			client_disconnect = true;
			cout << "Client disconnected.\n";
			out_string << "Client disconnected.\n";
		}
	}
	activity = false;
	buffer = "";
}
