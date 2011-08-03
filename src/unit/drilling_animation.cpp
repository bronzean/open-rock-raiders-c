/* Copyright the ORR-C Dev Team */
#include "unit.hpp"

void bClassUnit::drilling_animation() //Handles animating the drilling animation.
{
	if(!paused)
	{
		cout << "Drilling animation.\n"; //Debugging output

		if(Map[mine_tile_id].wx < wx && drill_left)
		{
			//PROGRESS THE ANIMATION AS NEEDED.
			cout << "Blarg. Tile to left and has drill left animation.\n"; //Debugging output.

			active_animation = drill_left;

			if(drill_animation_frame_progress >= drill_time)
			{
				cout << "Progressing animation.\n";

				drill_left->proceed_animation();

				drill_animation_frame_progress = 0;
			}
			drill_animation_frame_progress++;
		}
		else if(Map[mine_tile_id].wx > wx && drill_right)
		{
			//PROGRESS THE ANIMATION AS NEEDED.
			cout << "Blarg. Tile to right and has drill right animation.\n"; //Debugging output.

			active_animation = drill_right;

			if(drill_animation_frame_progress >= drill_time)
			{
				cout << "Progressing animation.\n";

				drill_right->proceed_animation();

				drill_animation_frame_progress = 0;
			}
			drill_animation_frame_progress++;
		}
		else if(Map[mine_tile_id].wy < wy && drill_up)
		{
			//PROGRESS THE ANIMATION AS NEEDED.
			cout << "Blarg. Tile to north and has drill up animation.\n"; //Debugging output.

			active_animation = drill_up;

			if(drill_animation_frame_progress >= drill_time)
			{
				cout << "Progressing animation.\n";

				drill_up->proceed_animation();

				drill_animation_frame_progress = 0;
			}
			drill_animation_frame_progress++;
		}
		else if(Map[mine_tile_id].wy > wy && drill_down)
		{
			//PROGRESS THE ANIMATION AS NEEDED.
			cout << "Blarg. Tile to south and has drill down animation.\n"; //Debugging output.

			active_animation = drill_down;

			if(drill_animation_frame_progress >= drill_time)
			{
				cout << "Progressing animation.\n";

				drill_down->proceed_animation();

				drill_animation_frame_progress = 0;
			}
			drill_animation_frame_progress++;
		}
	}
}
