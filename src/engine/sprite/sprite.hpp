/* Copyright the ORR-C Dev Team */
#pragma once
#include "../../Engine.hpp"

class sprite_wrapper
{
public:
	int wx, wy, layer; //Essentially the location of the sprite.
	SDL_Surface *image; //The sprite itself.

	sprite_wrapper(); //Constructor.
	~sprite_wrapper(); //Deconstructor.

	void draw_sprite(); //Draw itself.
};
