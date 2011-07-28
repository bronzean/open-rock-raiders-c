/* Copyright the ORR-C Dev Team */
#include "construction.hpp"

void construction::update() //Update whatever needs updating.
{
	//cout << "Updating construction.\n";

	if(teleporter) //If this construction is a teleporter.
	{
		//cout << "Is teleporter.\n";
		if(def_teleporter == this) //Check if this is the default teleporter.
		{
			//cout << "Is default teleporter.\n";
			if(!g_teleport_que.empty()) //Make sure the global teleport que is not empty.
			{
				//cout << "Stuff to teleport.\n";
				//cout << "Stuff to teleport.\n";

				char temp = ' ';
				string variable = "";
				string paramater = "";
				bool check_variable = false;

				for(int i = 0; i < g_teleport_que[0].size(); i++)
				{
					temp = g_teleport_que[0][i];

					if(temp == '.')
					{
						check_variable = true;

						cout << "Time to check variable.\n";
						cout << "Variable: " << variable << "\n";
					}
					else
					{
						variable += temp;
					}

					if(check_variable)
					{
						if(variable == "unit")
						{
							for(; i < g_teleport_que[0].size(); i++)
							{
								if(paramater != "\x00")
									paramater += g_teleport_que[0][i];
							}

							cout << "Paramater: " << paramater << "\n";

							int unit_id_to_teleport = atoi(paramater.c_str());

							unit newUnit = Unit_Type_Manager.get_by_id(unit_id_to_teleport); //Grab the unit that has the same ID as this guy.

							//newUnit.wx = containing_tile->wx; //Assign the new unit's world x.
							//newUnit.wy = containing_tile->wy; //Assign the new unit's world y.
							//newUnit.layer = containing_tile->layer; //Assign the new unit's layer.
							//std::cout << "Created new unit.\n";

							int dest_tile = containing_tile->ID - 1; //First off, check the tile to the left.
							bool found = false; //Found a place to teleport to?

							if(dest_tile > 0 && dest_tile < num_tiles) //Check if the tile exists.
							{
								if(!Map[dest_tile].wall && !Map[dest_tile].obstruction)
								{
									found = true;
									cout << "Tile to the left works.\n";
								}
							}

							if(!found)
							{
								dest_tile = containing_tile->ID + 1; //Ok...Check tile to the right.

								if(dest_tile > 0 && dest_tile < num_tiles) //Check if the tile exists.
								{
									if(!Map[dest_tile].wall && !Map[dest_tile].obstruction)
									{
										found = true;
										cout << "Tile to the right works.\n";
									}
								}
							}

							if(!found)
							{
								dest_tile = containing_tile->ID - num_row_objects; //Ok...Check tile to the north.

								if(dest_tile > 0 && dest_tile < num_tiles) //Check if the tile exists.
								{
									if(!Map[dest_tile].wall && !Map[dest_tile].obstruction)
									{
										found = true;
										cout << "Tile to the north works.\n";
									}
								}
							}

							if(!found)
							{
								dest_tile = containing_tile->ID + num_row_objects; //Ok...Check tile to the south.

								if(dest_tile > 0 && dest_tile < num_tiles) //Check if the tile exists.
								{
									if(!Map[dest_tile].wall && !Map[dest_tile].obstruction)
									{
										found = true;
										cout << "Tile to the south works.\n";
									}
								}
							}

							if(found) //If it found space to teleport in the unit.
							{
								newUnit.wx = Map[dest_tile].wx; //Assign the new unit's world x.
								newUnit.wy = Map[dest_tile].wy; //Assign the new unit's world y.
								newUnit.layer = Map[dest_tile].layer; //Assign the new unit's layer.
								newUnit.c_health = 100; //Assign the new unit's current health.

								newUnit.rubble_popup_menu = new popup_menu;
								newUnit.rubble_popup_menu->fields.push_back(field_moveto); //Add this to the unit's popup menu.
								newUnit.rubble_popup_menu->fields[newUnit.rubble_popup_menu->fields.size() - 1].set_parent_menu(newUnit.rubble_popup_menu); //Let the new field know what popup_menu contains it.

								newUnit.ground_popup_menu = new popup_menu;
								newUnit.ground_popup_menu->fields.push_back(field_moveto); //Add this to the unit's popup menu.
								newUnit.ground_popup_menu->fields[newUnit.ground_popup_menu->fields.size() - 1].set_parent_menu(newUnit.ground_popup_menu); //Let the new field know what popup_menu contains it.

								Map[dest_tile].unitlist.push_back(newUnit); //Add the new unit to the tile.

								bool exists = false;

								for(int i = 0; i < Active_Map.size(); i++)
								{
									if(Active_Map[i] == Map[dest_tile].ID)
									{
										exists = true;

										cout << "Exists.\n";
									}
								}

								if(!exists)
								{
									Active_Map.push_back(dest_tile); //Tell the active map this tile needs updating.
								}

								cout << "Dest tile: " << dest_tile << "\n";
							}
							else
							{
								cout << "Unable to teleport in the unit.\n";
							}

							g_teleport_que.erase(g_teleport_que.begin()); //Remove the qued teleport.
						}
					}
				}
			}
		}
	}
}
