/* Copyright the ORR-C Dev Team */
#include "pickup_sprite.hpp"

void pickup_sprite::draw_sprite(SDL_Surface* destination) //Draw itself.
{
	//Check if its onscreen.
	if(layer == PCamera->layer && wx + image->w >= PCamera->wx && wx <= (PCamera->wx + SCREEN_WIDTH) && wy + image->h >= PCamera->wy && wy <= (PCamera->wy + SCREEN_HEIGHT)) //If the sprite is on screen...
	{
		draw((wx + centerx) - (PCamera->wx), (wy + centery) - (PCamera->wy), image, destination);
	}
}
