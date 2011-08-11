/* Copyright the ORR-C Dev Team */
#include "graphic_effect_2d.hpp"

bool load_2d_graphics_effects() //Load all the 2d graphical effects.
{
	if(!whiteflash1.init("data/effects/flash/flash-white-1")) //Initialize the effect. With error checking.
	{
		gameover = true;
		return false;
	}

	return true;
}
