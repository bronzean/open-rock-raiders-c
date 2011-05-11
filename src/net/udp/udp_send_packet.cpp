/* Copyright the ORR-C Dev Team */
#include "udp.hpp"
#include <stdio.h>
#include <string.h>
using namespace std;

#define ERROR (0xff)

int udp_send(UDPsocket sock, int channel, UDPpacket *out, UDPpacket *in, Uint32 delay, Uint8 expect, int timeout) //Send a packet.
{
	pthread_mutex_lock(&udp_send_lock);
	Uint32 t,t2;
	int err;
	
	in->data[0]=0;
	t=SDL_GetTicks();
	do
	{
		t2=SDL_GetTicks();
		if(t2-t>(Uint32)timeout)
		{
			printf("timed out\n");
			return(0);
		}
		if(!SDLNet_UDP_Send(sock, channel, out))
		{
			printf("SDLNet_UDP_Send: %s\n",SDLNet_GetError());
			exit(1);
		}
		err=SDLNet_UDP_Recv(sock, in);
		if(!err)
			SDL_Delay(delay);
	} while(!err || (in->data[0]!=expect && in->data[0]!=ERROR));
	if(in->data[0]==ERROR)
		printf("received error code\n");
	pthread_mutex_unlock(&udp_send_lock);
	return(in->data[0]==ERROR?-1:1);
}
