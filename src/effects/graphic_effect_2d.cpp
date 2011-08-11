/* Copyright the ORR-C Dev Team */
#include "graphic_effect_2d.hpp"
#include "../engine/sprite/sprite.hpp"
#include "../engine/Interface.hpp"

graphic_effect_2d::graphic_effect_2d() //Constructor.
{
	wx = 0;
	wy = 0;
	layer = 0;
	the_animation = NULL;
}

graphic_effect_2d::~graphic_effect_2d() //Deconstructor.
{
}

void graphic_effect_2d::draw_self() //Draw the effect.
{
	sprite_wrapper* _sprite = new sprite_wrapper;
	_sprite->wx = wx;
	_sprite->wy = wy;
	_sprite->image = the_animation->frames_spr[the_animation->current_frame];
	Interface.add_sprite_that_needs_drawing(_sprite);
}

void graphic_effect_2d::animate() //Progress the animation.
{
	the_animation->proceed_animation(); //Progress the animation.
}

bool graphic_effect_2d::init(std::string folderpath) //Initialize this.
{
	if(!the_animation->load_settings(folderpath + "/animation.2dap")) //Load the effect's animation. With error checking.
	{
		return false;
	}

	return true;
}

graphic_effect_2d whiteflash1; //White flash #1.
