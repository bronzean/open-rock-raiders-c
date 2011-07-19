/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp
#include <iostream>
using namespace std;

/* --------------------------------------------------------------
 * Everything related to the unit constructing stuff is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::construct_construction() //Does the stuff related to constructions.
{
	if(!move) //Just make sure the raider ain't trying to go anywhere.
	{
		try
		{
			//-------------------------------------
			//Here the construction is constructed.
			//-------------------------------------

			Draw_Message_Handler.add_message(wx + tile_width, wy, PCamera->layer, constructing_message_spr, 1, false); //Draw the "I'm Bob the builder!" message.

			my_job->construction_health -= construct_rate; //Progress the construction.

			if(my_job->construction_health <= 0 && construction_repositioning == 2) //Check if it's done constructing, and if the unit has already moved off the building's tile.
			{
				//-------------------------------------
				//Here the construction is finished.
				//-------------------------------------

				cout << "Done constructing!\n"; //Debugging output.
				out_string << "Done constructing!\n"; //Debugging output.

				if(my_job->construction_type == "wall") //Check if the unit is building a wall.
				{
					my_job->tasked_tile->construct_construction(c_wall); //Add the wall construction to the specified tile.
				}
				else if(my_job->construction_type == "door") //Check if the unit is building a door.
				{
					my_job->tasked_tile->construct_construction(c_door); //Add the door construction to the specified tile.
				}

				delete my_job; //Free that memory!!!
				my_job = NULL; //Reset this.

				construction_repositioning = 0; //Reset this so the raider moves off the tile next time too.

				job_state = "idle"; //Unit's done building. Now it's time for it to idle again.
			}
			else if(my_job->construction_health <= 0 && construction_repositioning == 0) //Check if it's time to move off the tile.
			{
				//-------------------------------------
				//Check if the raider can move off this tile once the construction is built.
				//-------------------------------------

				int layer_offset = (num_row_objects * num_col_objects * Map[my_job->tasked_tile->ID].layer); //Assign the layer offset.

				move = true; //I LIKE TO MOVE IT MOVE IT.

				construction_repositioning = 1; //Let the game know this unit is relocating itself.

				bool calculate_next_tile = false; //Set to true if the current tile failed the check.

				cout << "WX = " << Map[my_job->tasked_tile->ID].wx << ", WY = " << Map[my_job->tasked_tile->ID].wy << ", layer_offset = " << layer_offset << "\n"; //Debugging output.

				move_destination = (((((Map[my_job->tasked_tile->ID].wx) / tile_width) + ((Map[my_job->tasked_tile->ID].wy) / tile_height)) + ((num_row_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / tile_height)) ) ) - 1) + layer_offset; //Grab tile to the left, to start things off.

 				cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.


				if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile is "in bounds".
				{
					if(calculate_path() == false || (Map[move_destination].local_construction->door == true && Map[move_destination].has_construction == true)) //Calculate the path and check to make sure there's no door construction there.
					{
						if(Map[move_destination].local_construction->door == true && Map[move_destination].has_construction == true) cout << "Door! Can't move there foo.\n"; //Debugging output/yelling at ye foolish player.

						calculate_next_tile = true; //Calculate the next tile to see if it works.
					}
				}

				if(calculate_next_tile) //Previous tile failed? Try this one.
				{
					calculate_next_tile = false; //First off, reset this.

					move_destination = (((((Map[my_job->tasked_tile->ID].wx) / tile_width) + ((Map[my_job->tasked_tile->ID].wy) / tile_height)) + ((num_row_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / tile_height)) ) ) + 1) + layer_offset; //Last tile check failed. Grab the tile to the right this time.


 					cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

					if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
					{
						if(calculate_path() == false || (Map[move_destination].local_construction->door == true && Map[move_destination].has_construction == true)) //Calculate the path and check to make sure there's no door construction there.
						{
							if(Map[move_destination].local_construction->door == true && Map[move_destination].has_construction == true) cout << "Door! Can't move there foo.\n"; //Debugging output/yelling at ye foolish player.

							calculate_next_tile = true; //Eh, calculate next tile to see if that works.
						}
					}
				}

				if(calculate_next_tile) //Previous tile failed? Try this one.
				{
					calculate_next_tile = false; //Reset this!

					move_destination = (((((Map[my_job->tasked_tile->ID].wx) / tile_width) + ((Map[my_job->tasked_tile->ID].wy) / tile_height)) + ((num_row_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / tile_height) - 1) ) ) - 1) + layer_offset; //Oh dear, it failed yet again. Grab the tile to the north.


 					cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

					if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
					{
						if(calculate_path() == false || (Map[move_destination].local_construction->door == true && Map[move_destination].has_construction == true)) //Calculate the path and check to make sure there's no door construction there.
						{
							if(Map[move_destination].local_construction->door == true && Map[move_destination].has_construction == true) cout << "Door! Can't move there foo.\n"; //Debugging output/yelling at ye foolish player.

							calculate_next_tile = true; //Oh boy, last check to follow.
						}
					}
				}

				if(calculate_next_tile) //Previous tile failed? Try this one.
				{
					calculate_next_tile = false;

					move_destination = (((((Map[my_job->tasked_tile->ID].wx) / tile_width) + ((Map[my_job->tasked_tile->ID].wy) / tile_height)) + ((num_col_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / tile_height) + 1) ) ) + 1) + layer_offset; //You know the drill. Tile to the south now.


 					cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

					if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
					{
						if(calculate_path() == false || (Map[move_destination].local_construction->door == true && Map[move_destination].has_construction == true)) //Calculate the path and check to make sure there's no door construction there.
						{
							if(Map[move_destination].local_construction->door == true && Map[move_destination].has_construction == true) cout << "Door! Can't move there foo.\n"; //Debugging output/yelling at ye foolish player.

							//OH COME ON. WHAT IS WRONG WITH THIS PLAYER. THEY CLICKED ON AN INACCESSIBLE TILE!
							move = false; //Tell the unit it's staying put
							move_destination = 0; //Reset the unit's move destination.
							construction_repositioning = 0; //Signifies failure.

							cout << "What's this? Failed all the checks...\n"; //Debugging output.
						}
					}
				}

				if(construction_repositioning == 0) //If true, it means it failed to find a free tile.
				{
					//Add job back to job que.
					Job_Que.jobs.push_back(*my_job);
					delete my_job; //Free memory.
					job_state = "idling"; //Unit is now idling.
					cout << "What? Something failed.\n"; //Debugging ouput.
				}
			}
			else if(construction_repositioning == 1 && move == false) //Checks if the unit has relocated and is now pending construction finalisation.
			{
				construction_repositioning = 2; //YARR. Means the construction will finalise.
			}
		}
		catch(string error)
		{
			cout << "ERROR CODE 3: Construction has failed. Error message: " << error << "\n"; //Debugging output.
			out_string << "ERROR CODE 3: Construction has failed. Error message: " << error << "\n"; //Log the error.
			return;
		}
		catch(char const *error)
		{
			cout << "ERROR CODE 3: Construction has failed. Error message: " << error << "\n"; //Debugging output.
			out_string << "ERROR CODE 3: Construction has failed. Error message: " << error << "\n"; //Log the error.
			return;
		}
		catch(...) //Oops, something borked. General error. Abort!
		{
			cout << "ERROR CODE 3: Construction has failed. NO ERROR MESSAGE AVAILABLE. " << "\n"; //Debugging output.
			out_string << "ERROR CODE 3: Construction has failed. NO ERROR MESSAGE AVAILABLE. " << "\n"; //Log the error.
			gameover = true; //Tells the game to stop running.
			throw; //Quit this function.
		}
	}
	else //The unit hasn't yet reached the destination.
	{
		if(!allow_move)
		{
			if(allow_draw)
			{
				Draw_Message_Handler.add_message(wx + tile_width, wy, PCamera->layer, construct_walking_message_spr, 1, false); //Draw the "I'm coming to construct stuff!" message.
			}
		}
	}
}



/* Here's the debugging output that got generated:

WX = 160, WY = 160, layer_offset = 0
Move_destination = 74.
Path to ramp found!
Door! Can't move there foo.
Move_destination = 76.
Error: Can't move onto the unmovable!
Map[move_destination].wall = 1, Map[move_destination].air = 0, Map[move_destination].obstruction = 1
ID of said tile: 76
move_destination = 76.
Door! Can't move there foo.
Move_destination = 61.
Path to ramp found!
Door! Can't move there foo.
Move_destination = 89.
Error: Can't move onto the unmovable!
Map[move_destination].wall = 1, Map[move_destination].air = 0, Map[move_destination].obstruction = 1
ID of said tile: 89
move_destination = 89.
Door! Can't move there foo.
What's this? Failed all the checks...
What? Something failed.

Only 74 had a door.
See the problem?*/
