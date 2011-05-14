/* Copyright the ORR-C Dev Team */
#include "udp.hpp"
#include <stdio.h>
#include <string.h>
using namespace std;

#define ERROR (0xff)

int udp_send(UDPsocket sock, int channel, UDPpacket *out, UDPpacket *in, Uint32 delay, Uint8 expect, int timeout) //Send a packet.
{
	Uint32 t, t2; //Has to do with the timeout.
	int err = '\x00';
	
	in->data[0]=0;
	t = SDL_GetTicks();

	do
	{
		t2=SDL_GetTicks();

		if(t2-t > (Uint32)timeout)
		{
			cout <<  "Timed out\n";
			//pthread_mutex_unlock(&udp_send_lock);
			return 1;
		}

		pthread_mutex_lock(&udp_send_lock); //Makes it all work.
		if(!SDLNet_UDP_Send(sock, channel, out))
		{
			printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
			pthread_mutex_unlock(&udp_send_lock);
			return 1;
		}
		pthread_mutex_unlock(&udp_send_lock);

		/*err = SDLNet_UDP_Recv(sock, in);
		if(!err)
		{
			SDL_Delay(delay);
		}*/

		pthread_mutex_lock(&udp_send_lock); //Makes it all work.
		err = SDLNet_UDP_Recv(sock, in);
		pthread_mutex_unlock(&udp_send_lock);

		if(!err)
		{
			SDL_Delay(delay);
		}
	} 
	while(!err || (in->data[0] != expect && in->data[0] != ERROR));

	if(in->data[0] == ERROR)
	{
		printf("received error code\n");
	}

	return(in->data[0] == ERROR ? -1 : 1);
}
