/* Copyright the ORR-C Dev Team */
#include "construction.hpp"
#include "../effects/graphic_effect_2d.hpp"
#include "../engine/sprite/sprite.hpp"
#include "../engine/Interface.hpp"

void construction::update() //Update whatever needs updating.
{
	//cout << "Updating construction.\n";

	if(teleporter) //If this construction is a teleporter.
	{
		//cout << "Is teleporter.\n";
		if(def_teleporter == this && !creating_unit) //Check if this is the default teleporter, and if it's not still working on the last teleport.
		{
			//cout << "Is default teleporter.\n";
			if(!g_teleport_que.empty() && !paused) //Make sure the global teleport que is not empty, and the game is not paused.
			{
				//cout << "Stuff to teleport.\n";

				if(!teleport_animation_done) //Check if the teleport animation has played yet.
				{
					cout << "Teleport animation.\n";

					if(teleport_animation)
					{
						active_animation = teleport_animation; //Tell the construction that it has an ongoing animation, and let it know it just happens to be the teleport animation.
					}

					if(teleport_animation && teleport_progress >= teleport_time) //Check if it has a teleport animation, and if it's time to progress it.
					{
						if(teleport_animation->current_frame == teleport_animation->num_frames - 1) //If the animation is over.
						{
							teleport_animation_done = true; //The teleport animation is done!
							teleport_animation->current_frame = 0; //Reset the teleport animation.
							active_animation = NULL;

							cout << "Teleporting done.\n";
						}
						else
						{
							cout << "Proceeding animation.\n";
							teleport_animation->proceed_animation(); //Progress the animation.
						}
						teleport_progress = 0; //Reset this.
					}
					else if(teleport_progress >= teleport_time) //No animation. Oh well, check if it's done sending the signal.
					{
						cout << "Done teleporting.\n";
						teleport_animation_done = true; //The teleport animation is done!
					}

					teleport_progress++; //Increment this.
				}
				else
				{
					teleport_animation_done = false;
					teleport_progress = 0;

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

								newUnit = new unit; //Allocate memory for the new unit.
								/*unit*/ *newUnit = Unit_Type_Manager.get_by_id(unit_id_to_teleport); //Grab the unit that has the same ID as this guy.

								//newUnit.wx = containing_tile->wx; //Assign the new unit's world x.
								//newUnit.wy = containing_tile->wy; //Assign the new unit's world y.
								//newUnit.layer = containing_tile->layer; //Assign the new unit's layer.
								//std::cout << "Created new unit.\n";

								/*int*/ dest_tile = containing_tile->ID - 1; //First off, check the tile to the left.
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
									creating_unit = true;

									create_flash(Map[dest_tile].wx + (tile_width / 2), Map[dest_tile].wy + (tile_height / 2), Map[dest_tile].layer, &whiteflash1); //Create a white flash at the specified location.

									newUnit->wx = Map[dest_tile].wx; //Assign the new unit's world x.
									newUnit->wy = Map[dest_tile].wy; //Assign the new unit's world y.
									newUnit->layer = Map[dest_tile].layer; //Assign the new unit's layer.
									newUnit->c_health = 100; //Assign the new unit's current health.

									newUnit->rubble_popup_menu = new popup_menu;
									newUnit->rubble_popup_menu->fields.push_back(field_moveto); //Add this to the unit's popup menu.
									newUnit->rubble_popup_menu->fields[newUnit->rubble_popup_menu->fields.size() - 1].set_parent_menu(newUnit->rubble_popup_menu); //Let the new field know what popup_menu contains it.

									newUnit->ground_popup_menu = new popup_menu;
									newUnit->ground_popup_menu->fields.push_back(field_moveto); //Add this to the unit's popup menu.
									newUnit->ground_popup_menu->fields[newUnit->ground_popup_menu->fields.size() - 1].set_parent_menu(newUnit->ground_popup_menu); //Let the new field know what popup_menu contains it.

									//Now handle the animations.
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_left) //If there is a move left animation for this unit.
									{
										out_string << "Giving unit its move_left animation.\n";
										newUnit->move_left = new animation; //Create the new animation.
										*newUnit->move_left = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_left; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_right) //If there is a move right animation for this unit.
									{
										out_string << "Giving unit its move_right animation.\n";
										newUnit->move_right = new animation; //Create the new animation.
										*newUnit->move_right = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_right; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_up) //If there is a move up animation for this unit.
									{
										out_string << "Giving unit its move_up animation.\n";
										newUnit->move_up = new animation; //Create the new animation.
										*newUnit->move_up = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_up; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_down) //If there is a move down animation for this unit.
									{
										out_string << "Giving unit its move_down animation.\n";
										newUnit->move_down = new animation; //Create the new animation.
										*newUnit->move_down = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_down; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_left_carryore) //If there is a move left carryore animation for this unit.
									{
										out_string << "Giving unit its move_left_carryore animation.\n";
										newUnit->move_left_carryore = new animation; //Create the new animation.
										*newUnit->move_left_carryore = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_left_carryore; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_right_carryore) //If there is a move right carryore animation for this unit.
									{
										out_string << "Giving unit its move_right_carryore animation.\n";
										newUnit->move_right_carryore = new animation; //Create the new animation.
										*newUnit->move_right_carryore = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_right_carryore; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_up_carryore) //If there is a move up carryore animation for this unit.
									{
										out_string << "Giving unit its move_up_carryore animation.\n";
										newUnit->move_up_carryore = new animation; //Create the new animation.
										*newUnit->move_up_carryore = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_up_carryore; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_down_carryore) //If there is a move down carryore animation for this unit.
									{
										out_string << "Giving unit its move_down_carryore animation.\n";
										newUnit->move_down_carryore = new animation; //Create the new animation.
										*newUnit->move_down_carryore = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).move_down_carryore; //Copy over the animation.
									}
									//Drilling animations.
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_left) //If there is a takeout drill left animation for this unit.
									{
										out_string << "Giving unit its takeout_drill_left animation.\n";
										newUnit->takeout_drill_left = new animation; //Create the new animation.
										*newUnit->takeout_drill_left = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_left; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_right) //If there is a takeout drill right animation for this unit.
									{
										out_string << "Giving unit its takeout_drill_right animation.\n";
										newUnit->takeout_drill_right = new animation; //Create the new animation.
										*newUnit->takeout_drill_right = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_right; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_up) //If there is a takeout drill up animation for this unit.
									{
										out_string << "Giving unit its takeout_drill_up animation.\n";
										newUnit->takeout_drill_up = new animation; //Create the new animation.
										*newUnit->takeout_drill_up = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_up; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_down) //If there is a takeout drill left animation for this unit.
									{
										out_string << "Giving unit its takeout_drill_down animation.\n";
										newUnit->takeout_drill_down = new animation; //Create the new animation.
										*newUnit->takeout_drill_down = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).takeout_drill_down; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_left) //If there is a drill left animation for this unit.
									{
										out_string << "Giving unit its drill_left animation.\n";
										newUnit->drill_left = new animation; //Create the new animation.
										*newUnit->drill_left = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_left; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_right) //If there is a drill right animation for this unit.
									{
										out_string << "Giving unit its drill_right animation.\n";
										newUnit->drill_right = new animation; //Create the new animation.
										*newUnit->drill_right = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_right; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_up) //If there is a drill up animation for this unit.
									{
										out_string << "Giving unit its drill_up animation.\n";
										newUnit->drill_up = new animation; //Create the new animation.
										*newUnit->drill_up = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_up; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_down) //If there is a drill down animation for this unit.
									{
										out_string << "Giving unit its drill_down animation.\n";
										newUnit->drill_down = new animation; //Create the new animation.
										*newUnit->drill_down = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).drill_down; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).shovel_animation) //If there is a shovel animation for this unit.
									{
										out_string << "Giving unit its shovel animation.\n";
										newUnit->shovel_animation = new animation; //Create the new animation.
										*newUnit->shovel_animation = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).shovel_animation; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).pick_up) //If there is a pickup animation for this unit.
									{
										out_string << "Giving unit its pickup animation.\n";
										newUnit->pick_up = new animation; //Create the new animation.
										*newUnit->pick_up = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).pick_up; //Copy over the animation.
									}
									if(Unit_Type_Manager.get_by_id(unit_id_to_teleport).teleport_in_animation) //If there is a teleporting in animation for this unit.
									{
										out_string << "Giving unit its teleport in animation.\n";
										newUnit->teleport_in_animation = new animation; //Create the new animation.
										*newUnit->teleport_in_animation = *Unit_Type_Manager.get_by_id(unit_id_to_teleport).teleport_in_animation; //Copy over the animation.
									}

									/*Map[dest_tile].unitlist.push_back(newUnit); //Add the new unit to the tile.

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

									cout << "Dest tile: " << dest_tile << "\n";*/
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
		else if(!g_teleport_que.empty())
		{
			if(teleport_animation)
			{
				teleport_animation->current_frame = 0; //Reset the teleport animation.
				active_animation = NULL;
			}
			teleport_progress = 0;
		}
		else if(creating_unit) //Is it currently in the process of creating a unit?
		{
			if(newUnit->teleport_in_animation) //If the unit has a teleport in animation.
			{
				//TODO: Draw the animation here.
				//newUnit->teleport_in_animation->

				sprite_wrapper* _sprite = new sprite_wrapper;
				_sprite->wx = newUnit->wx;
				_sprite->wy = newUnit->wy;
				_sprite->layer = newUnit->layer;
				_sprite->image = newUnit->teleport_in_animation->frames_spr[newUnit->teleport_in_animation->current_frame];
				Interface.add_sprite_that_needs_drawing(_sprite);

				if(!paused)
				{
					newUnit->teleport_in_progress++; //Increment this.

					if(newUnit->teleport_in_progress > newUnit->teleport_in_time) //If the time has transpired.
					{
						if(newUnit->teleport_in_animation->current_frame >= newUnit->teleport_in_animation->num_frames - 1) //Check if it's done with the animation.
						{
							creating_unit = false;
						}
						else
						{
							newUnit->teleport_in_animation->proceed_animation(); //Progress the animation.
							newUnit->teleport_in_progress = 0; //Reset this.
						}
					}
				}
			}
			else if(!paused) //No animation.
			{
				newUnit->teleport_in_progress++; //Increment this.

				if(newUnit->teleport_in_progress > newUnit->teleport_in_time) //If the time has transpired.
				{
					creating_unit = false;
				}
			}

			if(!creating_unit && !paused)
			{
				newUnit->teleport_in_progress = 0; //Reset this.

				Map[dest_tile].unitlist.push_back(*newUnit); //Add the new unit to the tile.

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

				delete newUnit; //Free up the memory.
				newUnit = NULL; //Reset the pointer.
				dest_tile = 0;
			}
		}
	}
}
