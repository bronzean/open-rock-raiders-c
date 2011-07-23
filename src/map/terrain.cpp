/* Copyright the ORR-C Dev Team */
#include "tile.hpp"

tile::tile() //Constructor. Initialize an empty tile.
{
	type_id = 0;
	sprite = NULL;
	name = "";
	wx = 0;
	wy = 0;
	layer = 0;
	plane = 0;
	width = 0;
	height = 0;
	ID = 0;
	temp = "";
	new_tile = 0;
	ramp = false;
	up_ramp = false;
	down_ramp = false;
	wall = false;
	self_supporting = false;
	ore_type = 0;
	can_mine = false;
	minimumn_mining_power = 0;
	air = false;
	turn_to_ground = false;
	ground_type = 0;
	generate_ore_on_mine = false;
	num_ore_to_generate = 0;
	tree = false;
	important = false;
	rubble = false;
	Active_Map_Entry = -1;
	active_animation = false;
	active_animation_entry = 0;
	has_construction = false;
	obstruction = false;
	ground = false;
	construction_in_progress = false;
}

void tile::init(int ID, SDL_Surface *SPRITE, std::string NAME, bool WALL, bool RAMP, bool UP_RAMP, bool DOWN_RAMP, bool SELF_SUPPORTING, int ORE_TYPE, bool CAN_MINE, int MINIMUMN_MINING_POWER, bool AIR, bool TURN_TO_GROUND, int GROUND_TYPE, bool GENERATE_ORE_ON_MINE, int NUM_ORE_TO_GENERATE, bool TREE, bool RUBBLE)
{
	type_id = ID;
	sprite = SPRITE;
	name = NAME;
	width = SPRITE->w;
	height = SPRITE->h;
	ramp = RAMP;
	up_ramp = UP_RAMP;
	down_ramp = DOWN_RAMP;
	wall = WALL;
	self_supporting = SELF_SUPPORTING;
	ore_type = ORE_TYPE;
	can_mine = CAN_MINE;
	minimumn_mining_power = MINIMUMN_MINING_POWER;
	air = AIR;
	turn_to_ground = TURN_TO_GROUND;
	ground_type = GROUND_TYPE;
	generate_ore_on_mine = GENERATE_ORE_ON_MINE;
	num_ore_to_generate = NUM_ORE_TO_GENERATE;
	tree = TREE;
	rubble = RUBBLE;
}

void tile::draw_sprite()
{
	if(layer == PCamera->layer && get_wx() + get_width() >= PCamera->wx && get_wx() <= (PCamera->wx + SCREEN_WIDTH) && get_wy() + get_height() >= PCamera->wy && get_wy() <= (PCamera->wy + SCREEN_HEIGHT))
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
		if(unitlist.size() != 0) //If the tile has units on it.
		{
			unitlist[unitlist.size() - 1].draw_sprite(); //Draw the topmost unit's sprite.
		}
	}
}


void tile::update()
{
	//draw_sprite(); //Draw the tile's sprite

	for(unsigned int i = 0; i < unitlist.size(); i++)
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
			int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset. TODO: Make this a global variable...
			
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
			int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset. TODO: Make this a global variable...
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
			int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset. TODO: Make this a global variable...
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
			int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset. TODO: Make this a global variable...
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
			unitlist[i].move = false; //Tell the unit it doesn't have anywhere to go.
			unitlist[i].move_destination = 0; //Reset the unit's move destination.
			unitlist[i].move_frame = 0; //Reset this to prevent the "skip first tile in move_path" bug.
			cout << "Reached destination.\n\n";
			out_string << "Reached destination.\n\n";

			if(unitlist[i].job_state == "moving") //If the unit's command is simply "move", then...
			{
				unitlist[i].job_state = "idle"; //Since it reached its destination, set its current state to idle.
			}

			if(unitlist[i].mine_on_reach_goal)
			{
				unitlist[i].mine_on_reach_goal = false; //Reset this. Otherwise it'd be the random walls popping up glitch all over again.
				unitlist[i].mining = true; //Let the game know the unit is now mining the tile.
			}
			else if(unitlist[i].chop_on_reach_goal == true)
			{
				unitlist[i].chop_on_reach_goal = false; //Reset this. Otherwise bad stuff can happen.
				unitlist[i].chopping = true; //Let the game know the unit is now chopping the tree.
			}
			else if(unitlist[i].shovel_on_reach_goal == true)
			{
				unitlist[i].shovel_on_reach_goal = false; //Reset this. Otherwise bad stuff will happen.
				unitlist[i].shovelling = true; //Let the game know the unit is now shovelling the rubble.
			}

			//TODO: Check if the unit is picking up any ore.
			//Then check if it can pick up ore.
			//Then pick up the ore.

			if(unitlist[i].pick_up_on_reach_goal == true) //If the unit is supposed to pick something up...
			{
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
							if(ore_on_map[i2]->containing_tile->ID == ID) //So, if the tile the ore claims it's located on is equal to this tile, then we've found the ore...TODO: This is very primitive. Later, this will need to be redone to be better.
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

					cout << "Picked up ore!\n"; //Debugging output.
				}
			}

			if(unitlist[i].close_door) //Check if the unit is supposed to close a door upon reaching its goal.
			{
				unitlist[i].close_door = false; //Reset this,
				unitlist[i].closing_door = true; //Let the game know the unit is now in the process of closing the door.
			}

			unitlist[i].move_path.erase( unitlist[i].move_path.begin(), unitlist[i].move_path.end() ); //Empty move path.
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

void tile::move_unit(int i)
{
	bool can_continue = true;
	if(unitlist[i].move_path.size() >= 1)
	{
		if(Map[unitlist[i].move_path[0]].has_construction) //Check if the tile has a construction, and if the construction is a door, check if its open.
		{
			if(Map[unitlist[i].move_path[0]].local_construction->door && !Map[unitlist[i].move_path[0]].local_construction->construction_open)
			{
				/*//Has door, and it ain't open. OPEN THE DOOR.
				if(local_construction->opening)
				{
					//Do nothing.
				}
				else
				{*/
					Map[unitlist[i].move_path[0]].local_construction->open_thyself(false); //OPEN THE DOOR.
				/*}*/
				can_continue = false;
			}
		}
	}
	if(can_continue) //Ok, the unit's all good to move on.
	{
		std::cout << "Position of new tile: (" << Map[unitlist[i].move_path[0]].wx << "," << Map[unitlist[i].move_path[0]].wy << "," << Map[unitlist[i].move_path[0]].layer << ")\n";
		out_string << "Position of new tile: (" << Map[unitlist[i].move_path[0]].wx << "," << Map[unitlist[i].move_path[0]].wy << "," << Map[unitlist[i].move_path[0]].layer << ")\n";
		cout << "Index of new tile: " << unitlist[i].move_path[0] << "\n"; //Debugging output.
		out_string << "Index of new tile: " << unitlist[i].move_path[0] << "\n";

		unitlist[i].allow_move = false; //Let the unit know it moved...

		//Initialize a new unit.
		bClassUnit newUnit;
		/*if(unitlist[i].move_frame != 0)
		{
			unitlist[i].move_path.erase(unitlist[i].move_path.begin()); //Remove the tile the unit just moved to from its move route.
		}*/
		newUnit = unitlist[i]; //Copy this unit over to the new one.
		newUnit.wx = Map[unitlist[i].move_path[0]].wx; //Assign the new unit's world x.
		newUnit.wy = Map[unitlist[i].move_path[0]].wy; //Assign the new unit's world y.
		newUnit.layer = Map[unitlist[i].move_path[0]].layer; //Assign the new unit's layer.
		newUnit.move_frame = fps_counter; //Let the game know the unit has already moved this turn.

		int new_tile_id = 0;
		new_tile_id = unitlist[i].move_path[0]; //Copy this over since we need it...

		if(!Map[new_tile_id].obstruction)
		{
			Map[unitlist[i].move_path[0]].unitlist.push_back(newUnit);

			if(Map[unitlist[i].move_path[0]].unitlist[Map[unitlist[i].move_path[0]].unitlist.size() - 1].move_frame != 0)
			{
				Map[unitlist[i].move_path[0]].unitlist[Map[unitlist[i].move_path[0]].unitlist.size() - 1].move_path.erase(Map[unitlist[i].move_path[0]].unitlist[Map[unitlist[i].move_path[0]].unitlist.size() - 1].move_path.begin()); //Remove the tile the unit just moved to from its move route.
			}

			if(Map[unitlist[i].move_path[0]].unitlist[Map[unitlist[i].move_path[0]].unitlist.size() - 1].selected && selected_unit == &unitlist[i]) //If the unit is selected.
			{
				selected_unit = &Map[unitlist[i].move_path[0]].unitlist[Map[unitlist[i].move_path[0]].unitlist.size() - 1]; //Let the game know this is the currently selected unit.
				cout << "Transferring over selected unit status.\n";
			}

			unitlist.erase(unitlist.begin() + i); //Remove this unit from this tile. Otherwise it would be the self replicating raiders glitch all over again. //TODO: This randomally crashes.

	

			if(unitlist.size() < 1)
			{
				cout << "Removing tile from Active_Map.\n"; //Debugging output.
				bool done = false;
				for(unsigned int i2 = 0; i2 < Active_Map.size(); i2++)
				{
					if(Map[Active_Map[i2]].ID == ID && done == false)
					{
						Active_Map.erase(Active_Map.begin() + i2); //Remove this tile from Active_Map.
						done = true;
					}
				}
			}
			//TODO: Make sure the tile isn't already in active map.
			bool found_entry = false;
			for(unsigned int i2 = 0; i2 < Active_Map.size(); i2++)
			{
				if(Map[Active_Map[i2]].ID == Map[new_tile_id].ID)
				{
					found_entry = true;
				}
			}
			if(found_entry == false)
			{
				Active_Map.push_back(Map[new_tile_id].ID); //Add the index of the tile the unit just moved to to Active_Map.
				cout << "Entry: " << Active_Map.size() - 1 << "\n";
				out_string << "Entry: " << Active_Map.size() - 1 << "\n";
			}

			std::cout << "Succesfully moved unit.\n\n"; //Debugging output.
			out_string << "Successfully moved unit.\n\n";
		}
		else //Foolish mortal
		{
			cout << "Foolish mortal. You can't move onto that which you cannot move onto.\n"; //Debugging output.

			unitlist[i].move = false; //The unit must stop moving.
			unitlist[i].move_destination = 0; //Reset this.
			unitlist[i].move_path.clear(); //Empty the move path.
			unitlist[i].move_frame = 0; //Reset this.
		}
	}
}

void tile::set_sprite(std::string sprite_path)
{
	sprite = img_load3(sprite_path);
	if(&sprite == NULL)
	{
		std::cout << "\ntile_object.sprite == NULL\n";
	}
	width = sprite->w;
	height = sprite->h;
}

int tile::get_wx()
{
	return wx;
}

int tile::get_wy()
{
	return wy;
}

int tile::get_width()
{
	return width;
}

int tile::get_height()
{
	return height;
}

/*void tile::mine_to_ground(int i)
{
	if(!paused)
	{
		if(Map[unitlist[i].mine_tile_id].health[0] <= 0) //TODO: Remember when going through and changing mining that this needs to be changed too.
		{
			cout << "Mining wall!\n"; //Debugging output.

			if(Map[unitlist[i].mine_tile_id].generate_ore_on_mine == true) //If the tile generates ore when it is mined... TODO: There's a bug here. If, in the config file, I change GENERATE_ORE_ON_MINE to false, it still thinks it's set to true. Fix this bug.
			{
				cout << "Generatin some ore for ya.\n"; //Debugging output.

				int num_to_gen = Map[unitlist[i].mine_tile_id].num_ore_to_generate; //Grab the number of ore it generates.

				for(int i2 = 0; i2 < num_to_gen; i2++) //Keep adding ore untill all the requested ore have been generated.
				{
					ore new_ore = Ore_Type_Manager.get_by_id(Map[unitlist[i].mine_tile_id].ore_type); //Grab the properties of the new ore.
					Map[unitlist[i].mine_tile_id].orelist.push_back(new_ore); //Add the new ore to the orelist.

					cout << "Generating ore with type: " << Map[unitlist[i].mine_tile_id].ore_type << "\n"; //Debugging output.
				}
			}

			tile new_tile; //The tile this tile is going to be transforming into.

			new_tile = Tile_Type_Manager.get_by_id(Map[unitlist[i].mine_tile_id].ground_type); //Grab the properties of the specified tile it turns into.
			new_tile.wx = Map[unitlist[i].mine_tile_id].wx; //Give the new tile this tile's world x.
			new_tile.wy = Map[unitlist[i].mine_tile_id].wy; //Give the new tile this tile's world y.
			new_tile.layer = Map[unitlist[i].mine_tile_id].layer; //Give the new tile this tile's layer.
			new_tile.ID = Map[unitlist[i].mine_tile_id].ID; //Give the new tile this tile's ID.
			new_tile.unitlist = Map[unitlist[i].mine_tile_id].unitlist; //Copy over this tile's unitlist.
			new_tile.orelist = Map[unitlist[i].mine_tile_id].orelist; //Copy over this tile's orelist.
			new_tile.energy_crystal_list = Map[unitlist[i].mine_tile_id].energy_crystal_list; //Copy over this tile's energy crystal list.
			Map[unitlist[i].mine_tile_id] = new_tile;

			std::cout << "\n\n" << new_tile.wx << "," << new_tile.wy << "," << new_tile.layer << "," << new_tile.ID << "," << Map[unitlist[i].mine_tile_id].ground_type << "," << new_tile.type << "\n\n";

	
			unitlist[i].mine_on_reach_goal = false; //Reset mine_on_reach_goal.
			unitlist[i].mine_tile_id = 0; //Reset mine_tile_id
			unitlist[i].mining = false; //Let the game know the unit stopped minin'.
		}
		else
		{
			cout << "Wall not damaged enough to collapse! Gonna damage it a bit right now...\n";
			out_string << "Wall not damaged enough to collapse! Gonna damage it a bit right now...\n";


			int counter = 0;
			bool found = false; //Did it find a tool that meets the requirements?

			for(unitlist[i].iterator = unitlist[i].tool_list.begin(); unitlist[i].iterator < unitlist[i].tool_list.end(); unitlist[i].iterator++, counter++) //Loop through the tool list
			{
				if(found == false && unitlist[i].tool_list[counter].can_drill_wall == true && Map[unitlist[i].mine_tile_id].minimumn_mining_power <= unitlist[i].tool_list[counter].drill_power) //If the tool meets all the requirements to mine this wall...
				{
					Map[unitlist[i].mine_tile_id].health[0] -= unitlist[i].tool_list[counter].drill_rate; //Subtract the tool's drill rate from this tile's health. //TODO: Remember when going through and changing mining that this needs to be changed too.
					found = true;
					cout << "Wall's new health: " << Map[unitlist[i].mine_tile_id].health[0] << "\n"; //TODO: Remember when going through and changing mining that this needs to be changed too.
					Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].mining_message_spr, 1); //Draw the "Whee, mining!" message.
				}
			}
		}
	}
	else
	{
		Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].mining_message_spr, 1); //Draw the "Whee, mining!"
	}
}*/

void tile::mine_to_ground(int i)
{
	if(!paused)
	{
		//bClassUnit *temp_unit = &unitlist[i];
		if(Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels /*- 1*/] <= 0 && Map[unitlist[i].mine_tile_id].num_shovels <= 0) //This checks if the mining is completely done.
		{
			cout << "Mining wall!\n"; //Debugging output.

			unitlist[i].mining = false; //Tell the unit it's done mining.
			unitlist[i].mine_on_reach_goal = false; //Reset mine_on_reach_goal.

			//TODO: Generate ore, if any.

			//Turn the destination tile into a ground tile.
			tile new_tile; //The tile this tile is going to be transforming into.

			new_tile = Tile_Type_Manager.get_by_id(Map[unitlist[i].mine_tile_id].ground_type); //Grab the properties of the specified tile it turns into.
			new_tile.wx = Map[unitlist[i].mine_tile_id].wx; //Give the new tile this tile's world x.
			new_tile.wy = Map[unitlist[i].mine_tile_id].wy; //Give the new tile this tile's world y.
			new_tile.layer = Map[unitlist[i].mine_tile_id].layer; //Give the new tile this tile's layer.
			new_tile.ID = Map[unitlist[i].mine_tile_id].ID; //Give the new tile this tile's ID.
			new_tile.unitlist = Map[unitlist[i].mine_tile_id].unitlist; //Copy over this tile's unitlist.
			new_tile.orelist = Map[unitlist[i].mine_tile_id].orelist; //Copy over this tile's orelist.
			new_tile.energy_crystal_list = Map[unitlist[i].mine_tile_id].energy_crystal_list; //Copy over this tile's energy crystal list.
			Map[unitlist[i].mine_tile_id] = new_tile;

			//tile old_tile = Map[unitlist[i].mine_tile_id]; //Store the old stuff...
			//Map[unitlist[i].mine_tile_id] = Tile_Type_Manager.get_by_id(old_tile.ground_type); //Grab the properties of the specified tile it turns into.
			//Map[unitlist[i].mine_tile_id].wx = old_tile.wx; //Give the new tile this tile's world x.
			//Map[unitlist[i].mine_tile_id].wy = old_tile.wy; //Give the new tile this tile's world y.
			//Map[unitlist[i].mine_tile_id].layer = old_tile.layer; //Give the new tile this tile's layer.
			//Map[unitlist[i].mine_tile_id].ID = old_tile.ID; //Give the new tile this tile's ID.
			//Map[unitlist[i].mine_tile_id].unitlist = old_tile.unitlist; //Copy over this tile's unitlist.
			//Map[unitlist[i].mine_tile_id].orelist = old_tile.orelist; //Copy over this tile's orelist.
			//Map[unitlist[i].mine_tile_id].energy_crystal_list = old_tile.energy_crystal_list; //Copy over this tile's energy crystal list.

			/*int i2 = 0;
			vector<ore*>::iterator iterator = ore_on_map.begin(); //Used to loop through ore on map list.
			vector<ore>::iterator iterator2 = Map[unitlist[i].mine_tile_id].orelist.begin(); //Used to loop through the new tile's ore list.

			for(; iterator < ore_on_map.end(); iterator++, i2++) //Remove all the ore from this tile...
			{
				cout << "Size: " << ore_on_map.size() << "\n"; //Debugging output...
				cout << "ID: " << ore_on_map[i2]->containing_tile->ID << "\n"; //Debugging output...
				if(ore_on_map[i2]->containing_tile->ID == new_tile.ID) //See if it found the right ore...
				{
					cout << "I did it! Found the ore! Removing it!\n"; //Debugging output.
					out_string << "I did it! Found the ore! Removing it!\n"; //Debugging output.

					ore_on_map.erase(iterator); //Remove the ore from the ore_on_map list.
				}
			}

			//Add the new ore into the ore_on_map thing.
			for(i2 = 0; iterator2 < new_tile.orelist.end(); iterator2++, i2++)
			{
				ore_on_map.push_back(&Map[unitlist[i].mine_tile_id].orelist[Map[unitlist[i].mine_tile_id].orelist.size()]); //Add the current ore into the orelist.
				ore_on_map[ore_on_map.size() - 1]->containing_tile = &Map[unitlist[i].mine_tile_id]; //I guess this has to be reset for some weird reason.
			}*/

			std::cout << "\n\n" << new_tile.wx << "," << new_tile.wy << "," << new_tile.layer << "," << new_tile.ID << "," << Map[unitlist[i].mine_tile_id].ground_type << "," << new_tile.type_id << "\n\n";

			unitlist[i].job_state = "idle"; //Be sure to reset the unit's state!
		}
		else if(Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels - 1] <= 0) //This checks if the current drill is done.
		{
			out_string << "Done with a drill!\n"; //Debugging output.
			Map[unitlist[i].mine_tile_id].health.pop_back(); //Remove the last element of health. For obvious reasons.

			/*out_string << "Health: \n";
			for(int i = 0; i < Map[unitlist[i].mine_tile_id].num_shovels; i++)
			{
				out_string << Map[unitlist[i].mine_tile_id].health[i] << "\n";
			}
			out_string << "\n";*/

			if(Map[unitlist[i].mine_tile_id].drilling_animation == true)
			{
				if(Map[unitlist[i].mine_tile_id].num_shovels != Map[unitlist[i].mine_tile_id].total_shovels)
				{
					Map[unitlist[i].mine_tile_id].animations[Map[unitlist[i].mine_tile_id].drilling_animation_entry].proceed_animation(); //Increase the animation thingy.
				}
				Map[unitlist[i].mine_tile_id].active_animation = true; //Let the game know an animation is going on for this tile.
				Map[unitlist[i].mine_tile_id].active_animation_entry = Map[unitlist[i].mine_tile_id].drilling_animation_entry; //Let it know the entry of the active animation in the animations vector.
				cout << "Mine tile ID: " << Map[unitlist[i].mine_tile_id].ID << "\n";
			}

			Map[unitlist[i].mine_tile_id].num_shovels--; //First, reduce the number of drills left.
		}
		else if(Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels - 1] > 0) //So, all the other checks returned false. Here the wall's health is lowered by the unit's drill.
		{
			//cout << "YARR! DRILLING!!\n"; //Debugging output.

			//cout << "Health: " << Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels - 1] << ", num_shovels: " << Map[unitlist[i].mine_tile_id].num_shovels - 1 << "\n"; //Debugging output.



			//Subtract the raider's drill's damage from the health of the tile.
			int counter = 0;
			bool found = false; //Did it find the tool that meets its requirements?

			for(unitlist[i].iterator = unitlist[i].tool_list.begin(); unitlist[i].iterator < unitlist[i].tool_list.end(); unitlist[i].iterator++, counter++) //Loop through the tool list
			{
				if(found == false && unitlist[i].tool_list[counter].can_drill_wall == true && Map[unitlist[i].mine_tile_id].minimumn_mining_power <= unitlist[i].tool_list[counter].drill_power) //If the tool meets all the requirements to mine this wall...
				{
					Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels - 1] -= unitlist[i].tool_list[counter].drill_rate; //Subtract the tool's shovel rate from this tile's health.
					found = true;
					//cout << "Wall's new health: " << Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels - 1]<< "\n";
					Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].mining_message_spr, 1, false); //Draw the "Whee, mining!" message.
				}
			}
		}
	}
	else
	{
		Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].mining_message_spr, 1, false); //Draw the "Whee, mining!"
	}
}

void tile::chop_to_ground(int i)
{	if(!paused)
	{
		if(Map[unitlist[i].mine_tile_id].health[0] <= 0) //TODO: Remember when going through and changing chopping that this needs to be changed too.
		{
			cout << "Chopping tree!\n"; //Debugging output.

			if(Map[unitlist[i].mine_tile_id].generate_ore_on_mine) //If the tile generates wood when it is chopped...
			{
				cout << "Generatin some wood for ya.\n"; //Debugging output.

				int num_to_gen = Map[unitlist[i].mine_tile_id].num_ore_to_generate; //Grab the number of wood it generates.

				for(int i2 = 0; i2 < num_to_gen; i2++) //Keep adding wood until all the requested wood has been generated.
				{
					ore new_ore = Ore_Type_Manager.get_by_id(Map[unitlist[i].mine_tile_id].ore_type); //Grab the properties of the new wood.
					Map[unitlist[i].mine_tile_id].orelist.push_back(new_ore); //Add the new ore to the orelist.

					cout << "Generating wood with type: " << Map[unitlist[i].mine_tile_id].ore_type << "\n"; //Debugging output.
				}
			}

			tile new_tile; //The tile this tile is going to be transforming into.

			new_tile = Tile_Type_Manager.get_by_id(Map[unitlist[i].mine_tile_id].ground_type); //Grab the properties of the specified tile it turns into.
			new_tile.wx = Map[unitlist[i].mine_tile_id].wx; //Give the new tile this tile's world x.
			new_tile.wy = Map[unitlist[i].mine_tile_id].wy; //Give the new tile this tile's world y.
			new_tile.layer = Map[unitlist[i].mine_tile_id].layer; //Give the new tile this tile's layer.
			new_tile.ID = Map[unitlist[i].mine_tile_id].ID; //Give the new tile this tile's ID.
			new_tile.unitlist = Map[unitlist[i].mine_tile_id].unitlist; //Copy over this tile's unitlist.
			new_tile.orelist = Map[unitlist[i].mine_tile_id].orelist; //Copy over this tile's orelist.
			new_tile.energy_crystal_list = Map[unitlist[i].mine_tile_id].energy_crystal_list; //Copy over this tile's energy crystal list.
			Map[unitlist[i].mine_tile_id] = new_tile;

			std::cout << "\n\n" << new_tile.wx << "," << new_tile.wy << "," << new_tile.layer << "," << new_tile.ID << "," << Map[unitlist[i].mine_tile_id].ground_type << "," << new_tile.type_id << "\n\n";


			cout << "Done chopping!\n";	
			unitlist[i].mine_on_reach_goal = false; //Reset mine_on_reach_goal.
			unitlist[i].mine_tile_id = 0; //Reset mine_tile_id
			unitlist[i].chopping = false; //Let the game know the unit stopped minin'.

						int i2 = 0;
			vector<ore*>::iterator iterator = ore_on_map.begin(); //Used to loop through ore on map list.
			vector<ore>::iterator iterator2 = Map[unitlist[i].mine_tile_id].orelist.begin(); //Used to loop through the new tile's ore list.

			for(; iterator < ore_on_map.end(); iterator++, i2++) //Remove all the ore from this tile...
			{
				cout << "Size: " << ore_on_map.size() << "\n"; //Debugging output...
				cout << "ID: " << ore_on_map[i2]->containing_tile->ID << "\n"; //Debugging output...
				if(ore_on_map[i2]->containing_tile->ID == new_tile.ID) //See if it found the right ore...
				{
					cout << "I did it! Found the ore! Removing it!\n"; //Debugging output.
					out_string << "I did it! Found the ore! Removing it!\n"; //Debugging output.

					ore_on_map.erase(iterator); //Remove the ore from the ore_on_map list.
				}
			}

			//TODO: Add the new ore into the ore_on_map thing.
			for(i2 = 0; iterator2 < new_tile.orelist.end(); iterator++, i2++)
			{
				ore_on_map.push_back(&Map[unitlist[i].mine_tile_id].orelist[Map[unitlist[i].mine_tile_id].orelist.size()]); //Add the current ore into the orelist.
				ore_on_map[ore_on_map.size() - 1]->containing_tile = &Map[unitlist[i].mine_tile_id]; //I guess this has to be reset for some weird reason.
			}

			unitlist[i].job_state = "idle"; //Be sure to reset the unit's state!
		}
		else
		{
			cout << "Tree not damaged enough to collapse! Gonna damage it a bit right now...\n";
			out_string << "Tree not damaged enough to collapse! Gonna damage it a bit right now...\n";


			int counter = 0;
			bool found = false; //Did it find a tool that meets the requirements?

			for(unitlist[i].iterator = unitlist[i].tool_list.begin(); unitlist[i].iterator < unitlist[i].tool_list.end(); unitlist[i].iterator++, counter++) //Loop through the tool list
			{
				if(found == false && unitlist[i].tool_list[counter].can_chop_tree == true && Map[unitlist[i].mine_tile_id].minimumn_mining_power <= unitlist[i].tool_list[counter].drill_power) //If the tool meets all the requirements to chop down this tree...
				{
					Map[unitlist[i].mine_tile_id].health[0] -= unitlist[i].tool_list[counter].drill_rate; //Subtract the tool's drill rate from this tile's health. //TODO: Remember when going through and changing mining that this needs to be changed too.
					found = true;
					cout << "Tree's new health: " << Map[unitlist[i].mine_tile_id].health[0] << "\n"; //TODO: Remember when going through and changing chopping that this needs to be changed too.
					Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].chopping_message_spr, 1, false); //Draw the "Whee, mining!" message.
				}
			}
		}
	}
}

void tile::rubble_to_ground(int i) //TODO: This fails on generating the third ore in a three ore generating thing.
{

	Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].shovelling_message_spr, 1, false); //Draw the "I'm shovelling" message.

	if(!paused)
	{
		//if(health[num_shovels - 1] <= 0 && num_shovels <= 0) //This checks if the shovelling is completely done.
		if(num_shovels <= 0 && health[0] <= 0) //This checks if the shovelling is completely done.
		{
			cout << "Done shovelling rubble! You can go home now!\n"; //Debugging output.

			unitlist[i].shovelling = false; //Tell the unit it's done shovelling.
			unitlist[i].shovel_on_reach_goal = false; //Reset mine_on_reach_goal.

			//Turn this tile into a ground tile.
			tile new_tile; //The tile this tile is going to be transforming into.

			new_tile = Tile_Type_Manager.get_by_id(ground_type); //Grab the properties of the specified tile it turns into.
			new_tile.wx = wx; //Give the new tile this tile's world x.
			new_tile.wy = wy; //Give the new tile this tile's world y.
			new_tile.layer = layer; //Give the new tile this tile's layer.
			new_tile.ID = ID; //Give the new tile this tile's ID.
			new_tile.unitlist = unitlist; //Copy over this tile's unitlist.
			new_tile.orelist = orelist; //Copy over this tile's orelist.
			new_tile.energy_crystal_list = energy_crystal_list; //Copy over this tile's energy crystal list.
			new_tile.obstruction = obstruction; //Copy over the obstruction variable.
			if(has_construction) //If this tile has a construction.
			{
				new_tile.has_construction = true; //So the new tile has a construction.
				new_tile.local_construction = local_construction; //Copy over this tile's construction.
			}

			//---------------------------
			//Now what's gonna happen here is the game's gonna remove all the ore on this tile from the ore on map list, and then add the ore from the tile we just created. Otherwise the ore on map list would be full of pointers to nonexistant ore. We can't have none of that!
			//---------------------------


			int i2 = 0; //Used to iterate through the ore on map list.
			vector<ore*>::iterator iterator = ore_on_map.begin(); //Used to loop through ore on map list.
			cout << "ore_on_map.size(): " << ore_on_map.size() << "\n"; //Debugging output.

			//for(; iterator < ore_on_map.end(); iterator++, i2++) //Remove all the ore from this tile...
			for(i2 = 0; i2 < ore_on_map.size(); iterator++, i2++) //Remove all the ore from this tile...
			{
				cout << "Size: " << ore_on_map.size() << "\n"; //Debugging output...
				//cout << "ID: " << (int)ore_on_map[i2]->containing_tile->ID << "\n"; //Debugging output...

				if(ore_on_map[i2]->containing_tile == this) //See if it found the right ore...
				{
					cout << "I did it! Found the ore! Removing it!\n"; //Debugging output.
					out_string << "I did it! Found the ore! Removing it!\n"; //Debugging output.

					//ore_on_map.erase(iterator); //Remove the ore from the ore_on_map list.
					ore_on_map.erase(ore_on_map.begin() + i2); //Remove the ore from the ore_on_map list.
					i2--; //So that it doesn't skip any ore.
				}
			}

			//---------------------------
			//End of removing the old ore from the ore on map list code.
			//---------------------------

			Map[ID] = new_tile; //Assign the tile.

			/*for(int i2 = 0; i < Map[ID].orelist.size(); i++)
			{
				Map[ID].orelist[i].containing_tile = &Map[ID];
				cout << "Map[ID].orelist[i].containing_tile->ID = " << Map[ID].orelist[i].containing_tile->ID << "\n";
			}*/

			vector<ore>::iterator iterator2 = orelist.begin(); //Used to loop through the new tile's ore list.

			//Add the new ore into the ore_on_map thing.
			for(int i2 = 0; iterator2 < Map[ID].orelist.end(); iterator2++, i2++) //Loop through all of this tile's ore.
			{
				ore_on_map.push_back(&Map[ID].orelist[i2]); //Add the current ore into the ore on map list.
				ore_on_map[ore_on_map.size() - 1]->containing_tile = &Map[ID]; //I guess this has to be reset for some weird reason.
			}

			//---------------------------
			//End of the transfering the new ore onto the ore on map list code.
			//---------------------------

			std::cout << "\n\n" << new_tile.wx << "," << new_tile.wy << "," << new_tile.layer << "," << new_tile.ID << "," << Map[unitlist[i].mine_tile_id].ground_type << "," << new_tile.type_id << "\n\n"; //Debugging output.

			unitlist[i].job_state = "idle"; //Be sure to reset the unit's state!
		}
		//else if(health[num_shovels - 1] <= 0) //This checks if the current shovel is done.
		else if(health[num_shovels - 1] <= 0) //This checks if the current shovel is done.
		{
			cout << "Num shovels: " << num_shovels << "\n";
			cout << "health.size(): " << health.size() << "\n";
			out_string << "Done with a shovel!\n"; //Debugging output.

			num_shovels--; //First, reduce the number of shovels left.
			health.pop_back(); //Remove the last element of health. For obvious reasons.

			out_string << "Health: \n";
			for(int i = 0; i < num_shovels; i++)
			{
				out_string << health[i] << "\n";
			}
			out_string << "\n";

			//Now generate ore.
			cout << "Generatin some ore for ya.\n"; //Debugging output.

			int num_to_gen = num_ore_to_generate; //Grab the number of ore it generates.

			for(int i2 = 0; i2 < num_to_gen; i2++) //Keep adding ore until all the requested ore have been generated.
			{
				ore new_ore = Ore_Type_Manager.get_by_id(ore_gen_ids[0]); //Grab the properties of the new ore. TODO: Make this randomally choose an ID from ore_gen_ids.
				new_ore.containing_tile = this; //Let the newly created ore know which tile it's sitting on.
				orelist.push_back(new_ore); //Add the new ore to the orelist.
				orelist[orelist.size() - 1].containing_tile = this;  //I guess this has to be reset for some weird reason.
				ore_on_map.push_back(&orelist[orelist.size() - 1]); //Add the ore that was just created into the ore one map list.
				ore_on_map[ore_on_map.size() - 1] = &orelist[orelist.size() - 1];
				ore_on_map[ore_on_map.size() - 1]->containing_tile = this; //I guess this has to be reset for some weird reason.

				cout << "ore.containing_tile->ID = " << ore_on_map[ore_on_map.size() - 1]->containing_tile->ID << "\n"; //TODO: Valgrind says:
				/*
				==15706== 
				==15706== 1 errors in context 1 of 274:
				==15706== Invalid read of size 4
				==15706==    at 0x429FBE: tile::rubble_to_ground(int) (terrain.cpp:994)
				==15706==    by 0x4270BD: tile::update() (terrain.cpp:388)
				==15706==    by 0x41CDE9: update() (update.cpp:161)
				==15706==    by 0x41ED9F: main (main.cpp:224)
				==15706==  Address 0xa0 is not stack'd, malloc'd or (recently) free'd
				==15706== 
				==15706== 
				==15706== 1 errors in context 2 of 274:
				==15706== Invalid read of size 8
				==15706==    at 0x429FBA: tile::rubble_to_ground(int) (terrain.cpp:994)
				==15706==    by 0x4270BD: tile::update() (terrain.cpp:388)
				==15706==    by 0x41CDE9: update() (update.cpp:161)
				==15706==    by 0x41ED9F: main (main.cpp:224)
				==15706==  Address 0x1149cc98 is not stack'd, malloc'd or (recently) free'd
				*/

				cout << "Generating ore with type: " << ore_gen_ids[0] << "\n\n"; //Debugging output.
			}


			//TODO: Increase the animation thingy...
		}
		else if(health[num_shovels - 1] > 0) //So, all the other checks returned false. Here the rubble's health is lowered by the unit's shovel.
		{
			//cout << "Shovelling! Shovelling! Shovelling I am!\n"; //Debugging output.

			//cout << "Health: " << health[num_shovels - 1] << ", num_shovels: " << num_shovels - 1 << "\n"; //Debugging output.



			//Subtract the raider's shovel's damage from the health of the tile.
			int counter = 0; //Used in the for loop below.
			bool found = false; //Did it find the tool that meets its requirements?

			for(unitlist[i].iterator = unitlist[i].tool_list.begin(); unitlist[i].iterator < unitlist[i].tool_list.end(); unitlist[i].iterator++, counter++) //Loop through the tool list
			{
				if(found == false && unitlist[i].tool_list[counter].can_clear_rubble == true && minimumn_mining_power <= unitlist[i].tool_list[counter].shovel_power) //If the tool meets all the requirements to shovel this rubble...
				{
					health[num_shovels - 1] -= unitlist[i].tool_list[counter].default_rubble_damage; //Subtract the tool's shovel rate from this tile's health.
					found = true; //Found the appropiate tool.
					//cout << "Rubble's new health: " << health[num_shovels - 1]<< "\n";
				}
			}
		}
	}
}

vector<tile> Map; //This is the vector that stores the entire map...
vector<int> Active_Map; //This is the vector that stores all of the indexes of the active tiles...
vector<int> Draw_Map; //This is the vector that stores all of the indexes of the tiles that are in the camera's view.
std::vector<ore*> ore_on_map; //Points to all the ore that is currently laying around the place.
