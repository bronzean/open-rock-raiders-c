/* Copyright the ORR-C Dev Team */
#include "tile.hpp"


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

			//Add the new ore into the ore_on_map thing.
			for(i2 = 0; iterator2 < new_tile.orelist.end(); iterator++, i2++)
			{
				ore_on_map.push_back(&Map[unitlist[i].mine_tile_id].orelist[Map[unitlist[i].mine_tile_id].orelist.size()]); //Add the current ore into the orelist.
				ore_on_map[ore_on_map.size() - 1]->containing_tile = &Map[unitlist[i].mine_tile_id]; //I guess this has to be reset for some weird reason.
			}

			//unitlist[i].job_state = "idling"; //Be sure to reset the unit's state!

			unitlist[i].cancel_current_activity();
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
