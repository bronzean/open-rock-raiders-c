/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp

/* --------------------------------------------------------------
 * Everything related to the "check if user has given a pick up object command" stuff is defined here.
 * ----------------------------------------------------------- */

bool bClassUnit::check_pick_up_command() //Checks if a pick up object command was issued.
{
	cout << "in check pick up function!\n";
	//int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
	if(event_struct.button.button == SDL_BUTTON_LEFT && event_struct.type == SDL_MOUSEBUTTONDOWN && pick_up_stage == 0) //If the left mouse button was clicked and the pick up stage is 0 (Awaiting tile to be selected)
	{
		cout << "chose it!\n";
		allow_deselect = true;
		bool run = true;
		//Check if a tile was clicked
		for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++)
		{
			cout << "I: " << i << "\n";
			if(run)
			{
				//Check if the tile is the one that was clicked on.
				if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
				{
					out_string << "Found it!\n";
					run = false;

					//std::cout << "Position of the tile to be mined: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";
					//out_string << "Position of the tile to be mined: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";

					if(Map[i].wall == false) //If said tile is not a wall...
					{
						//pick_up_mode = false; //let the game know pick up mode is off.
						//move = true; //Let the game know that the unit is moving somewhere.
						//move_destination = i; //Let the game know that the move destination of this unit is the tile that was just clicked on.
						//pick_up_tile_id = i; //Let the game know what the pick up target is...
						//pick_up_on_reach_goal = true; //Tells the unit to pick up the object once it reaches its goal.
						//layer_offset = (num_row_objects * num_col_objects * Map[i].layer); //Assign the layer offset.

						/*if(calculate_path() == false) //If it can't calculate find a path...
						{
							
							//Inaccessible tile...
							move = false; //Tell the unit it's staying put
							move_destination = 0; //Reset the unit's move destination.
							pick_up_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
							picking_up = false; //Reset this so that the game knows to not mine pick up anything...
						}*/

						//TODO: Check if the tile has any objects.
						//TODO: Then check what objects are on there.
						//TODO: If more than 1, create a pop-up menu asking player which one to pick up.
						//TODO: Once the player desides which one, check if the unit can pick it up, then tell the unit to go pick it up.
						//TODO: If just 1, then check if the unit can pick it up, then tell the unit to go pick it up.

						//First, check how many objects the tile has. If it has 0, then let the game know there's nothing for the unit to pick up.
						//If 1, then go to pick up stage 2.
						//If 2+, then go to stage 1.

						//Actually, after further thought, I think stage 1 should be dumped in here.

						bool has_ore = false; //Does the tile have any ore?
						int num_ore = 0; //The number of ore the tile has.
						int total_objects = 0; //How many objects, that can be picked up, are on the tile?

						if(Map[i].orelist.size() < 1) //First check if the object lists are empty. If they all are, there's nothing to pick up here... //TODO: Add the rest of the object lists here.
						{
							//Nothing to pick up
							cout << "Nothing to pick up here!\n";
							out_string << "Nothing to pick up here!\n";

							move = false; //Tell the unit it's staying put.
							move_destination = 0; //Reset the unit's move destination.
							pick_up_on_reach_goal = false; //Nup, no object's getting a free ride home.
							pick_up_mode = false; //Turn off pick up mode...

							return false; //Ya, no use continuing.
						}

						if(Map[i].orelist.size() > 0) //Now we check if it's the orelist that had anything in it.
						{
							has_ore = true; //If it is, let the game know the tile has ore on it.
							num_ore = Map[i].orelist.size(); //Retrieve the number of ore on it.
							total_objects += num_ore; //Add the number of ore on this tile with the total number of objects on this tile.

							cout << "Yay! Has Ore!\nTODO REMINDER: Check what other objects are on the title, and if there are more, as the player which one they want.\nAnother one: If there is more than one ore, ask the player which one they want the unit to pick up. Very important!\n";

							move = true; //Let the game know the unit is moving.
							move_destination = i; //Let the game know what the location of the tile is.
							pick_up_on_reach_goal = true; //Yippie! The unit is gonna be collecting some stuff tonight.
							pick_up_mode = false; //Turn off pick up mode...

							if(calculate_path() == false) //If it can't calculate find a path...
							{
								move = false; //Tell the unit it doesn't have anywhere to go.
								move_destination = 0; //Reset the unit's move destination.
								pick_up_on_reach_goal = false; //Ya, don't want the unit randomaly trying to pick up nonexistant objects.

								cout << "Couldn't find path!\n"; //Debugging output.

								return false;
							}

							return true; //For now, return true. TODO: Later refine this function to check the other objects and also ask the user which object to pick up if there are multiple on the tile.
						}
					}
					else 
					{
						move = false; //Tell the unit it's staying put
						move_destination = 0; //Reset the unit's move destination.
						pick_up_on_reach_goal = false; //Nup, no objects getting a free ride home.
						pick_up_mode = false; //Turn off pick up mode..
						cout << "Can't pick up a wall!\n"; //Debugging output.
						out_string << "Can't pick up a wall!\n";

						return false; //No use in continuing!
					}
				}
			}
		}
	}
	else if(pick_up_stage == 1) //Ok, multiple objects. Create a pop-up menu asking the player to select the object to be picked up from a list.
	{
		//TODO: Create a pop-up menu asking player which object to pick up.
		//TODO: Then check if the player can pick up said object.
		//TODO: And finally, tell the unit to go pick that object up.
	}
	else if(pick_up_stage == 2) //Only one object. PICK IT UP!
	{
		//TODO: Check if the unit can pick up that object.
		//TODO: Then tell the unit to pick it up.
	}

	return false;
}
