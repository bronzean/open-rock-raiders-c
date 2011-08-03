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
			if(!g_teleport_que.empty() && !paused) //Make sure the global teleport que is not empty, and the game is not paused.
			{
				cout << "Stuff to teleport.\n";

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

								//Now handle the animations.
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_left) //If there is a move left animation for this unit.
								{
									out_string << "Giving unit its move_left animation.\n";
									newUnit.move_left = new animation; //Create the new animation.
									*newUnit.move_left = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_left; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_right) //If there is a move right animation for this unit.
								{
									out_string << "Giving unit its move_right animation.\n";
									newUnit.move_right = new animation; //Create the new animation.
									*newUnit.move_right = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_right; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_up) //If there is a move up animation for this unit.
								{
									out_string << "Giving unit its move_up animation.\n";
									newUnit.move_up = new animation; //Create the new animation.
									*newUnit.move_up = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_up; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_down) //If there is a move down animation for this unit.
								{
									out_string << "Giving unit its move_down animation.\n";
									newUnit.move_down = new animation; //Create the new animation.
									*newUnit.move_down = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_down; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_left_carryore) //If there is a move left carryore animation for this unit.
								{
									out_string << "Giving unit its move_left_carryore animation.\n";
									newUnit.move_left_carryore = new animation; //Create the new animation.
									*newUnit.move_left_carryore = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_left_carryore; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_right_carryore) //If there is a move right carryore animation for this unit.
								{
									out_string << "Giving unit its move_right_carryore animation.\n";
									newUnit.move_right_carryore = new animation; //Create the new animation.
									*newUnit.move_right_carryore = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_right_carryore; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_up_carryore) //If there is a move up carryore animation for this unit.
								{
									out_string << "Giving unit its move_up_carryore animation.\n";
									newUnit.move_up_carryore = new animation; //Create the new animation.
									*newUnit.move_up_carryore = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_up_carryore; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_down_carryore) //If there is a move down carryore animation for this unit.
								{
									out_string << "Giving unit its move_down_carryore animation.\n";
									newUnit.move_down_carryore = new animation; //Create the new animation.
									*newUnit.move_down_carryore = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_down_carryore; //Copy over the animation.
								}
								//Drilling animations.
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_left) //If there is a takeout drill left animation for this unit.
								{
									out_string << "Giving unit its takeout_drill_left animation.\n";
									newUnit.takeout_drill_left = new animation; //Create the new animation.
									*newUnit.takeout_drill_left = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_left; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_right) //If there is a takeout drill right animation for this unit.
								{
									out_string << "Giving unit its takeout_drill_right animation.\n";
									newUnit.takeout_drill_right = new animation; //Create the new animation.
									*newUnit.takeout_drill_right = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_right; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_up) //If there is a takeout drill up animation for this unit.
								{
									out_string << "Giving unit its takeout_drill_up animation.\n";
									newUnit.takeout_drill_up = new animation; //Create the new animation.
									*newUnit.takeout_drill_up = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_up; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_down) //If there is a takeout drill left animation for this unit.
								{
									out_string << "Giving unit its takeout_drill_down animation.\n";
									newUnit.takeout_drill_down = new animation; //Create the new animation.
									*newUnit.takeout_drill_down = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_down; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_left) //If there is a drill left animation for this unit.
								{
									out_string << "Giving unit its drill_left animation.\n";
									newUnit.drill_left = new animation; //Create the new animation.
									*newUnit.drill_left = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_left; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_right) //If there is a drill right animation for this unit.
								{
									out_string << "Giving unit its drill_right animation.\n";
									newUnit.drill_right = new animation; //Create the new animation.
									*newUnit.drill_right = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_right; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_up) //If there is a drill up animation for this unit.
								{
									out_string << "Giving unit its drill_up animation.\n";
									newUnit.drill_up = new animation; //Create the new animation.
									*newUnit.drill_up = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_up; //Copy over the animation.
								}
								if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_down) //If there is a drill down animation for this unit.
								{
									out_string << "Giving unit its drill_down animation.\n";
									newUnit.drill_down = new animation; //Create the new animation.
									*newUnit.drill_down = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_down; //Copy over the animation.
								}

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
