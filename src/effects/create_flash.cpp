/* Copyright the ORR-C Dev Team */
#include "graphic_effect_2d.hpp"

void create_flash(int x, int y, int layer, graphic_effect_2d *flash) //Create a flash that will be centered at the specified location.
{
	graphic_effect_2d new_effect; //New 2d grpahical effect.
	new_effect = *flash; //Copy over the data.
	new_effect.the_animation = new animation;
	*new_effect.the_animation = *flash->the_animation;

	int new_x, new_y; //The new x and y of the flash.

	new_x = x - (new_effect.the_animation->frames_spr[0]->w / 2); //Center the x.
	new_y = y - (new_effect.the_animation->frames_spr[0]->h / 2); //Center the y.

	new_effect.wx = new_x; //Save the new x.
	new_effect.wy = new_y; //Save the new y.
	new_effect.layer = layer; //Save the layer.

	active_2d_graphic_effects.push_back(new_effect); //Store the new effect in this.
}
