/* Copyright the ORR-C Dev Team */
#include "tile.hpp"

void tile::rubble_to_ground(int i)
{
	Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].shovelling_message_spr, 1, false); //Draw the "I'm shovelling" message.

	if(!paused)
	{
		unitlist[i].shoveling_animation(); //Animate the shoveling, if applicable.

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

			//unitlist[i].job_state = "idle"; //Be sure to reset the unit's state!

			if(unitlist[i].my_job != NULL) //Check if the unit has a job.
			{
				delete unitlist[i].my_job; //Delete the unit's job.
				unitlist[i].my_job = NULL;

				cout << "Removed unit's job.\n";
			}

			unitlist[i].cancel_current_activity();

			unitlist[i].active_animation = NULL;
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

				cout << "ore.containing_tile->ID = " << ore_on_map[ore_on_map.size() - 1]->containing_tile->ID << "\n";

				cout << "Generating ore with type: " << ore_gen_ids[0] << "\n\n"; //Debugging output.
			}

			//Check to see if the "pickup any ore" field has been added.
			bool found = false;

			/*if(rubble_popup_menu != NULL)
			{
				if(!rubble_popup_menu->fields.empty())
				{
					for(int i = 0; i < rubble_popup_menu->fields.size)
					{
					}
				}
			}*/


			//TODO: Increase the animation thingy...
		}
		else if(health[num_shovels - 1] > 0) //So, all the other checks returned false. Here the rubble's health is lowered by the unit's shovel.
		{
			//cout << "Shovelling! Shovelling! Shovelling I am!\n"; //Debugging output.

			//cout << "Health: " << health[num_shovels - 1] << ", num_shovels: " << num_shovels - 1 << "\n"; //Debugging output.



			//Subtract the raider's shovel's damage from the health of the tile.
			int counter = 0; //Used in the for loop below.
			bool found = false; //Did it find the object that meets the requirements?

			for(unitlist[i].iterator = unitlist[i].object_list.begin(); unitlist[i].iterator < unitlist[i].object_list.end(); unitlist[i].iterator++, counter++) //Loop through the object list.
			{
				if(found == false && unitlist[i].object_list[counter].can_clear_rubble == true && minimumn_mining_power <= unitlist[i].object_list[counter].shovel_power) //If the object meets all the requirements to shovel this rubble...
				{
					health[num_shovels - 1] -= unitlist[i].object_list[counter].default_rubble_damage; //Subtract the object's shovel rate from this tile's health.
					found = true; //Found the appropiate object.
					//cout << "Rubble's new health: " << health[num_shovels - 1]<< "\n";
				}
			}
		}
	}
}
