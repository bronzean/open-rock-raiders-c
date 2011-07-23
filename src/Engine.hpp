/* Copyright the ORR-C Dev Team */
//This is the main engine file.
//TODO: Continue organizing the engine's structure
//Remember, all the engine source files Start with an 'E'

#pragma once
#define DEBUG
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_net.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <fstream>
#include <sstream>
//#include <cstdarg>
#include <vector>
#include <pthread.h>
#include <memory>

#ifdef WIN32
#include <winsock2.h>
#else
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

//#include <SDL/SDL_rotozoom.h>
//#include <GL/glut.h>
#include "engine/EClass.hpp"
#include "engine/EPrototypes.hpp"
#include "engine/EDeclarations.hpp"
#include "engine/parser.hpp"

#define VERSION "0.0.4.2"

//The following two are a quick solution to unhardcoding tile size.
//TODO: REPLACE ALL HARDCODED TILE SIZES IN CODE WITH THESE TWO VARIABLE NAMES
#define tile_width 32
#define tile_height 32
