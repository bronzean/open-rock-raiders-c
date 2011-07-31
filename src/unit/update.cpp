/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the unit header.
using namespace std;

/* --------------------------------------------------------------
 * The unit's update function is defined here.
 * ----------------------------------------------------------- */

std::string bClassUnit::update()
{
	update_return = ""; //The variable it returns.

	if(move && !paused) //If the unit is moving somewhere.
	{
		if(Map[move_path[0]].wx < wx && move_left != NULL) //Check if the tile is to the left.
		{
			cout << "Blarg. Tile to the left and has move left animation.\n";

			bool can_animate = true;
			if(Map[move_path[0]].has_construction) //Check if the tile has a construction, and if the construction is a door, check if its open.
			{
				if(Map[move_path[0]].local_construction->door && !Map[move_path[0]].local_construction->construction_open)
				{
					cout << "Waiting for door to open.\n";
					can_animate = false;

					Map[move_path[0]].local_construction->open_thyself(false); //OPEN THE DOOR.

					bool allowed_to_close_door = true;

					if(my_job)
					{
						if(my_job->type == "open door" && my_job->tasked_tile == &Map[move_path[0]]) //Specifically check to make sure the unit is not supposed to close the door afterwards.
						{
							allowed_to_close_door = false;
						}
					}

					if(allowed_to_close_door)
					{
						needs_to_close_door = true; //Tell the unit it needs to close the door behind itself.
						needs_to_close_door_tile = &Map[move_path[0]]; //Tell the unit which tile is the one that at needs to close the door of.
						moves_till_close_door_time = 1;
					}
				}
			}

			if(can_animate)
			{
				active_animation = move_left;

				//Progress the animation.
				//(float)open_ammount / (float)open_time >= (float)animations[open_animation_entry].current_frame + 1
				//if( (float)((my_job->build_time * my_job->_animation->num_frames) - my_job->construction_health) / (float)my_job->build_time >= (float)my_job->_animation->current_frame + 1)
				if((float)frames_since_last_move / (float)move_speed >= (float)move_left->current_frame + 1) //Check if it is time to update the animation.
				{
					move_left->proceed_animation(); //PROGRESS THE ANIMATION.

					wx -= tile_width / move_right->num_frames; //To make it look like it's moving.
				}

				if(!allow_move)
				{
					if(frames_since_last_move >= move_speed * move_left->num_frames) //If the number of frames that have passed >= the move speed...
					{
						allow_move = true; //Allow movement again.
						frames_since_last_move = 0; //Reset frames_since_last_move.
					}
					frames_since_last_move++; //Increment the frames that have passed since the last move.
				}

				if(job_state == "constructing")
				{
					Draw_Message_Handler.add_message(wx + tile_width, wy, PCamera->layer, construct_walking_message_spr, 1, false); //Draw the "I'm coming to construct stuff!" message.
				}
			}
		}
		else if(Map[move_path[0]].wx > wx && move_right != NULL) //Check if the tile is to the right.
		{
			cout << "Blarg. Tile to the right and has move right animation.\n";

			bool can_animate = true;
			if(Map[move_path[0]].has_construction) //Check if the tile has a construction, and if the construction is a door, check if its open.
			{
				if(Map[move_path[0]].local_construction->door && !Map[move_path[0]].local_construction->construction_open)
				{
					cout << "Waiting for door to open.\n";
					can_animate = false;

					Map[move_path[0]].local_construction->open_thyself(false); //OPEN THE DOOR.

					bool allowed_to_close_door = true;

					if(my_job)
					{
						if(my_job->type == "open door" && my_job->tasked_tile == &Map[move_path[0]]) //Specifically check to make sure the unit is not supposed to close the door afterwards.
						{
							allowed_to_close_door = false;
						}
					}

					if(allowed_to_close_door)
					{
						needs_to_close_door = true; //Tell the unit it needs to close the door behind itself.
						needs_to_close_door_tile = &Map[move_path[0]]; //Tell the unit which tile is the one that at needs to close the door of.
						moves_till_close_door_time = 1;
					}
				}
			}

			if(can_animate)
			{
				active_animation = move_right;

				//Progress the animation.
				if((float)frames_since_last_move / (float)move_speed >= (float)move_right->current_frame + 1) //Check if it is time to update the animation.
				{
					move_right->proceed_animation(); //PROGRESS THE ANIMATION.

					wx += tile_width / move_right->num_frames; //To make it look like it's moving.
				}

				if(!allow_move)
				{
					if(frames_since_last_move >= move_speed * move_left->num_frames) //If the number of frames that have passed >= the move speed...
					{
						allow_move = true; //Allow movement again.
						frames_since_last_move = 0; //Reset frames_since_last_move.
					}
					frames_since_last_move++; //Increment the frames that have passed since the last move.
				}

				if(job_state == "constructing")
				{
					Draw_Message_Handler.add_message(wx + tile_width, wy, PCamera->layer, construct_walking_message_spr, 1, false); //Draw the "I'm coming to construct stuff!" message.
				}
			}
		}
		else if(Map[move_path[0]].wy < wy && move_up != NULL) //Check if the tile is to the north.
		{
			cout << "Blarg. Tile to the north and has move up animation.\n";

			bool can_animate = true;
			if(Map[move_path[0]].has_construction) //Check if the tile has a construction, and if the construction is a door, check if its open.
			{
				if(Map[move_path[0]].local_construction->door && !Map[move_path[0]].local_construction->construction_open)
				{
					cout << "Waiting for door to open.\n";
					can_animate = false;

					Map[move_path[0]].local_construction->open_thyself(false); //OPEN THE DOOR.

					bool allowed_to_close_door = true;

					if(my_job)
					{
						if(my_job->type == "open door" && my_job->tasked_tile == &Map[move_path[0]]) //Specifically check to make sure the unit is not supposed to close the door afterwards.
						{
							allowed_to_close_door = false;
						}
					}

					if(allowed_to_close_door)
					{
						needs_to_close_door = true; //Tell the unit it needs to close the door behind itself.
						needs_to_close_door_tile = &Map[move_path[0]]; //Tell the unit which tile is the one that at needs to close the door of.
						moves_till_close_door_time = 1;
					}
				}
			}

			if(can_animate)
			{
				active_animation = move_up;

				//Progress the animation.
				if((float)frames_since_last_move / (float)move_speed >= (float)move_up->current_frame + 1) //Check if it is time to update the animation.
				{
					move_up->proceed_animation(); //PROGRESS THE ANIMATION.

					wy -= tile_width / move_up->num_frames; //To make it look like it's moving.
				}

				if(!allow_move)
				{
					if(frames_since_last_move >= move_speed * move_left->num_frames) //If the number of frames that have passed >= the move speed...
					{
						allow_move = true; //Allow movement again.
						frames_since_last_move = 0; //Reset frames_since_last_move.
					}
					frames_since_last_move++; //Increment the frames that have passed since the last move.
				}

				if(job_state == "constructing")
				{
					Draw_Message_Handler.add_message(wx + tile_width, wy, PCamera->layer, construct_walking_message_spr, 1, false); //Draw the "I'm coming to construct stuff!" message.
				}
			}
		}
		else if(Map[move_path[0]].wy > wy && move_down != NULL) //Check if the tile is to the south.
		{
			bool can_animate = true;
			if(Map[move_path[0]].has_construction) //Check if the tile has a construction, and if the construction is a door, check if its open.
			{
				if(Map[move_path[0]].local_construction->door && !Map[move_path[0]].local_construction->construction_open)
				{
					cout << "Waiting for door to open.\n";
					can_animate = false;

					Map[move_path[0]].local_construction->open_thyself(false); //OPEN THE DOOR.

					bool allowed_to_close_door = true;

					if(my_job)
					{
						if(my_job->type == "open door" && my_job->tasked_tile == &Map[move_path[0]]) //Specifically check to make sure the unit is not supposed to close the door afterwards.
						{
							allowed_to_close_door = false;
						}
					}

					if(allowed_to_close_door)
					{
						needs_to_close_door = true; //Tell the unit it needs to close the door behind itself.
						needs_to_close_door_tile = &Map[move_path[0]]; //Tell the unit which tile is the one that at needs to close the door of.
						moves_till_close_door_time = 1;
					}
				}
			}

			if(can_animate)
			{
				cout << "Blarg. Tile to the south and has move down animation.\n";

				active_animation = move_down;

				//Progress the animation.
				if((float)frames_since_last_move / (float)move_speed >= (float)move_down->current_frame + 1) //Check if it is time to update the animation.
				{
					move_down->proceed_animation(); //PROGRESS THE ANIMATION.

					wy += tile_width / move_down->num_frames; //To make it look like it's moving.
				}

				if(!allow_move)
				{
					if(frames_since_last_move >= move_speed * move_left->num_frames) //If the number of frames that have passed >= the move speed...
					{
						allow_move = true; //Allow movement again.
						frames_since_last_move = 0; //Reset frames_since_last_move.
					}
					frames_since_last_move++; //Increment the frames that have passed since the last move.
				}

				if(job_state == "constructing")
				{
					Draw_Message_Handler.add_message(wx + tile_width, wy, PCamera->layer, construct_walking_message_spr, 1, false); //Draw the "I'm coming to construct stuff!" message.
				}
			}
		}
		else
		{
			if(allow_move == false) //If the unit is not allowed to move...
			{
				if(frames_since_last_move >= move_speed) //If the number of frames that have passed >= the move speed...
				{
					allow_move = true; //Allow movement again.
					frames_since_last_move = 0; //Reset frames_since_last_move.
				}
				frames_since_last_move++; //Increment the frames that have passed since the last move.
			}

			if(job_state == "constructing")
			{
				Draw_Message_Handler.add_message(wx + tile_width, wy, PCamera->layer, construct_walking_message_spr, 1, false); //Draw the "I'm coming to construct stuff!" message.
			}
		}
	}
	//Check how many frames have passed since last move.
	//Ff the number frames >= the move speed, then allow movement.
	else if(allow_move == false && !paused) //If the unit is not allowed to move...
	{
		if(frames_since_last_move >= move_speed) //If the number of frames that have passed >= the move speed...
		{
			allow_move = true; //Allow movement again.
			frames_since_last_move = 0; //Reset frames_since_last_move.
		}
		frames_since_last_move++; //Increment the frames that have passed since the last move.
	}

	if(closing_door)
	{
		if(close_door_tile->has_construction) //Check if the tile has a construction, and if the construction is a door, check if its open.
		{
			if(close_door_tile->local_construction->door) //Check if that tile even has a door.
			{
				if(close_door_tile->local_construction->construction_open) //Check if the door is open.
				{
					close_door_tile->local_construction->close_thyself(false); //Close the door!
				}
				else //Door is open.
				{
					cout << "Done closing door.\n"; //Debugging output.

					if(my_job) //Check if the unit's job exists.
					{
						delete my_job; //Delete it.
						my_job = NULL; //Reset this.
					}

					cancel_current_activity(); //Wrap things up.
				}
			}
		}
	}

	if(!server) //If this is not the server.
	{

		if(allow_deselect && allow_unit_selection) //If the unit is allowed to be deselected...TODO: If shift or some other key is pressed, make it so that allow_deselect will equal false.
		{
			select(); //Check if the unit has selected/deselected it.
		}

		if(mining_mode) //If the unit is awaiting the user to tell it which wall to mine.
		{
			//Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, select_wall_to_mine_spr, 1); //Draw the "Whee, mining!" message.
			Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, select_wall_to_mine_spr, 1, false);
			check_mine_command(); //Check if the player is ordering this unit to mine walls.

			cout << "Mining mode.\n";
		}

		if(!mining_mode) //So, it isn't mining mode...
		{
			if(keystates[SDLK_4] && selected == true) //If '4' was pressed
			{
				bool found = false; //Did the game find a drill in the player's inventory?

				for(unsigned int i = 0; i < tool_list.size(); i++) //Find out if the unit is carrying a drill.
				{
					if(tool_list[i].can_drill_wall == true) //If the the tool at index i in this tile's tool_list is able to drill walls...

					{
						found = true; //Let's the game know it found a drill in the unit's inventory.
					}
				}

				if(found == true) //If it found a drill.
				{				
					mining_mode = true; //Let the game know that the player is going to mine a wall.
					allow_deselect = false; //Don't allow the player to deselect this unit.
					job_state = "mining";
				}
				else //Didn't find a drill
				{
					cout << "You need a drill to mine walls!\n"; //Debugging output.
				}
			}
		}

		if(!pick_up_mode) //Here the game checks if the player is ordering this unit to get out its axe.
		{
			if(keystates[SDLK_g] && selected == true) //If the key 'g' was pressed.
			{
				allow_deselect = false; //Make sure the unit is not allowed to be deselected...

				pick_up_mode = true; //Let the game know the unit is waiting for the player to specify what it will pick up.
				job_state = "picking_up";
			}
		}
		else //Ok, so pick up mode equals true.
		{
			draw(0, 0, select_object_to_pick_up_spr, screen); //Draw message "Select an object to pick up." TODO: Make this use messages...
			check_pick_up_command(); //Check if the player is ordering the unit to pick up an object.
		}

		if(!chop_mode) //So, is chop mode equal to false?
		{
			if(keystates[SDLK_c]) //Check if the 'c' key was pressed.
			{
				if(selected == true || player == true) //If the unit is selected or it is the player...
				{

					bool found = false; //Did the game find an axe or something in the player's inventory?

					for(unsigned int i = 0; i < tool_list.size(); i++) //Find out if the unit is carrying a tool that can chop trees.
					{
						if(tool_list[i].can_chop_tree == true) //If the tool at index i of this tile's tool list is able to chop trees...
						{
							found = true; //Let's the game know it found a tool that can chop trees in the unit's inventory.
						}
					}

					if(found == true) //If it found a tool that can chop trees...
					{				
						chop_mode = true; //Let the game know that the player is going to chop a tree.
						allow_deselect = false; //Make sure the unit can't be unselected...
						job_state = "chopping";
					}
					else //Didn't find an axe.
					{
						cout << "You need a tool that can chop trees!\n"; //Debugging output.
					}
				}
			}
		}
		else //Ok, this means that the game is waiting for the user to tell the unit which tree to chop.
		{
			draw(0, 0, select_tree_to_chop_spr, screen); //Draw message "Select an object to pick up." TODO: Make this use messages...
		}

		if(!shovel_mode) //If the user hasn't allready given the unit a shovel order...
		{
			if(keystates[SDLK_r] && selected == true) //Check if the 'r' key was pressed.
			{
				bool found = false; //Did the game find a shovel in the player's inventory?

				for(unsigned int i = 0; i < tool_list.size(); i++) //Find out if the unit is carrying a shovel.
				{
					if(tool_list[i].can_clear_rubble == true) //If the tool at index i of this unit's tool list is able to clear rubble...
					{
						found = true; //Let's the game know it found a shovel in the unit's inventory.
					}
				}

				if(found == true) //If it found a shovel.
				{				
					shovel_mode = true; //Let the game know that the player is going to shovel a wall.
					allow_deselect = false; //Make sure the unit will not be deselected...
					job_state = "shoveling";
				}
				else //Didn't find a shovel.
				{
					cout << "You need a shovel to clear rubble!\n"; //Let the user know the unit needs a shovel to shovel rubble.
				}
			}
		}
		else //So, a shovel command has allready been issued.
		{
			draw(0, 0, select_rubble_to_shovel_spr, screen); //Draw the "select rubble to shovel" message.
			check_shovel_command(); //Check if the player is ordering the unit to shovel rubble.
		}

		if(active_popup_menu)
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

	if(job_state == "idling")
	{
		try
		{
			check_job(); //Since the unit is idling, might as well give it something to do.
		}
		catch(...)
		{
			cout << "Caught exception from check_job().\n";
			gameover = true;
		}
	}
	else if(job_state == "constructing")
	{
		construct_construction(); //Build the construction!!!
	}

	if(!paused && !server) //If the game is not paused.
	{
		if(keystates[SDLK_RIGHT]) //If the user has pressed the right arrow key.
		{
			if(selected == true || player == true) //If the unit is selected or it is the player's unit.
			{
				update_return = "m_right"; //Tell the calling tile that the unit is moving to the tile to the right.
			}
		}

		if(keystates[SDLK_LEFT]) //If the user has pressed the left arrow key.
		{
			if(selected == true || player == true) //If the unit is selected or it is the player's unit.
			{

				update_return = "m_left"; //Tell the calling tile that the unit is moving to the tile to the left.
			}
		}

		if(keystates[SDLK_UP]) //If the user has pressed the up arrow key.
		{
			if(selected == true || player == true) //If the unit is selected or it is the player's unit.
			{
				update_return = "m_up"; //Tell the calling tile that the unit is moving to the tile north of it.
			}
		}

		if(keystates[SDLK_DOWN]) //If the user has pressed the down arrow key.
		{
			if(selected == true || player == true) //If the unit is selected or it is the player's unit.
			{
				update_return = "m_down"; //Tell the calling tile that the unit is moving to the tile south of it.
			}
		}
	}

	return update_return; //Return. update_return stores various information for the calling function to process.
}
