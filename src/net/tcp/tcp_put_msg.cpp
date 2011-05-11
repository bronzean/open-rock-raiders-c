#include "tcputil.h"

/* send a string buffer over a TCP socket with error checking */
/* returns 0 on any errors, length sent on success */
int putMsg(TCPsocket sock, char *buf)
{
	Uint32 len,result;

	if(!buf || !strlen(buf))
		return(1);

	/* determine the length of the string */
	len=strlen(&*buf)+1; /* add one for the terminating NULL */
	
	/* change endianness to network order */
	len=SDL_SwapBE32(len);

	/* send the length of the string */
	result=SDLNet_TCP_Send(sock,&len,sizeof(len));
	if(result<sizeof(len)) {
		if(SDLNet_GetError() && strlen(&*SDLNet_GetError())) /* sometimes blank! */
			printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return(0);
	}
	
	/* revert to our local byte order */
	len=SDL_SwapBE32(len);
	
	/* send the buffer, with the NULL as well */
	result=SDLNet_TCP_Send(sock,buf,len);
	if(result<len) {
		if(SDLNet_GetError() && strlen(&*SDLNet_GetError())) /* sometimes blank! */
			printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return(0);
	}
	
	/* return the length sent */
	return(result);
}
