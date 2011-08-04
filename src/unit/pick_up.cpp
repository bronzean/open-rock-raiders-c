/* Copyright the ORR-C Dev Team */
#include "unit.hpp"

void bClassUnit::_pick_up() //Picks up objects. Well. Does the timing stuff, and the animating, if the unit has an animation.
{
	if(!paused)
	{
		if(pick_up) //If it has a pick up animation
		{
			//PROGRESS THE ANIMATION AS NEEDED.
			cout << "Blarg. Pick up animation.\n"; //Debugging output.

			active_animation = pick_up;

			if(pickup_progress >= pickup_time && pick_up->current_frame < pick_up->num_frames - 1)
			{
				cout << "Progressing animation.\n";

				pick_up->proceed_animation();

				pickup_progress = 0;
			}
			pickup_progress++;

			if(pickup_progress >= pickup_time && pick_up->current_frame >= pick_up->num_frames - 1)
			{
				//THE WHATEVER IS PICKED UP.
				cout << "Yay. Picked up. Go throw a party or something. *sarcasm*\n"; //Debugging output.

				pickup_progress = 0; //Reset this.
				picked_up = true; //Let the game know this unit has picked something up.
				pick_up->current_frame = 0;
			}
		}
		else
		{
			if(pickup_progress >= pickup_time)
			{
				cout << "Picked up!\n";

				picked_up = true;

				pickup_progress = 0;
			}
			pickup_progress++;
		}
	}
}
