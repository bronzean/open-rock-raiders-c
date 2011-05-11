#include "tcputil.h"

/* receive a buffer from a TCP socket with error checking */
/* this function handles the memory, so it can't use any [] arrays */
/* returns 0 on any errors, or a valid char* on success */
char *getMsg(TCPsocket sock, char **buf)
{
	Uint32 len,result;
	static char *_buf;

	/* allow for a NULL buf, use a static internal one... */
	if(!buf)
		buf=&_buf;
	
	/* free the old buffer */
	//if(*buf)
	//	free(*buf);
	*buf=NULL;

	/* receive the length of the string message */
	result=SDLNet_TCP_Recv(sock,&len,sizeof(len));
	if(result<sizeof(len))
	{
		if(SDLNet_GetError() && strlen(&*SDLNet_GetError())) /* sometimes blank! */
			printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		return(NULL);
	}
	
	/* swap byte order to our local order */
	len=SDL_SwapBE32(len);
	
	/* check if anything is strange, like a zero length buffer */
	if(!len)
		return(NULL);

	/* allocate the buffer memory */
	*buf=(char*)malloc(len);
	if(!(*buf))
		return(NULL);

	/* get the string buffer over the socket */
	result=SDLNet_TCP_Recv(sock,*buf,len);
	if(result<len)
	{
		if(SDLNet_GetError() && strlen(&*SDLNet_GetError())) /* sometimes blank! */
			printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		free(*buf);
		buf=NULL;
	}

	/* return the new buffer */
	return(*buf);
}
