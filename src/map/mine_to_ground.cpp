/* Copyright the ORR-C Dev Team */
#include "tile.hpp"

void tile::mine_to_ground(int i)
{
	//If drill isn't out, pull it out.
	if(!unitlist[i].drill_out)
	{
		if(!paused) //Make sure the game isn't paused.
		{
			unitlist[i].take_out_drill(); //TAKE OUT THE UNIT'S DRILL.
		}
	}
	else
	{
		Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].mining_message_spr, 1, false); //Draw the "Whee, mining!"
		if(!paused)
		{

			unitlist[i].drilling_animation(); //Animate the drilling, if applicable.

			//bClassUnit *temp_unit = &unitlist[i];
			if(Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels /*- 1*/] <= 0 && Map[unitlist[i].mine_tile_id].num_shovels <= 0) //This checks if the mining is completely done.
			{
				cout << "Mining wall!\n"; //Debugging output.

				unitlist[i].mining = false; //Tell the unit it's done mining.
				unitlist[i].mine_on_reach_goal = false; //Reset mine_on_reach_goal.

				//Generate ore, if any.

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

				if(unitlist[i].my_job != NULL) //Check if the unit has a job.
				{
					delete unitlist[i].my_job; //Delete the unit's job.
					unitlist[i].my_job = NULL;
				}

				unitlist[i].cancel_current_activity();

				unitlist[i].active_animation = NULL;
			}
			else if(Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels - 1] <= 0) //This checks if the current drill is done.
			{
				//out_string << "Done with a drill!\n"; //Debugging output.
				Map[unitlist[i].mine_tile_id].health.pop_back(); //Remove the last element of health. For obvious reasons.

				/*out_string << "Health: \n";
				for(int i = 0; i < Map[unitlist[i].mine_tile_id].num_shovels; i++)
				{
					out_string << Map[unitlist[i].mine_tile_id].health[i] << "\n";
				}
				out_string << "\n";*/

				if(Map[unitlist[i].mine_tile_id].drilling_animation == true)
				{
					//if(Map[unitlist[i].mine_tile_id].num_shovels != Map[unitlist[i].mine_tile_id].total_shovels)
					//{
						Map[unitlist[i].mine_tile_id].animations[Map[unitlist[i].mine_tile_id].drilling_animation_entry].proceed_animation(); //Increase the animation thingy.
					//}
					Map[unitlist[i].mine_tile_id].active_animation = true; //Let the game know an animation is going on for this tile.
					Map[unitlist[i].mine_tile_id].active_animation_entry = Map[unitlist[i].mine_tile_id].drilling_animation_entry; //Let it know the entry of the active animation in the animations vector.
					//cout << "Mine tile ID: " << Map[unitlist[i].mine_tile_id].ID << "\n";
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
						Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels - 1] -= unitlist[i].tool_list[counter].drill_rate; //Subtract the tool's drill rate from this tile's health.
						found = true;
						//cout << "Wall's new health: " << Map[unitlist[i].mine_tile_id].health[Map[unitlist[i].mine_tile_id].num_shovels - 1]<< "\n";
						Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].mining_message_spr, 1, false); //Draw the "Whee, mining!" message.

						if(!active_animation)
						{
							if(Map[unitlist[i].mine_tile_id].drilling_animation == true)
							{
								/*if(Map[unitlist[i].mine_tile_id].num_shovels != Map[unitlist[i].mine_tile_id].total_shovels)
								{
									Map[unitlist[i].mine_tile_id].animations[Map[unitlist[i].mine_tile_id].drilling_animation_entry].proceed_animation(); //Increase the animation thingy.
								}*/
								Map[unitlist[i].mine_tile_id].active_animation = true; //Let the game know an animation is going on for this tile.
								Map[unitlist[i].mine_tile_id].active_animation_entry = Map[unitlist[i].mine_tile_id].drilling_animation_entry; //Let it know the entry of the active animation in the animations vector.
								//cout << "Mine tile ID: " << Map[unitlist[i].mine_tile_id].ID << "\n";
							}
						}
					}
				}

				if(!found) //If it couldn't find a viable tool with which to drill the wall with.
				{
					cout << "Fool, watcha tryin to do? Don't ya know better than to tell units to mine walls which they can't mine?\n"; //Yell at the player.

					unitlist[i].cancel_current_activity(); //Cancel drilling.
				}
			}
		}
		else
		{
			Draw_Message_Handler.add_message(wx + 32, wy, layer, unitlist[i].mining_message_spr, 1, false); //Draw the "Whee, mining!"
		}
	}
}
