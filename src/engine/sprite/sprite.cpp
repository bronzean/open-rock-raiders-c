/* Copyright the ORR-C Dev Team */
#pragma once
#include "sprite.hpp"


sprite_wrapper::sprite_wrapper() //Constructor.
{
	wx = 0;
	wy = 0;
	layer = 0;
	image = NULL;
}

sprite_wrapper::~sprite_wrapper() //Deconstructor.
{
}

void sprite_wrapper::draw_sprite() //Draw itself.
{
	//Check if its onscreen.
	if(layer == PCamera->layer && wx + image->w >= PCamera->wx && wx <= (PCamera->wx + SCREEN_WIDTH) && wy + image->h >= PCamera->wy && wy <= (PCamera->wy + SCREEN_HEIGHT)) //If the sprite is on screen...
	{
		draw(wx - (PCamera->wx), wy - (PCamera->wy), image, screen);
	}
}
