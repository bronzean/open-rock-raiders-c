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
	//if(layer == PCamera->layer && wx + frames_spr[current_frame]->w >= PCamera->wx && wx <= (PCamera->wx + SCREEN_WIDTH) && wy + frames_spr[current_frame]->h >= PCamera->wy && wy <= (PCamera->wy + SCREEN_HEIGHT)) //If the sprite is on screen...
	//{
		draw(wx, wy, image, screen);
	//}
}
