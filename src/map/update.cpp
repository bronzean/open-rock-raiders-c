/* Copyright the ORR-C Dev Team */
#include "tile.hpp"

void tile::update()
{
	//draw_sprite(); //Draw the tile's sprite

	if(has_construction) //Check if it has a construction on it.
	{
		local_construction->update(); //Update the local construction.
	}

	if(!server)
	{
		if(active_popup_menu && selected)
		{
			if(wall_popup_menu != NULL) //Make sure that wall_popup_menu even exists.
			{
				if(!wall_popup_menu->fields.empty()) //Make sure that wall_popup_menu is not empty.
				{
					wall_popup_menu_update(); //Update the wall_popup_menu.
				}
			}

			if(rubble_popup_menu != NULL) //Make sure that rubble_popup_menu even exists.
			{
				if(!rubble_popup_menu->fields.empty()) //Make sure that rubble_popup_menu is not empty.
				{
					rubble_popup_menu_update(); //Update the rubble_popup_menu.
				}
			}

			if(ground_popup_menu != NULL) //Make sure that ground_popup_menu even exists.
			{
				if(!ground_popup_menu->fields.empty()) //Make sure that ground_popup_menu is not empty.
				{
					ground_popup_menu_update(); //Update the ground_popup_menu.
				}
			}
		}
	}

	for(unsigned int i = 0; i < unitlist.size(); i++) //Loop through the tile's unitlist.
	{
		new_tile = 0; //Reset new_tile.
		//temp = ""; //Reset temp.
		try
		{
			temp = unitlist[i].update(); //Call the unit's update function and store the return value.
		}
		catch(...)
		{
			gameover = true;
			return; //Error!
		}

		//If the unit is selected and the tile the right click tookl place != -1 (-1 means that it took place outside of the map)...
		if(unitlist[i].selected == true && rightclick_tile_id != -1 && unitlist[i].move_frame != fps_counter)
		{
			//Check if the tile the unit was told to move to is the tile it's currently standing on.
			if(Map[rightclick_tile_id].wx == wx && Map[rightclick_tile_id].wy == wy && Map[rightclick_tile_id].layer == layer)
			{
				//If so, tell the player.
				std::cout << "\nCan't move to specified tile, unit already on tile.\n";
			}
			else
			{
				//If not, then tell the unit is has been issued a moveto command.
				unitlist[i].move = true; //Move = true let's the unit know it has to move somewhere.
				unitlist[i].move_destination = rightclick_tile_id; //move_destination is the index in the map array of the tile that the unit has to move to.
				unitlist[i].move_destination_ramp = -1;
				unitlist[i].calculate_need_ramp = true; //Let the game know it needs to check if a ramp needs to be used to access the next layer.
				unitlist[i].move_path.clear(); //Empty the move path so that movement doesn't glitch.
				unitlist[i].mining = false; //Let the game know the unit has moved away and has stopped mining the tile.
				unitlist[i].mine_on_reach_goal = false; //Let the game know the unit isn't moving to that tile anymore.
				unitlist[i].pick_up_on_reach_goal = false; //Let the game know the unit isn't moving to that tile anymore.
				unitlist[i].mine_tile_id = 0; //Reset mine_tile_id.
				unitlist[i].shovelling = false; //Let the game know the unit has moved away and has stopped shovelling the tile.
				unitlist[i].shovel_on_reach_goal = false; //Let the game know the unit isn't moving to that tile anymore.
				unitlist[i].move_frame = 0; //Reset this to prevent the "skip first tile in move_path" bug.
				std::cout << "\nSet unit's move destination...\n"; //Debugging output.
				out_string << "\nSet unit's move destination...\n";

				if(unitlist[i].calculate_path() == false) //If it can't calculate find a path...
				{
					unitlist[i].move = false; //Tell the unit it doesn't have anywhere to go.
					unitlist[i].move_destination = 0; //Reset the unit's move destination.
					unitlist[i].move_frame = 0; //Reset this to prevent the "skip first tile in move_path" bug.
				}
				else
				{
					unitlist[i].job_state = "moving"; //Since a move command has been issued, the unit is going to be in a "moving" job state.
				}
			}
		}

		

		if(temp == "m_right")
		{
			unitlist[i].chopping = false; //Otherwise, the unit would continue chopping the tree even though it isn't at the tree anymore.
			int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
			
			new_tile = (((((wx) / 32) + ((wy) / 32)) + ((num_row_objects - 1)* ((wy / 32)) ) ) + 1) + layer_offset; //Grab the index of the tile to the east.
			if(wx / 32 < num_row_objects - 1)
			{
				unitlist[i].move_destination = new_tile; //If so, assign the move destination.

				if(Map[unitlist[i].move_destination].wall != true && Map[unitlist[i].move_destination].air != true && Map[unitlist[i].move_destination].tree != true)
				{
					if(unitlist[i].move == false && move_issued == true)
					{
						std::cout << "Movin'!\n";
						cout << "new_tile = " << new_tile << "\n";
						unitlist[i].move = true; //Let the game know the unit is moving.
						unitlist[i].move_path.push_back(unitlist[i].move_destination); //Add the tile to the move path.
						unitlist[i].chop_mode = false; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
						unitlist[i].chopping = false; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
						unitlist[i].mine_tile_id = 0; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
					}
				}
				else if(Map[unitlist[i].move_destination].tree == true && unitlist[i].chop_mode == true)
				{
					unitlist[i].move = false; //Let the game know the unit aint going anywhere
					unitlist[i].move_destination = 0; //Reset this.
					unitlist[i].chop_mode = false; //Reset this.
					unitlist[i].chopping = true; //Let the game know the unit is now chopping down a tree.
					unitlist[i].mine_tile_id = new_tile; //Let the game know the location of the tree...
				}
				else
				{
					unitlist[i].move = false;
					unitlist[i].move_destination = 0;
					unitlist[i].chop_mode = false;
					if(Map[unitlist[i].move_destination].wall == true || Map[unitlist[i].move_destination].air == true || Map[unitlist[i].move_destination].tree == true)
					{
						cout << "Can't move onto an impassible tile!\n";
					}
					else
					{
						//cout << "Can't move yet!\n";
					}
				}
			}
			else
			{
				cout << "Can't move off map!\n";
			}
		}
		else if(temp == "m_left")
		{
			int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
			new_tile = (((((wx) / 32) + ((wy) / 32)) + ((num_row_objects - 1)* ((wy / 32)) ) ) - 1) + layer_offset; //Grab the index of the tile to the west.
			if(wx > 0)
			{
				unitlist[i].move_destination = new_tile; //If so, assign the move destination.

				if(Map[unitlist[i].move_destination].wall != true && Map[unitlist[i].move_destination].air != true && Map[unitlist[i].move_destination].tree != true)
				{
					if(unitlist[i].move == false && move_issued == true)
					{
						std::cout << "Movin'!\n";
						cout << "new_tile = " << new_tile << "\n";
						unitlist[i].move = true; //Let the game know the unit is moving.
						unitlist[i].move_path.push_back(unitlist[i].move_destination); //Add the tile to the move path.
						unitlist[i].chop_mode = false; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
						unitlist[i].chopping = false; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
						unitlist[i].mine_tile_id = 0; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
					}
				}
				else if(Map[unitlist[i].move_destination].tree == true && unitlist[i].chop_mode == true)
				{
					unitlist[i].move = false; //Let the game know the unit aint going anywhere
					unitlist[i].move_destination = 0; //Reset this.
					unitlist[i].chop_mode = false; //Reset this.
					unitlist[i].chopping = true; //Let the game know the unit is now chopping down a tree.
					unitlist[i].mine_tile_id = new_tile; //Let the game know the location of the tree...
				}
				else
				{
					unitlist[i].move = false;
					unitlist[i].move_destination = 0;
					unitlist[i].chop_mode = false;
					if(Map[unitlist[i].move_destination].wall == true || Map[unitlist[i].move_destination].air == true || Map[unitlist[i].move_destination].tree == true)
					{
						cout << "Can't move onto an impassible tile!\n";
					}
					else
					{
						//cout << "Can't move yet!\n";
					}
				}
			}
			else
			{
				cout << "Can't move off map!\n";
			}
		}
		else if(temp == "m_up")
		{
			int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
			new_tile = (((((wx) / 32) + ((wy) / 32)) + ((num_row_objects - 1)* ((wy / 32) - 1) ) ) - 1) + layer_offset;

			if(wy > 0)
			{
				unitlist[i].move_destination = new_tile; //If so, assign the move destination.

				if(Map[unitlist[i].move_destination].wall != true && Map[unitlist[i].move_destination].air != true && Map[unitlist[i].move_destination].tree != true)
				{
					if(unitlist[i].move == false && move_issued == true)
					{
						std::cout << "Movin'!\n";
						cout << "new_tile = " << new_tile << "\n";
						unitlist[i].move = true; //Let the game know the unit is moving.
						unitlist[i].move_path.push_back(unitlist[i].move_destination); //Add the tile to the move path.
						unitlist[i].chop_mode = false; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
						unitlist[i].chopping = false; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
						unitlist[i].mine_tile_id = 0; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
					}
				}
				else if(Map[unitlist[i].move_destination].tree == true && unitlist[i].chop_mode == true)
				{
					unitlist[i].move = false; //Let the game know the unit aint going anywhere
					unitlist[i].move_destination = 0; //Reset this.
					unitlist[i].chop_mode = false; //Reset this.
					unitlist[i].chopping = true; //Let the game know the unit is now chopping down a tree.
					unitlist[i].mine_tile_id = new_tile; //Let the game know the location of the tree...
				}
				else
				{
					unitlist[i].move = false;
					unitlist[i].move_destination = 0;
					unitlist[i].chop_mode = false;
					if(Map[unitlist[i].move_destination].wall == true || Map[unitlist[i].move_destination].air == true || Map[unitlist[i].move_destination].tree == true)
					{
						cout << "Can't move onto an impassible tile!\n";
					}
					else
					{
						//cout << "Can't move yet!\n";
					}
				}
			}
			else
			{
				cout << "Can't move off map!\n";
			}
		}
		else if(temp == "m_down")
		{
			int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
			new_tile = (((((wx) / 32) + ((wy) / 32)) + ((num_col_objects - 1)* ((wy / 32) + 1) ) ) + 1) + layer_offset; //Grab the index of the tile to the south.
			if(wy / 32 < num_col_objects - 1)
			{	
				unitlist[i].move_destination = new_tile; //If so, assign the move destination.

				if(Map[unitlist[i].move_destination].wall != true && Map[unitlist[i].move_destination].air != true && Map[unitlist[i].move_destination].tree != true)
				{
					if(unitlist[i].move == false && move_issued == true)
					{
						std::cout << "Movin'!\n";
						cout << "new_tile = " << new_tile << "\n";
						unitlist[i].move = true; //Let the game know the unit is moving.
						unitlist[i].move_path.push_back(unitlist[i].move_destination); //Add the tile to the move path.
						unitlist[i].chop_mode = false; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
						unitlist[i].chopping = false; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
						unitlist[i].mine_tile_id = 0; //The player didn't select a tree...Oh well. Let the game know the unit ain't chopping.
					}
				}
				else if(Map[unitlist[i].move_destination].tree == true && unitlist[i].chop_mode == true)
				{
					unitlist[i].move = false; //Let the game know the unit aint going anywhere
					unitlist[i].move_destination = 0; //Reset this.
					unitlist[i].chop_mode = false; //Reset this.
					unitlist[i].chopping = true; //Let the game know the unit is now chopping down a tree.
					unitlist[i].mine_tile_id = new_tile; //Let the game know the location of the tree...
				}
				else
				{
					unitlist[i].move = false;
					unitlist[i].move_destination = 0;
					unitlist[i].chop_mode = false;
					if(Map[unitlist[i].move_destination].wall == true || Map[unitlist[i].move_destination].air == true || Map[unitlist[i].move_destination].tree == true)
					{
						cout << "Can't move onto an impassible tile!\n";
					}
					else
					{
						//cout << "Can't move yet!\n";
					}
				}
			}
			else
			{
				cout << "Can't move off map!\n";
			}
		}

		if(unitlist[i].move_path.empty() == true && unitlist[i].move == true) //If it cycled through everything in the move path...
		{
			unitlist[i].move_frame = 0; //Reset this to prevent the "skip first tile in move_path" bug.
			cout << "Reached destination.\n\n";
			out_string << "Reached destination.\n\n";

			bool can_continue = true;

			if(unitlist[i].needs_to_close_door)
			{
				if(unitlist[i].moves_till_close_door_time <= 0) //Check if it's time to close the door.
				{
					cout << "Unit needs to close door.\n"; //Debugging output.
					if(unitlist[i].needs_to_close_door_tile->has_construction) //Check if the tile has a construction.
					{
						if(unitlist[i].needs_to_close_door_tile->local_construction->door && unitlist[i].needs_to_close_door_tile->local_construction->construction_open) //Check if it's a door and if the door is open.
						{
							unitlist[i].needs_to_close_door_tile->local_construction->close_thyself(false); //INCIDE USA MA.
							can_continue = false;
							unitlist[i].move = true;

							cout << "closing door.\n"; //Debugging output.
						}
						else
						{
							unitlist[i].needs_to_close_door = false; //Tell the unit it needs to close the door behind itself no longer.
							unitlist[i].needs_to_close_door_tile = NULL; //Reset this.

							cout << "Door already closed, or not a door.\n"; //Debugging output.
						}

						if(!unitlist[i].needs_to_close_door_tile->local_construction->construction_open)
						{
							unitlist[i].needs_to_close_door = false; //Tell the unit it needs to close the door behind itself no longer.
							unitlist[i].needs_to_close_door_tile = NULL; //Reset this.
						}
					}
					else
					{
						unitlist[i].needs_to_close_door = false; //Tell the unit it needs to close the door behind itself no longer.
						unitlist[i].needs_to_close_door_tile = NULL; //Reset this.

						cout << "Tile doesn't even have construction!\n"; //Debugging output.
					}
				}
				else
				{
					unitlist[i].needs_to_close_door = false; //Tell the unit it needs to close the door behind itself no longer.
					unitlist[i].needs_to_close_door_tile = NULL; //Reset this.
				}
			}

			if(can_continue)
			{
				if(unitlist[i].mine_on_reach_goal)
				{
					unitlist[i].mine_on_reach_goal = false; //Reset this. Otherwise it'd be the random walls popping up glitch all over again.
					if(Map[unitlist[i].mine_tile_id].wall && Map[unitlist[i].mine_tile_id].can_mine) //Check if the tile still is a wall that can be mined!
					{
						unitlist[i].mining = true; //Let the game know the unit is now mining the tile.
					}
					else
					{
						if(unitlist[i].my_job)
						{
							delete unitlist[i].my_job;
							unitlist[i].my_job = NULL;
						}
						unitlist[i].cancel_current_activity(); //Not a drillable wall anymore. Cancelling drilling.
					}
				}
				else if(unitlist[i].chop_on_reach_goal == true)
				{
					unitlist[i].chop_on_reach_goal = false; //Reset this. Otherwise bad stuff can happen.
					unitlist[i].chopping = true; //Let the game know the unit is now chopping the tree.
				}
				else if(unitlist[i].shovel_on_reach_goal == true)
				{
					unitlist[i].shovel_on_reach_goal = false; //Reset this. Otherwise bad stuff will happen.
					if(rubble) //Check if this tile is even rubble still.
					{
						unitlist[i].shovelling = true; //Let the game know the unit is now shovelling the rubble.
					}
					else
					{
						if(unitlist[i].my_job)
						{
							delete unitlist[i].my_job;
							unitlist[i].my_job = NULL;
						}
						unitlist[i].cancel_current_activity(); //Not rubble anymore. Cancelling shovelling.
					}
				}

				//Check if the unit is picking up any ore.
				//Then check if it can pick up ore.
				//Then pick up the ore.

				else if(unitlist[i].pick_up_on_reach_goal == true && !unitlist[i].carrying_resource) //If the unit is supposed to pick something up...
				{
					if(!unitlist[i].picked_up) //If the unit has not yet picked up the object.
					{
						unitlist[i]._pick_up(); //Make the unit pick up! An animate it, if applicable.
						can_continue = false;
					}
					else
					{
						cout << "Pick up ore on reach goal stuff taking place.\n";
						//TODO: Change this later to check if the unit can pick up the specified object.
						unitlist[i].pick_up_on_reach_goal = false; //Reset this. Otherwise bad things will happen.

						//TODO: Check to see if the tile still has the item the unit was sent to pick up.
						//if(tile_has_whatever_unit_was_picking_up)
						//{
							//TODO: add whatever that was to the inventory
						//}

						if(orelist.size() < 1) //Check if there even is any ore here. TODO: Refine this to check if the item the player requested still is on the tile.
						{
							cout << "Hey, there's nothing to pick up here!\n"; //TODO: Make a message pop up informing the player that there's nothing to pick up there.

							if(unitlist[i].my_job) //Check if the unit's job exists.
							{
								delete unitlist[i].my_job; //DELETE.
								unitlist[i].my_job = NULL; //Reset.
							}

							unitlist[i].cancel_current_activity();
						}
						else
						{
							//Add the item into the player's inventory.

							unitlist[i].ore_list.push_back(orelist[0]); //Add the ore to the tile's orelist.

							//Map[unitlist[i].move_path[0]].orelist.erase(Map[unitlist[i].move_path[0]].orelist.begin()); //Remove the ore from the tile's orelist.

							bool done = false; //Used to control the loop below.
							int i2 = 0;
							vector<ore*>::iterator iterator = ore_on_map.begin(); //Used to loop through ore list.

							/*while(done == false) //So, here the game loops until it's either gone through the entire ore on map list or it's found the ore it's looking for.
							{
								cout << "Loop: " << i2 << "\n";
								if(iterator >= ore_on_map.end())
								{
									done = true; //Uh oh, it reached the end of the ore on map list. Something done borked.
									cout << "Uh oh, reached the end of the ore on map list when I shouldn't have. Something done borked. Error code: 1\n"; //Let the user know that something went wrong.
									out_string << "Uh oh, reached the end of the ore on map list when I shouldn't have. Something done borked. Error code: 1\n"; //Let the user know that something went wrong.
								}
								else
								{
									if(ore_on_map[i2]->containing_tile->ID == ID) //So, if the tile the ore claims it's located on is equal to this tile, then we've found the ore...
									{
										cout << "I did it! Found the ore! Removing it!\n"; //Debugging output.

										ore_on_map.erase(iterator); //Remove the ore from the ore_on_map list.

										done = true; //The ore has been found. No use lingering around in this loop.
									}
								}

								i2++; //Obviously, increment this.
								iterator++;
							}*/

							for(i2 = 0; iterator < ore_on_map.end(); iterator++, i2++) //Remove the ore that was just picked up from the ore on map list.
							{
								cout << "Size: " << ore_on_map.size() << "\n";
								if(ore_on_map[i2]->containing_tile == this && done == false) //So, if the tile the ore claims it's located on is equal to this tile, then we've found the ore...TODO: This is very primitive. Later, this will need to be redone to be better.
								{
									cout << "I did it! Found the ore! Removing it!\n"; //Debugging output.
									out_string << "I did it! Found the ore! Removing it!\n"; //Debugging output.

									ore_on_map.erase(iterator); //Remove the ore from the ore_on_map list.

									done = true; //The ore has been found. No use lingering around in this loop.
								}
							}

							orelist.erase(orelist.begin()); //Remove the ore from the tile's orelist.

							unitlist[i].carrying_resource = true;

							if(unitlist[i].my_job)
							{
								delete unitlist[i].my_job;
								unitlist[i].my_job = NULL;
							}

							cout << "Picked up ore!\n"; //Debugging output.

							unitlist[i].cancel_current_activity();
						}

						unitlist[i].cancel_current_activity();
					}
				}

				else if(unitlist[i].close_door) //Check if the unit is supposed to close a door upon reaching its goal.
				{
					unitlist[i].close_door = false; //Reset this,
					unitlist[i].closing_door = true; //Let the game know the unit is now in the process of closing the door.
				}
				else //Just a simple moveto command.
				{
					if(unitlist[i].my_job) //Check if the unit's job exists.
					{
						if(unitlist[i].my_job->type == "open door")
						{
							delete unitlist[i].my_job; //DELETE.
							unitlist[i].my_job = NULL; //Reset.
						}
					}
					else
					{
						unitlist[i].cancel_current_activity();
					}
				}
			}
			if(can_continue)
			{
				if(unitlist[i].job_state == "moving") //If the unit's command is simply "move", then...
				{
					unitlist[i].job_state = "idling"; //Since it reached its destination, set its current state to idle.
				}

				unitlist[i].move_path.erase( unitlist[i].move_path.begin(), unitlist[i].move_path.end() ); //Empty move path.

				unitlist[i].move = false; //Tell the unit it doesn't have anywhere to go.
				unitlist[i].move_destination = 0; //Reset the unit's move destination.
			}
		}
		//If the unit is going somewhere...
		else if(unitlist[i].move == true && unitlist[i].move_frame != fps_counter && paused != true && unitlist[i].allow_move == true)
		{
			move_unit(i); //Call the function that moves the unit.
		}
		else if(unitlist[i].mining == true) //If the unit ain't moving but it's mining...
		{
			mine_to_ground(i); //BURN DOWN THE WALL!!! Errr...I mean...MINE THE WALL!!!
		}
		else if(unitlist[i].chopping == true)
		{
			chop_to_ground(i); //KILL THEM TREES!!!
		}
		else if(unitlist[i].shovelling == true)
		{
			rubble_to_ground(i); //SHOVEL SOME RUBBLE!!!
		}
	}
}

