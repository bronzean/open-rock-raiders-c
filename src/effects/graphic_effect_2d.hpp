/* Copyright the ORR-C Dev Team */

#pragma once
#include "../Engine.hpp"

class graphic_effect_2d //It's a 2d graphical effect. Nuff said.
{
public:
	animation *the_animation; //The animation associated with this graphical effect.
	int wx, wy, layer; //The wx, wy, and layer this effect is taking place on.

	graphic_effect_2d(); //Constructor.
	~graphic_effect_2d(); //Deconstructor.

	void draw_self(); //Draw the effect.
	void animate(); //Progress the animation.

	bool init(std::string folderpath); //Initialize this.
};

bool load_2d_graphics_effects(); //Load all the 2d graphical effects.

extern graphic_effect_2d whiteflash1; //White flash #1.
