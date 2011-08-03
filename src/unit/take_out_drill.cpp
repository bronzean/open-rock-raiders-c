/* Copyright the ORR-C Dev Team */
#include "unit.hpp"

void bClassUnit::take_out_drill() //Take out its drill.
{
	cout << "Taking out drill.\n"; //Debugging output

	if(Map[mine_tile_id].wx < wx && takeout_drill_left)
	{
		//PROGRESS THE ANIMATION AS NEEDED.
		cout << "Blarg. Tile to left and has takeout drill left animation.\n"; //Debugging output.

		active_animation = takeout_drill_left;

		if(take_out_drill_progress >= take_out_drill_time && takeout_drill_left->current_frame < takeout_drill_left->num_frames - 1)
		{
			cout << "Progressing animation.\n";

			takeout_drill_left->proceed_animation();

			take_out_drill_progress = 0;
		}
		take_out_drill_progress++;

		if(take_out_drill_progress >= take_out_drill_time && takeout_drill_left->current_frame >= takeout_drill_left->num_frames - 1)
		{
			//THE DRILL IS OUT.
			cout << "Yay. Drill out. Now go slap yourself silly. Er, I mean, watch your raider drill das wall.\n"; //Debugging output.

			take_out_drill_progress = 0; //Reset this.
			drill_out = true; //Let the game know this unit has its drill out.
			takeout_drill_left->current_frame = 0;
		}
	}
	else if(Map[mine_tile_id].wx > wx && takeout_drill_right)
	{
		//PROGRESS THE ANIMATION AS NEEDED.
		cout << "Blarg. Tile to right and has takeout drill right animation.\n"; //Debugging output.

		active_animation = takeout_drill_right;

		if(take_out_drill_progress >= take_out_drill_time && takeout_drill_right->current_frame < takeout_drill_right->num_frames - 1)
		{
			cout << "Progressing animation.\n";

			takeout_drill_right->proceed_animation();

			take_out_drill_progress = 0;
		}
		take_out_drill_progress++;

		if(take_out_drill_progress >= take_out_drill_time && takeout_drill_right->current_frame >= takeout_drill_right->num_frames - 1)
		{
			//THE DRILL IS OUT.
			cout << "Yay. Drill out. Now go slap yourself silly. Er, I mean, watch your raider drill das wall.\n"; //Debugging output.

			take_out_drill_progress = 0; //Reset this.
			drill_out = true; //Let the game know this unit has its drill out.
			takeout_drill_right->current_frame = 0;
		}
	}
	else if(Map[mine_tile_id].wy < wy && takeout_drill_up)
	{
		//PROGRESS THE ANIMATION AS NEEDED.
		cout << "Blarg. Tile to north and has takeout drill up animation.\n"; //Debugging output.

		active_animation = takeout_drill_up;

		if(take_out_drill_progress >= take_out_drill_time && takeout_drill_up->current_frame < takeout_drill_up->num_frames - 1)
		{
			cout << "Progressing animation.\n";

			takeout_drill_up->proceed_animation();

			take_out_drill_progress = 0;
		}
		take_out_drill_progress++;

		if(take_out_drill_progress >= take_out_drill_time && takeout_drill_up->current_frame >= takeout_drill_up->num_frames - 1)
		{
			//THE DRILL IS OUT.
			cout << "Yay. Drill out. Now go slap yourself silly. Er, I mean, watch your raider drill das wall.\n"; //Debugging output.

			take_out_drill_progress = 0; //Reset this.
			drill_out = true; //Let the game know this unit has its drill out.
			takeout_drill_up->current_frame = 0;
		}
	}
	else if(Map[mine_tile_id].wy > wy && takeout_drill_down)
	{
		//PROGRESS THE ANIMATION AS NEEDED.
		cout << "Blarg. Tile to south and has takeout drill down animation.\n"; //Debugging output.

		active_animation = takeout_drill_down;

		if(take_out_drill_progress >= take_out_drill_time && takeout_drill_down->current_frame < takeout_drill_down->num_frames - 1)
		{
			cout << "Progressing animation.\n";

			takeout_drill_down->proceed_animation();

			take_out_drill_progress = 0;
		}
		take_out_drill_progress++;

		if(take_out_drill_progress >= take_out_drill_time && takeout_drill_down->current_frame >= takeout_drill_down->num_frames - 1)
		{
			//THE DRILL IS OUT.
			cout << "Yay. Drill out. Now go slap yourself silly. Er, I mean, watch your raider drill das wall.\n"; //Debugging output.

			take_out_drill_progress = 0; //Reset this.
			drill_out = true; //Let the game know this unit has its drill out.
			takeout_drill_down->current_frame = 0;
		}
	}
	else
	{
		if(take_out_drill_progress >= take_out_drill_time)
		{
			//THE DRILL IS OUT.
			cout << "Yay. Drill out. Now go slap yourself silly. Er, I mean, watch your raider drill das wall.\n"; //Debugging output.

			take_out_drill_progress = 0; //Reset this.
			drill_out = true; //Let the game know this unit has its drill out.
		}
		take_out_drill_progress++;
	}
}
