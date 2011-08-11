/* Copyright the ORR-C Dev Team */
#include "graphic_effect_2d.hpp"

bool load_2d_graphics_effects() //Load all the 2d graphical effects.
{
	if(!whiteflash1.init("data/effects/flash/flash-white-1/")) //Initialize the effect. With error checking.
	{
		gameover = true;
		return false;
	}
	whiteflash1.time_per_frame = 1; //Set the time spent per frame of the flash's animation.

	return true;
}
