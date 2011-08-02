/* Copyright the ORR-C Dev Team */
#include "tile.hpp"

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

				bool allowed_to_close_door = true;

				if(unitlist[i].my_job)
				{
					if(unitlist[i].my_job->type == "open door" && unitlist[i].my_job->tasked_tile == &Map[unitlist[i].move_path[0]]) //Specifically check to make sure the unit is not supposed to close the door afterwards.
					{
						allowed_to_close_door = false;
					}
				}

				if(allowed_to_close_door)
				{
					unitlist[i].needs_to_close_door = true; //Tell the unit it needs to close the door behind itself.
					unitlist[i].needs_to_close_door_tile = &Map[unitlist[i].move_path[0]]; //Tell the unit which tile is the one that at needs to close the door of.
					unitlist[i].moves_till_close_door_time = 3;
				}
			}
		}

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

						cout << "closing door.\n"; //Debugging output.
					}
					else
					{
						unitlist[i].needs_to_close_door = false; //Tell the unit it needs to close the door behind itself no longer.
						unitlist[i].needs_to_close_door_tile = NULL; //Reset this.

						cout << "Door already closed, or not a door.\n"; //Debugging output.
					}

					/*if(!unitlist[i].needs_to_close_door_tile->local_construction->construction_open)
					{
						unitlist[i].needs_to_close_door = false; //Tell the unit it needs to close the door behind itself no longer.
						unitlist[i].needs_to_close_door_tile = NULL; //Reset this.
					}*/
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
				unitlist[i].moves_till_close_door_time--; //Deincrement this.
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

			unitlist.erase(unitlist.begin() + i); //Remove this unit from this tile. Otherwise it would be the self replicating raiders glitch all over again.

	

			if(unitlist.size() < 1)
			{
				bool allow_remove = true;

				if(has_construction)
				{
					if(local_construction->teleporter)
					{
						allow_remove = false;
					}
				}

				if(allow_remove)
				{
					cout << "Removing tile from Active_Map.\n"; //Debugging output.
					bool done = false;
					for(unsigned int i2 = 0; i2 < Active_Map.size(); i2++)
					{
						if(Map[Active_Map[i2]].ID == ID && done == false)
						{
							Active_Map.erase(Active_Map.begin() + i2); //Remove this tile from Active_Map.
							done = true;
							cout << "Erased from active_map.\n";
							out_string << "Erased from active_map.\n";
						}
					}
				}
			}
			//Make sure the tile isn't already in active map.
			bool found_entry = false;
			for(unsigned int i2 = 0; i2 < Active_Map.size(); i2++)
			{
				if(Map[Active_Map[i2]].ID == Map[new_tile_id].ID)
				{
					found_entry = true;
					cout << "Tile already in active_map.\n";
					out_string << "Tile already in active_map.\n";
				}
			}
			if(found_entry == false)
			{
				Active_Map.push_back(Map[new_tile_id].ID); //Add the index of the tile the unit just moved to to Active_Map.
				cout << "Entry (active_map.size() - 1): " << Active_Map.size() - 1 << "\n";
				out_string << "Entry(active_map.size() - 1): " << Active_Map.size() - 1 << "\n";

				cout << "Active_Map[Active_Map.size() - 1]: " << Active_Map[Active_Map.size() - 1] << "\n";
				out_string << "Active_Map[Active_Map.size() - 1]: " << Active_Map[Active_Map.size() - 1] << "\n";
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
