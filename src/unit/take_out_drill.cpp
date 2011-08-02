/* Copyright the ORR-C Dev Team */
#include "unit.hpp"

void bClassUnit::take_out_drill() //Take out its drill.
{
	cout << "Taking out drill.\n";

	if(Map[mine_tile_id].wx < wx && takeout_drill_left)
	{
		//PROGRESS THE ANIMATION AS NEEDED.
		cout << "Blarg. Tile to left and has takeout drill left animation.\n"; //Debugging output.
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

			/* //Check if it has the animation.
			if(Map[unitlist[i].mine_tile_id].wx < unitlist[i].wx && unitlist[i].takeout_drill_left) //Tile is to left and has animation?
			{
				//PROGRESS THE ANIMATION AS NEEDED>
				cout << "Blarg. Tile to left and has takeout drill left animation.\n";
			}
			else
			{
				if(unitlist[i].take_out_drill_progress >= unitlist[i].take_out_drill_time)
				{
					//THE DRILL IS OUT.
					cout << "Yay. Drill out. Now go slap yourself silly. Er, I mean, watch your raider drill das wall.\n";
				}
			}*/
}
