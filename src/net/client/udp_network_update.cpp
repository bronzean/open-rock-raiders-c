/* Copyright the ORR-C Dev Team */
#include "../udp/udp.hpp"
#include <stdio.h>
#include <string.h>
using namespace std;

void *ClientNetworkingUdp(void *param)
{
	cout << "In network update\n";
	Uint16 port = 0;
	char *host = "";
	Sint32 flen = 0;
	Sint32 pos = 0;
	Sint32 p2 = 0;
	int len = 0;
	int blocks = 0;
	int i = 0;
	int err = 0;
	Uint32 ack = 0;
	IPaddress ip;
	UDPsocket sock = NULL;
	UDPpacket *packet_in = NULL;
	UDPpacket *packet_out = NULL;
	double PACKET_SIZE = 65535;
	sock = NULL;

	host = (char *)"localhost"; //"host" is the IP of the server.
	port = 2097; //"port" is the port of the server
 
	if(SDLNet_ResolveHost(&ip, host, port) == -1) //Connect to server. With error checking.
	{
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		gameover = true;
		pthread_exit(NULL);
	}

	if(!(sock = SDLNet_UDP_Open(0))) //Open the socket. With error checking.
	{
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		gameover = true;
		pthread_exit(NULL);
	}

	if(SDLNet_UDP_Bind(sock, 0, &ip) == -1) //Bind the server address to channel 0. With error checking.
	{
		printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
		gameover = true;
		pthread_exit(NULL);
	}

	if(!(packet_in = SDLNet_AllocPacket(PACKET_SIZE))) //Allocate memory for the UDP packet. With error checking.
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		out_string << "SDLNet_AllocPacket: %s\n" << SDLNet_GetError() << "\n"; //Let the user know something failed.
		gameover = true; //Tells the game to quit.
		pthread_exit(NULL); //KILL THIS THREAD.
	}

	if(!(packet_out = SDLNet_AllocPacket(PACKET_SIZE))) //Allocate memory for the UDP packet. With error checking.
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		out_string << "SDLNet_AllocPacket: %s\n" << SDLNet_GetError() << "\n"; //Let the user know something failed.
		gameover = true; //Tells the game to quit.
		pthread_exit(NULL); //KILL THIS THREAD.
	}

	char message = '\x01';
	packet_out->data[0] = '\x01'; //Tells the server, "Hi!\n";

	if(udp_send(sock, 0, packet_out, packet_in, 200, '\x01', 5000) < 1)
	{
		cout << "Failed to send packet. :|\nTrying again...\n";
		if(udp_send(sock, 0, packet_out, packet_in, 200, '\x01', 1000) < 1)
		{
			cout << "Failed to send packet. Again. :|\n";
		}
	}

	//cout << "Recieved: " << (char*) packet_in->data << "\n";

	if(packet_in->data[0] == '\x02')
	{
		cout << "Recieved string: ";

		for(int i = 1; i < PACKET_SIZE; i++)
		{
			cout << packet_in->data[i];
		}

		cout << "\n";
	}
 
	SDLNet_FreePacket(packet_in); //Free the UDP packet.
	SDLNet_FreePacket(packet_out); //Free the UDP packet.
	//SDLNet_FreeSocketSet(socketSet); //Free the socket set.
	SDLNet_Quit(); //Quit SDL net...
	pthread_exit(NULL);
}
