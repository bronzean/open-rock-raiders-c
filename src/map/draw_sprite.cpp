/* Copyright the ORR-C Dev Team */
#include "tile.hpp"

void tile::draw_sprite()
{
	if(layer == PCamera->layer && get_wx() + get_width() >= PCamera->wx && get_wx() <= (PCamera->wx + SCREEN_WIDTH) && get_wy() + get_height() >= PCamera->wy && get_wy() <= (PCamera->wy + SCREEN_HEIGHT) && allow_draw)
	{
		if(active_animation == true) //If an animation is going on...
		{
			cout << "Animated tile ID: " << ID << "\n";
			/*if(active_animation_entry == drilling_animation_entry && animations[drilling_animation_entry].current_frame == 0) //If the current animation is the drilling animation, then...
			{
				animations[drilling_animation_entry].proceed_animation(); //Increase the animation thingy.
			}*/
			animations[active_animation_entry].draw_sprite(wx, wy, layer);
		}
		else //If not, draw the 'normal' sprite.
		{
			draw(get_wx() - (PCamera->wx), get_wy() - (PCamera->wy), sprite, screen); //Draw the sprite of the tile itself.
		}
		if(orelist.size() != 0) //If it has ore on it.
		{
			draw(wx - (PCamera->wx), wy - (PCamera->wy), orelist[orelist.size() - 1].sprite, screen); //Draw the ore's sprite.
		}
		if(has_construction) //If the tile has a construction.
		{
			//draw(get_wx() - (PCamera->wx), get_wy() - (PCamera->wy), local_construction->sprite, screen);
			local_construction->draw_sprite(wx, wy, layer); //Draw the construction's sprite.
		}
		else if(construction_in_progress) //If a construction is in progress.
		{
			if(construction_in_progress_animation)
			{
				construction_in_progress_animation->draw_sprite(wx, wy, layer);
			}
		}
		else if(qued_construction) //If it has a qued construction on it.
		{
			draw(wx - (PCamera->wx), wy - (PCamera->wy), qued_construction_sprite, screen);
		}
		if(unitlist.size() != 0) //If the tile has units on it.
		{
			for(int i = 0; i < unitlist.size(); i++)
			{
				unitlist[i].draw_sprite(); //Draw the topmost unit's sprite.
			}
		}
	}
}
