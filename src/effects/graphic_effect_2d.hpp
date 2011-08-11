/* Copyright the ORR-C Dev Team */

#pragma once
#include "../Engine.hpp"

class graphic_effect_2d //It's a 2d graphical effect. Nuff said.
{
public:
	animation *the_animation; //The animation associated with this graphical effect.
	int wx, wy, layer; //The wx, wy, and layer this effect is taking place on.
	int time_per_frame; //The ammount of time spent per frame of the animation.
	int time_progress; //The ammount of time so far put into each frame.

	graphic_effect_2d(); //Constructor.
	~graphic_effect_2d(); //Deconstructor.

	void draw_self(); //Draw the effect.
	void animate(); //Progress the animation.

	bool init(std::string folderpath); //Initialize this.
};

bool load_2d_graphics_effects(); //Load all the 2d graphical effects.

void create_flash(int x, int y, int layer, graphic_effect_2d *flash); //Create a flash that will be centered at the specified location.

extern graphic_effect_2d whiteflash1; //White flash #1.

extern std::vector<graphic_effect_2d> active_2d_graphic_effects; //It's a vector of all the active 2d graphical effects on the map.
