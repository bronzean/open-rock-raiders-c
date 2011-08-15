/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the unit header.
#include "../engine/Interface.hpp"
#include "../engine/sprite/pickup_sprite.hpp"
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

				/*if(active_animation == pick_up) //Check if the active animation is the pick up animation.
				{
					if(pick_up_objects_sprite) //Check if the object being picked up has a pick up version of its sprite.
					{
						//SDL_Surface* overlay = NULL;

						//overlay = pick_up_objects_sprite->image;

						//pick_up_objects_sprite->draw_self(wx, wy, layer, overlay)

						pickup_sprite* _pickup_sprite = new pickup_sprite;
						*_pickup_sprite = *pick_up_objects_sprite;

						_pickup_sprite->wx = wx;
						_pickup_sprite->wy = wy;
						_pickup_sprite->layer = layer;
						Interface.add_sprite_that_needs_drawing(_pickup_sprite);
					}
				}*/

			}
			else
			{
				if(allow_draw)
				{
					//if(carrying)
					if(carrying_resource)
					{
						//Check if it's carrying ore and draw the carrying ore sprite.

						if(sprite_ore_up && heading == 0)
						{
							draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite_ore_up, screen); //Draw the 'carrying ore up' sprite.
						}
						else if(sprite_ore_right && heading == 90)
						{
							draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite_ore_right, screen); //Draw the 'carrying ore right' sprite.
						}
						else if(sprite_ore_down && heading == 180)
						{
							//cout << "Sprite ore down.\n";
							draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite_ore_down, screen); //Draw the 'carrying ore down' sprite.
						}
						else if(sprite_ore_left && heading == 270)
						{
							draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite_ore_left, screen); //Draw the 'carrying ore left' sprite.
						}
						else
						{
							draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite, screen); //Draw the normal sprite sprite.
						}
					}
					else
					{
						if(sprite_up && heading == 0)
						{
							draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite_up, screen); //Draw the 'facing up' sprite.
						}
						else if(sprite_right && heading == 90)
						{
							draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite_right, screen); //Draw the 'facing right' sprite.
						}
						else if(sprite_left && heading ==270)
						{
							draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite_left, screen); //Draw the 'facing left' sprite.
						}
						else
						{
							draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite, screen); //Draw the 'normal/facing down' sprite.
						}
					}
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
			if(object_list.size() != 0) //If the unit's tool list size is not equal to 0.
			{
				draw_inventory(); //Let the player know what tools this guy is carrying.
			}

			cout << "Job state: " << job_state << "\n";
		}
	}
}
