/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the unit header.
#include "../engine/Interface.hpp"
using namespace std;

/* --------------------------------------------------------------
 * The unit's draw sprite function is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::draw_sprite() //Draw the unit's sprite.
{
	if(allow_draw)
	{
		if(wx + width >= PCamera->wx && wx <= (PCamera->wx + SCREEN_WIDTH) && wy + height >= PCamera->wy && wy <= (PCamera->wy + SCREEN_HEIGHT) && layer == PCamera->layer) //If the sprite is onscreen...
		{
			if(active_animation) //If there's an ongoing animation.
			{
				//active_animation->draw_sprite(wx, wy, layer);
				//draw(wx - (PCamera->wx), wy - (PCamera->wy), frames_spr[current_frame], screen); //Draw the sprite.
				sprite_wrapper* _sprite = new sprite_wrapper;
				_sprite->wx = wx;
				_sprite->wy = wy;
				_sprite->image = active_animation->frames_spr[active_animation->current_frame];
				Interface.add_sprite_that_needs_drawing(_sprite);
			}
			else
			{
				if(allow_draw)
				{
					//if(carrying)
					draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite, screen); //Draw the 'normal' sprite.
				}
			}
			if(selected) //If it is selected...
			{
				//draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite_select, screen); //Draw the selection overlay.
				//cout << "Unit job state: " << job_state << "\n";

				sprite_wrapper* _sprite = new sprite_wrapper;
				_sprite->wx = wx;
				_sprite->wy = wy;
				_sprite->image = sprite_select;
				Interface.add_sprite_that_needs_drawing(_sprite);
			}
		}
		if(selected || player) //If the unit is selected...Or it is th player's unit...
		{
			if(tool_list.size() != 0) //If the unit's tool list size is not equal to 0.
			{
				draw_inventory(); //Let the player know what tools this guy is carrying.
			}

			cout << "Job state: " << job_state << "\n";
		}
	}
}
