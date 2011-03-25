/* Copright the ORR-C Dev Team */
//This file includes all of the prototypes.
#pragma once
#include "../Engine.hpp"
#include "EObject.hpp"

//draw the image
void draw(int x, int y, SDL_Surface* source, SDL_Surface* destination);
void draw2(int x, int y, SDL_Surface* source, SDL_Surface* destination);

/*
//TODO: Write an image scaling function here
//draw the image scaled
//void ShrinkPicture (SDL_Surface *screen, SDL_Surface *picture);
*/

//Clean up the resources, must be defined in the game's code
void clean_up();

//Load a regular bmp. Only displays transparency if it is in the file.
SDL_Surface *img_load(std::string filename);
//Load an image and coler key it to add transparency. Don't load prealpha'd images
SDL_Surface *img_load2(std::string filename);
//Load a wide assortment of images
SDL_Surface *img_load3(std::string filename);

//startup the program
bool startup(bool fullscreen, int screen_w, int screen_h, int screen_bpp, std::string screen_capt, bool load_from_cfg);
//load the settings from the cfg
bool load_settings();

extern size_t strlen(/*const*/ char *string);
extern char *strrev(char *);
extern char *itoa(int, char *, int);
