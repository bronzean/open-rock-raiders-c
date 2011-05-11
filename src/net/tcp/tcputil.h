//COPYRIGHT SDL_NET DEMOS. THEY WROTE THIS .H FILE.
#ifndef tcputil_h
#define tcputil_h 1

#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include <stdio.h>
#include <string.h>

/* receive a buffer from a TCP socket with error checking */
/* this function handles the memory, so it can't use any [] arrays */
/* returns 0 on any errors, or a valid char* on success */
char *getMsg(TCPsocket sock, char **buf);

/* send a string buffer over a TCP socket with error checking */
/* returns 0 on any errors, length sent on success */
int putMsg(TCPsocket sock, char *buf);

#endif
