/* Copyright the ORR-C Dev Team */
#include "udp_client_socket_wrapper.hpp"
#include "udp.hpp"
#include <stdio.h>
#include <string.h>
using namespace std;

void *ServerNetworkingUdp(void *param)
{
	const char *host = NULL; //Not sure yet.
	UDPsocket udp_server_socket; //The UDP server socket.
	UDPpacket *packet_in, *packet_out; //Pointer to the UDP packet.
	IPaddress ip; //The IPAddress of...Something...I believe the client that just connected.
	Uint16 port = 0; //The port of the client that just connected.
	Uint32 ipnum = 0; //The ip of the client that just connected.
	//int TIMEOUT = 10;
 
	if(!(udp_server_socket = SDLNet_UDP_Open(port_number))) //Bind to port. With error checking.
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError()); //Let the user know something failed.
		out_string << "SDLNet_UDP_Open: " << SDLNet_GetError() << "\n"; //Let the user know something failed.
		gameover = true; //Tells the game to quit.
		pthread_exit(NULL); //KILL THIS THREAD.
	}
	cout << "Listening on port " << port_number << "\n"; //Let the user know we got somewhere.
	out_string << "Listening on port " << port_number << "\n";

	if(!(packet_in = SDLNet_AllocPacket(65535))) //Allocate memory for the UDP packet. With error checking.
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		out_string << "SDLNet_AllocPacket: %s\n" << SDLNet_GetError() << "\n"; //Let the user know something failed.
		gameover = true; //Tells the game to quit.
		pthread_exit(NULL); //KILL THIS THREAD.
	}

	if(!(packet_out = SDLNet_AllocPacket(65535))) //Allocate memory for the UDP packet. With error checking.
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		out_string << "SDLNet_AllocPacket: %s\n" << SDLNet_GetError() << "\n"; //Let the user know something failed.
		gameover = true; //Tells the game to quit.
		pthread_exit(NULL); //KILL THIS THREAD.
	}

	while(!gameover)
	{
		//cout << "\nUDP Network update tick.\n"; //Lets the user know this thread is still running.
		//cout << "Update pause (in MS): " << client_update_interval << "\n";
		SDL_Delay(client_update_interval); //Delay...Don't want this thread to eat the CPU.
		//cout << "Doing stuff.\n";

		//Now check for new data/connections.
		SDLNet_UDP_Unbind(udp_server_socket, 0); //Unbind the server socket.
		packet_in->data[0]=0;

		if(!SDLNet_UDP_Recv(udp_server_socket, packet_in))
		{
			//cout << "No packet.\n";
		}
		else
		{
			cout << "\nReceived packet. Do stuff here.\n";
			cout << "packet_in contains: " << packet_in->data << "\n";

			memcpy(&ip,&packet_in->address, sizeof(IPaddress));
			host = SDLNet_ResolveIP(&ip);
			//ipnum=SDL_SwapBE32(ip.host);
			ipnum = SDLNet_Read32(&ip.host);
			port = SDL_SwapBE16(ip.port);

			//TODO: 1. Check if the IP and Port match any already connected clients.
			// 2. If yes, then read what the client has to say.
			// 3. If not, add it to the connected clients lsit.

			if(host)
			{
				//printf("Request from Host=%s Port=%hd\n",host,port);
				cout << "Request from Host = " << host << " Port = " << port << "\n";
			}
			else
			{
				printf("Request from host=%d.%d.%d.%d Port=%hd\n", ipnum>>24, (ipnum>>16)&0xff, (ipnum>>8)&0xff, ipnum&0xff, port);
			}

			if(SDLNet_UDP_Bind(udp_server_socket, 0, &ip)==-1) //Rebind. With error checking.
			{
				printf("SDLNet_UDP_Bind: %s\n",SDLNet_GetError());
				gameover = true;
				pthread_exit(NULL);
			}

			packet_out->data[0] = '\x01';
			cout << "Attempting to send...\n";

			pthread_mutex_t udp_send_lock2;
			pthread_mutex_init(&udp_send_lock2, NULL); //Magical line that makes UDP_Send work.
			pthread_mutex_lock(&udp_send_lock2); //Makes it all work.
			if(!SDLNet_UDP_Send(udp_server_socket, 0, packet_out))
			{
				printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
				pthread_mutex_unlock(&udp_send_lock2);
			}
			else
			{
				pthread_mutex_unlock(&udp_send_lock2);
				string to_send = "Hello, new client!";

				packet_out->data[0] = '\x02'; //Lets the client know this is a string. '\x02' signifies it's a string.

				for(int i = 0; i < to_send.size(); i++)
				{
					packet_out->data[i+1] = (int)to_send[i]; //Convert message to int and store in packet_out.
					//Doesn't start at 0 becuase the first byte lets the client know this is a string.
				}

				//cout << "To send: " << packet_out->data << "\n";
				cout << "To send: ";

				/*for(int i = 1; i < sizeof(packet_out->data); i++)
				{
					cout << packet_out->data[i];
				}*/

				for(int i = 0; i < to_send.size(); i++)
				{
					cout << packet_out->data[i+1];
				}
				cout << "\n";

				//SDLNet_Write32(1, packet_out->data[1]); //So now write some data in here. Simply says "Hey, you connected."
				//if(!SDLNet_UDP_Send(udp_server_socket, 0, packet_out))
				//{
				//	printf("SDLNet_UDP_Send: %s\n",SDLNet_GetError());
				//	gameover = true;
				//	pthread_exit(NULL);
				//}
				if(!udp_send(udp_server_socket, 0, packet_out, packet_in, 0, '\x01', 5000)) //TODO: Make a seperate thread do this. //For the expect thing, '\x01' simply means "Got your message!"
				{
					cout << "Sent welcome message!\n";
				}

				//packet_out->data = NULL;
				//packet_in->data = NULL;
			}

			//pthread_mutex_destroy(&udp_send
		}

		//So, how does this figure out which client just sent a packet to it?
		//Each client wrapper stores the IP of that client. We can retrieve the IP of the packet sender. Match those and you know who sent it.

		
 
		/*if(!(udp_server_socket = SDLNet_UDP_Open(port_number))) //Bind to port. With error checking.
		{
			fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError()); //Let the user know something failed.
			out_string << "SDLNet_UDP_Open: " << SDLNet_GetError() << "\n"; //Let the user know something failed.
			gameover = true; //Tells the game to quit.
			pthread_exit(NULL); //KILL THIS THREAD.
		}*/
	}
 
	SDLNet_FreePacket(packet_in); //Free the UDP packet.
	SDLNet_FreePacket(packet_out);
	//SDLNet_FreeSocketSet(socketSet); //Free the socket set.
	SDLNet_Quit(); //Quit SDL net...
	pthread_exit(NULL);
}
