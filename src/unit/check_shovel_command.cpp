/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp

/* --------------------------------------------------------------
 * Everything related to the "check if user has given a shovel command" stuff is defined here.
 * ----------------------------------------------------------- */

bool bClassUnit::check_shovel_command() //Checks if a shovel command was issued.
{
	int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
	bool run = true;
	if(event_struct.button.button == SDL_BUTTON_LEFT && event_struct.type == SDL_MOUSEBUTTONDOWN)
	{
		allow_deselect = true;
		//Check if a tile was clicked
		for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++)
		{
			if(run)
			{
				//Check if the tile is the one that was clicked on.
				if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
				{
					run = false;

					std::cout << "Position of the tile to be shovelled: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";
					out_string << "Position of the tile to be shovelled: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";

					if(Map[i].rubble == true)
					{
						shovel_mode = false; //let the game know shovel mode is off.
						move = true; //Let the game know that the unit is moving somewhere.
						move_destination = i; //Let the game know that the move destination of this unit is the tile that was just clicked on.
						shovel_on_reach_goal = true; //Tells the unit to shovel the rubble once it reaches its goal.
						layer_offset = (num_row_objects * num_col_objects * Map[i].layer); //Assign the layer offset.

						if(calculate_path() == false) //If it can't calculate find a path...
						{
							//What...Something done borked. The tile is inaccessible.
							move = false; //Tell the unit it's staying put
							move_destination = 0; //Reset the unit's move destination.
							shovel_on_reach_goal = false; //Ya, let the unit know it ain't shovelling any rubble.
							shovelling = false; //Reset this so that the game knows to not shovel the tile...
						}
					}
					else
					{
						move = false; //Tell the unit it's staying put
						move_destination = 0; //Reset the unit's move destination.
						shovel_on_reach_goal = false; //Ya, let the unit know it ain't shovelling any rubble.
						shovel_mode = false; //let the game know shovel mode is off.
						shovelling = false; //Reset this so that the game knows to not shovel the tile...
						cout << "Not rubble!\n";
					}
				}
			}
		}
	}
	return false;
}
