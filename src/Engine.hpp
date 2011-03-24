/* Copright the ORR-C Dev Team */
//This is the main engine file.
//TODO: Continue organizing the engine's structure
//Remember, all the engine source files Start with an 'E'

#pragma once
#define DEBUG
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <pthread.h>
//#include <SDL/SDL_rotozoom.h>
//#include <GL/glut.h>
#include "engine/EClass.hpp"
#include "engine/EPrototypes.hpp"
#include "engine/EDeclarations.hpp"
#include "engine/parser.hpp"

#define VERSION "0.0.2.7"
