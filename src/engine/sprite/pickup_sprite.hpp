/* Copyright the ORR-C Dev Team */
#pragma once
#include "sprite.hpp"

class pickup_sprite: public sprite_wrapper
{
public:
	int centerx, centery; //The center of the image, relative to the image's top left corner.

	pickup_sprite() : sprite_wrapper() //Consructor
	{
		centerx = 0;
		centery = 0;
	}

	void draw_sprite(SDL_Surface* destination); //Draw itself.
};
