/* Copyright the ORR-C Dev Team */
#include "unit.hpp"

void bClassUnit::shoveling_animation() //Handles animating the shovelng animation.
{
	if(!paused)
	{
		if(shovel_animation)
		{
			//PROGRESS THE ANIMATION AS NEEDED.
			cout << "Blarg. Shoveling animation.\n"; //Debugging output.

			active_animation = shovel_animation;

			if(shovel_animation_frame_progress >= shovel_time)
			{
				cout << "Progressing animation.\n";

				shovel_animation->proceed_animation();

				shovel_animation_frame_progress = 0;
			}
			shovel_animation_frame_progress++;
		}
	}
}
