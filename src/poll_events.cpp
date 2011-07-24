/* Copyright the ORR-C Dev Team */
#include "main.hpp"
#include "engine/EObject.hpp"
#include "engine/Interface.hpp"

/* --------------------------------------------------------------
 * Does event handling and whatnot. Also cleans up the update.cpp file a bit!
 * ----------------------------------------------------------- */

void poll_events() //Checks for keyboard events, mouse events, all the good stuff. Also cleans up update.cpp quite a bit!
{
	while(SDL_PollEvent(&event_struct))
	{
		//when the user presses close window...
		if(event_struct.type == SDL_QUIT)
		{
			//Quit the program
			gameover = 1;
		}

		if(GameState == Level) //If the game is currently in-level.
		{
			if(event_struct.type == SDL_MOUSEBUTTONDOWN) //Check if a mouse button was pressed.
			{
				//I wonder if I should move code into the interface update function...
				if(event_struct.button.button == SDL_BUTTON_LEFT) //Check if it was the left mouse button.
				{
					if(!server) //If not in server mode...
					{
						//--------------------------------------------------------------------
						//KEEP IN MIND THE FOLLOWING CODE IS OUT OF DATE AND MUST BE REWRITTEN.
						//--------------------------------------------------------------------
						std::cout << "\nLeft click\n"; //Debugging output.
						out_string << "\nLeft click\n"; //Debugging output.

						if(active_popup_menu)
						{
							bool found = false;

							for(int i = 0; i < Interface.active_popup_menus[0]->fields.size(); i++)
							{
								if(Interface.active_popup_menus[0]->fields[i].clicked())
								{
									cout << "A popup menu's field has been clicked.\n";
									found = true;
								}
							}
							if(!found)
							{
								allow_unit_selection = true;
								active_popup_menu = false;
								Interface.active_popup_menus.clear();
								tile_selected = false;
								selected_tile->selected = false;
								selected_tile = NULL;

								cout << "None found.\n";
							}
						}
						else if(tile_selected && selected_tile != NULL)
						{
tile_popup_menu_force_draw:
							cout << "Checking tile thing\n";

							Interface.active_popup_menus.clear(); //Empty this.
							active_popup_menu = false; //No active popup menu...

							if(selected_tile->wall == true) //Check if the selected tile is a wall.
							{
								cout << "Is a wall.\n"; //Debugging output.
								popup_menu *_popup_menu = selected_tile->wall_popup_menu; //Assign a pointer to the selected tile's popup menu.

								if(_popup_menu == NULL) //Check if the wall_popup_menu of the tile actually exists.
								{
									//Do NOTHING.

									cout << "Do NOTHING.\n";

									Interface.active_popup_menus.clear(); //Empty this.
									active_popup_menu = false; //No active popup menu...
									allow_unit_selection = true; //Allow units to be selected/deselected.
									selected_tile->selected = false; //This tile is selected no longer.
									tile_selected = false; //No selected tile.
									selected_tile = NULL; //Reset this.

									//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
								}
								else if(_popup_menu->fields.empty())
								{
									//Do NOTHING.

									cout << "Do NOTHING.\n";

									Interface.active_popup_menus.clear(); //Empty this.
									active_popup_menu = false; //No active popup menu...
									allow_unit_selection = true; //Allow units to be selected/deselected.
									selected_tile->selected = false; //This tile is selected no longer.
									tile_selected = false; //No selected tile.
									selected_tile = NULL; //Reset this.

									//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
								}
								else //Tile's wall_popup_menu is not empty. That means stuff happens when you click on this wall.
								{
									Interface.active_popup_menus.push_back(selected_tile->wall_popup_menu); //Store the location of the active popup menu.
									active_popup_menu = true; //Let there game know that there's currently an active popup menu.

									allow_unit_selection = false; //Dissallow the selection (and consequently, deselection) of units.

									//Tell the popup menu where to draw.
									_popup_menu->x = event_struct.button.x;
									_popup_menu->y = event_struct.button.y;

									_popup_menu->event_tile = &Map[leftclick_tile_id]; //Let the popup menu know which tile is involved in this.

									cout << "Storing popup menu of the tile.\n"; //Debugging output.
								}

								leftclick_tile_id = -1; //Reset this so that units don't go walking around when you issue this...
							}
							else if(selected_tile->rubble) //Check if the selected tile is rubble.
							{
								cout << "Rubble trouble!\n"; //Debugging output.
								popup_menu *_popup_menu = selected_tile->rubble_popup_menu; //Assign a pointer to the selected tile's popup menu.

								if(_popup_menu == NULL) //Check if the rubble_popup_menu of the tile actually exists.
								{
									//Do NOTHING.

									cout << "Do NOTHING.\n";

									Interface.active_popup_menus.clear(); //Empty this.
									active_popup_menu = false; //No active popup menu...
									allow_unit_selection = true; //Allow units to be selected/deselected.
									selected_tile->selected = false; //This tile is selected no longer.
									tile_selected = false; //No selected tile.
									selected_tile = NULL; //Reset this.

									//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
								}
								else if(_popup_menu->fields.empty())
								{
									//Do NOTHING.

									Interface.active_popup_menus.clear(); //Empty this.
									active_popup_menu = false; //No active popup menu...
									allow_unit_selection = true; //Allow units to be selected/deselected.
									selected_tile->selected = false; //This tile is selected no longer.
									tile_selected = false; //No selected tile.
									selected_tile = NULL; //Reset this.

									cout << "Do NOTHING.\n";

									//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
								}
								else //Tile's rubble_popup_menu is not empty. That means stuff happens when you click on this rubble.
								{
									Interface.active_popup_menus.push_back(_popup_menu); //Store the location of the active popup menu.
									active_popup_menu = true; //Let the game know that there's currently an active popup menu.

									allow_unit_selection = false; //Dissallow the selection (and consequently, deselection) of units.

									//Tell the popup menu where to draw.
									_popup_menu->x = event_struct.button.x;
									_popup_menu->y = event_struct.button.y;

									_popup_menu->event_tile = &Map[leftclick_tile_id]; //Let the popup menu know which tile is involved in this.

									cout << "Storying popup menu of the tile.\n"; //Debugging output.
								}

								leftclick_tile_id = -1; //Reset this so that units don't go walking around when you issue this...
							}
							else //Ya, tile doesn't yet have a popup menu.
							{
								//Remove the tile from the active map (if applicable).
								if(selected_tile->unitlist.size() < 1)
								{
									cout << "Removing tile from Active_Map.\n"; //Debugging output.
									bool done = false;
									for(unsigned int i2 = 0; i2 < Active_Map.size(); i2++)
									{
										if(Map[Active_Map[i2]].ID == selected_tile->ID && done == false)
										{
											Active_Map.erase(Active_Map.begin() + i2); //Remove this tile from Active_Map.
											done = true;
										}
									}
								}

								selected_tile->selected = false;
								tile_selected = false;
								selected_tile = NULL;

								allow_unit_selection = true;

								active_popup_menu = false; //Reset this.
								Interface.active_popup_menus.clear(); //Empty this, of course.
							}
						}
						else if(Interface.g_teleport_button.clicked()) //Check this first, so that it doesn't deselect or select anything if true is returned.
						{
							//Teleport code here
							std::cout << "\nGlobal teleport button clicked.\n"; //Debugging output.
							out_string << "\nGlobal teleport button clicked.\n"; //Debugging output.

							bool found = false; //Found an empty slot in the teleport que?
							bool continue_ = true; //There's a two part if-check thing below. This controls part of it.

							for(int i = 0; i < 9; i++) //Loop through the teleport que to find a free spot.
							{
								if(!found) //If it hasn't found a free spot...
								{
									if(g_teleport_que_name[i] == "") //Check if it's a free spot.
										found = true; //Found a free spot.
								}
								if(found && continue_)
								{
									g_teleport_que_name[i] = "raider";
									g_teleport_que ++;
									continue_ = false;
								}
							}
						}
						//--------------------------------------------------------------------
						//END OF OBSOLETE CODE.
						//--------------------------------------------------------------------
						else if(Interface.construct_wall_button.clicked() && !construction_location_select) //Check if the "Construct wall" button was clicked.
						{
							std::cout << "\nConstruct wall button clicked.\n"; //Debugging output.

							Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, choose_wall_location_spr, 1, false); //Adds a message to be drawn.
							allow_unit_selection = false; //Since the construct wall button was clicked, disable selection of units and whatnot.
							construction_wall_location_select = true; //Let the game know the user is going to select the location for a construction.
							construction_location_select = true; //Tells the game the player is selecting the location of a construction to be built.
						}
						else if(Interface.construct_door_button.clicked() && !construction_location_select) //Check if the construct door button was clicked.
						{
							std::cout << "\nConstruct door button clicked.\n"; //Debugging output.

							Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, choose_door_location_spr, 1, false); //Adds a message to be drawn.
							allow_unit_selection = false; //Since the construct door button was clicked, disable selection of units and whatnot.
							construction_door_location_select = true; 
							construction_location_select = true; //Tells the game the player is selecting the location of a construction to be built.
						}
						else
						{
							if(construction_location_select == false)
							{
								bool run = true; //Controls the loop below.

								//Check if a tile was clicked
								for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++) //TODO: Make it look through draw map only.
								{
									if(run)
									{
										//Check if the tile is 'in bounds'.
										if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
										{
											if(Map[i].unitlist.size() == 0) //If there are no units on this tile...
											{
												cout << "Does not have units on it, saving tile id!\n"; //Debugging output.
												leftclick_tile_id = i; //Save the ID of this tile only if no units are on this tile.

												std::cout << "\nFound the tile that the left click took place over...\n"; //Debugging output.
												out_string << "\nFound the tile that the left click took place over...\n"; //Debugging output.
												std::cout << "Position of that tile: (" << Map[leftclick_tile_id].wx << "," << Map[leftclick_tile_id].wy << "," << Map[leftclick_tile_id].layer << ") and index is: " << i << "\n"; //Debugging output.
												out_string << "Position of that tile: (" << Map[leftclick_tile_id].wx << "," << Map[leftclick_tile_id].wy << "," << Map[leftclick_tile_id].layer << ") and index is: " << i << "\n"; //Debugging output.

												if(!unit_selected)
												{
													cout << "Bringing up popup menu for tile.\n"; //Debugging output.
													//Bring up an 'actions' menu (Like in LRR).

													Map[leftclick_tile_id].selected = true; //Let the tile know it is now selected.
													tile_selected = true; //Let the game know that a tile is currently selected.
													selected_tile = &Map[leftclick_tile_id]; //Store a pointer to the currently selected tile.

													//Store the tile in the active tiles vector.
													bool found = false;

													for(unsigned int i2 = 0; i2 < Active_Map.size(); i2++) //Check if the tile is already in active_map.
													{
														if(Map[Active_Map[i2]].ID == selected_tile->ID && found == false)
														{
															found = true;
														}
													}

													if(!found)
													{
														Active_Map.push_back(selected_tile->ID);

														cout << "Found. Adding to active map.\n";
													}

													goto tile_popup_menu_force_draw; //Force it to draw the popup menu of the tile on this click. This way, tiles don't have to be double clicked for them to draw their popup menu.
												}
											}


											run = false;
										}
									}
								}

								//if(tile_selected)
								//{
									//goto tile_popup_menu_force_draw; //Force it to draw the popup menu of the tile on this click. This way, tiles don't have to be double clicked for them to draw their popup menu.
								//}
							}
							else if(construction_wall_location_select)
							{
								//cout << "Here!\n";
								//Find the tile that was selected...
								bool run = true; //Controls the loop below.
								int tile_id = -1; //The ID of the tile that was selected.

								//Check if a tile was clicked
								for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++) //TODO: Make it look through draw map only.
								{
									if(run)
									{
										//Check if the tile is 'in bounds'.
										if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
										{
											tile_id = i; //Save the ID of this tile only if no units are on this tile.

											cout << "Found the tile!\n";

											run = false;
										}
									}
								}

								if(tile_id <= -1 || Map[tile_id].wall == true || Map[tile_id].tree == true || Map[tile_id].rubble == true || Map[tile_id].has_construction == true)
								{
									cout << "Invalid tile!\n\n";

									allow_unit_selection = true;
									construction_wall_location_select = false;
									construction_location_select = false;
								}
								else
								{
									//Add a construct wall command to the job que.
									job new_job;

									new_job.type = "construct";
									new_job.construction_type = "wall";
									new_job.tasked_tile = &Map[tile_id];

									Job_Que.add_job(new_job);
									//Job_Que.jobs[Job_Que.jobs.size() - 1].tasked_tile = &Map[tile_id];

									cout << "Added job!\n";

									allow_unit_selection = true;
									construction_wall_location_select = false;
									construction_location_select = false;
								}
							}
							else if(construction_door_location_select)
							{
								//Find the tile that was selected.
								bool run = true; //Controls the loop below.
								int tile_id = 0; //The ID of the tile that was selected.

								//Check if a tile was clicked.
								for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++)
								{
									if(run)
									{
										//Check if the tile is 'in bounds'.
										if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
										{
											tile_id = i; //Save the ID of this tile only if no units are on this tile.

											cout << "Found the tile!\n";

											run = false;
										}
									}
								}

								if(tile_id <= -1 || Map[tile_id].wall == true || Map[tile_id].tree == true || Map[tile_id].rubble == true || Map[tile_id].has_construction == true)
								{
									cout << "Invalid tile!\n\n";

									allow_unit_selection = true;
									construction_wall_location_select = false;
									construction_location_select = false;
								}
								else
								{
									//Add a construct door command to the job que.
									job new_job;

									new_job.type = "construct";
									new_job.construction_type = "door";
									new_job.tasked_tile = &Map[tile_id];

									Job_Que.add_job(new_job);
									//Job_Que.jobs[Job_Que.jobs.size() - 1].tasked_tile = &Map[tile_id];

									cout << "Added job!\n";

									allow_unit_selection = true;
									construction_door_location_select = false;
									construction_location_select = false;
								}
							}
							else
							{
								construction_location_select = false;
							}

							//TODO: Move unit selection code here.
						}
					}
				}
				if(event_struct.button.button == SDL_BUTTON_RIGHT)
				{
					std::cout << "Right click\n"; //Debugging output.
					out_string << "Right click\n";

					if(!server)
					{
						bool run = true; //Controls the loop below.

						//Check if a tile was clicked
						for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++)
						{
							if(run)
							{
								//Check if the tile is 'in bounds'.
								if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
								{
									rightclick_tile_id = i; //Assign the tile id...

									run = false;

									std::cout << "\nFound the tile that the right click took place over...\n";
									out_string << "\nFound the tile that the right click took place over...\n";
									std::cout << "Position of that tile: (" << Map[rightclick_tile_id].wx << "," << Map[rightclick_tile_id].wy << "," << Map[rightclick_tile_id].layer << ") and index is: " << i << "\n";
									out_string << "Position of that tile: (" << Map[rightclick_tile_id].wx << "," << Map[rightclick_tile_id].wy << "," << Map[rightclick_tile_id].layer << ") and index is: " << i << "\n";
								}
							}
						}

						if(unit_selected)
						{
							Interface.active_popup_menus.clear(); //Empty this.
							active_popup_menu = false; //No active popup menu...
							allow_unit_selection = true; //Allow units to be selected/deselected.

							if(Map[rightclick_tile_id].wall) //Check if the right clicked tile is a wall.
							{
								popup_menu *_popup_menu = selected_unit->wall_popup_menu; //Assign a pointer to the selected unit's popup menu.

								if(_popup_menu == NULL) //Check if the wall_popup_menu of the unit actually exists.
								{
									//Do NOTHING.

									cout << "Do NOTHING.\n";

									//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
								}
								else if(_popup_menu->fields.empty())
								{
									//Do NOTHING.

									cout << "Do NOTHING.\n";

									//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
								}
								else //Unit's wall_popup_menu is not empty. That means stuff happens when you click on a wall.
								{
									Interface.active_popup_menus.push_back(selected_unit->wall_popup_menu); //Store the location of the active popup menu.

									active_popup_menu = true; //Let there game know that there's currently an active popup menu.

									allow_unit_selection = false; //Dissallow the deselection of the unit.

									//Tell the popup menu where to draw.
									_popup_menu->x = event_struct.button.x;
									_popup_menu->y = event_struct.button.y;

									_popup_menu->event_tile = &Map[rightclick_tile_id]; //Let the popup menu know which tile is involved in this.

									cout << "Storing popup menu of the unit.\n"; //Debugging output.
								}

								rightclick_tile_id = -1; //Reset this so that units don't go walking around when you issue this...
							}
							else if(Map[rightclick_tile_id].rubble) //Check if the right clicked tile is rubble.
							{
								popup_menu *_popup_menu = selected_unit->rubble_popup_menu; //Assign a pointer to the selected unit's popup menu.

								if(_popup_menu == NULL) //Check if the rubble_popup_menu of the unit actually exists.
								{
									//Do NOTHING.

									cout << "Do NOTHING.\n"; //Debugging output.

									//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
								}
								else if(_popup_menu->fields.empty())
								{
									//Do NOTHING.

									cout << "Do NOTHING.\n";

									//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
								}
								else //Unit's rubble_popup_menu is not empty. That means stuff happens when you click on rubble.
								{
									Interface.active_popup_menus.push_back(selected_unit->rubble_popup_menu); //Store the location of the active popup menu.

									active_popup_menu = true; //Let the game know that there's currently an active popup menu.

									allow_unit_selection = false; //Dissallow the deselection of the unit.

									//Tell the popup menu where to draw.
									_popup_menu->x = event_struct.button.x;
									_popup_menu->y = event_struct.button.y;

									_popup_menu->event_tile = &Map[rightclick_tile_id]; //Let the popup menu know which tile is involved in this.

									for(int i = 0; i < _popup_menu->fields.size(); i++) //Remove all "pickup any ore" fields.
									{
										if(_popup_menu->fields[i].field_data == "pickup any ore") //Check if the current field is a "pickup any ore" field.
										{
											_popup_menu->fields.erase(_popup_menu->fields.begin() + i); //Remove  it.
											i--; //Deincrement this so that no entries are skipped.
										}
									}

									if(Map[rightclick_tile_id].orelist.size() > 0) //If there's any ore on this tile.
									{
										//TODO: Add the "pickup any ore" field
										selected_unit->rubble_popup_menu->fields.push_back(field_pickup_any_ore); //Add the "pick up any any ore" field.
										selected_unit->rubble_popup_menu->fields[selected_unit->rubble_popup_menu->fields.size() - 1].parent_menu = selected_unit->rubble_popup_menu; //Assign the new field's parent menu.

										//TODO: Add a "Pick up ore" field for every ore.
									}

									cout << "Storing popup menu of the unit.\n"; //Debugging output.
								}

								rightclick_tile_id = -1; //Reset this so that units don't go walking around when you issue this...
							}
							else if(Map[rightclick_tile_id].ground) //Check if the right clicked tile is ground.
							{
								if(!Map[rightclick_tile_id].obstruction)
								{
									cout << "Checking ground_popup_menu.\n";
									popup_menu *_popup_menu = selected_unit->ground_popup_menu; //Assign a pointer to the selected unit's popup menu.

									if(_popup_menu == NULL) //Check if the ground_popup_menu of the unit actually exists.
									{
										//Do NOTHING.

										cout << "Do NOTHING.\n"; //Debugging output.

										//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
									}
									else if(_popup_menu->fields.empty())
									{
										//Do NOTHING.

										cout << "Do NOTHING.\n";

										//TODO: Play a sound and show the "YOU CAN'T DO THAT" icon.
									}
									else //Unit's ground_popup_menu is not empty. That means stuff happens when you click on ground.
									{
										Interface.active_popup_menus.push_back(selected_unit->ground_popup_menu); //Store the location of the active popup menu.

										active_popup_menu = true; //Let the game know that there's currently an active popup menu.

										allow_unit_selection = false; //Dissallow the deselection of the unit.

										//Tell the popup menu where to draw.
										_popup_menu->x = event_struct.button.x;
										_popup_menu->y = event_struct.button.y;

										_popup_menu->event_tile = &Map[rightclick_tile_id]; //Let the popup menu know which tile is involved in this.

										for(int i = 0; i < _popup_menu->fields.size(); i++) //Remove all "pickup any ore", and the constructions, fields, and close/open fields.
										{
											if(_popup_menu->fields[i].field_data == "pickup any ore" || _popup_menu->fields[i].field_data == "construct wall" || _popup_menu->fields[i].field_data == "construct door" || _popup_menu->fields[i].field_data == "open door" || _popup_menu->fields[i].field_data == "close door") //Check if the current field is one to be removed.
											{
												_popup_menu->fields.erase(_popup_menu->fields.begin() + i); //Remove  it.
												i--; //Deincrement this so that no entries are skipped.
											}
										}

										if(Map[rightclick_tile_id].orelist.size() > 0) //If there's any ore on this tile.
										{
											//TODO: Add the "pickup any ore" field
											selected_unit->ground_popup_menu->fields.push_back(field_pickup_any_ore); //Add the "pick up any ore" field.
											selected_unit->ground_popup_menu->fields[selected_unit->ground_popup_menu->fields.size() - 1].parent_menu = selected_unit->ground_popup_menu; //Assign the new field's parent menu.

											//TODO: Add a "Pick up ore" field for every ore.
										}
										else if(!Map[rightclick_tile_id].has_construction) //No ore. Check if there is a construction on here.
										{
											selected_unit->ground_popup_menu->fields.push_back(field_construct_wall); //Add the "construct wall" field.
											selected_unit->ground_popup_menu->fields[selected_unit->ground_popup_menu->fields.size() - 1].parent_menu = selected_unit->ground_popup_menu; //Assign the new field's parent menu.
											selected_unit->ground_popup_menu->fields.push_back(field_construct_door); //Add the "construct door" field.
											selected_unit->ground_popup_menu->fields[selected_unit->ground_popup_menu->fields.size() - 1].parent_menu = selected_unit->ground_popup_menu; //Assign the new field's parent menu.
										}

										if(Map[rightclick_tile_id].has_construction) //Check if the tile has a construction on it.
										{
											if(Map[rightclick_tile_id].local_construction->door) //Check if the construction is a door.
											{
												if(Map[rightclick_tile_id].local_construction->construction_open) //Check if the door is open.
												{
													selected_unit->ground_popup_menu->fields.push_back(field_close_door); //Add the "close door" field.
													selected_unit->ground_popup_menu->fields[selected_unit->ground_popup_menu->fields.size() - 1].parent_menu = selected_unit->ground_popup_menu; //Assign the new field's parent menu.
												}
												else //Door isn't open.
												{
													selected_unit->ground_popup_menu->fields.push_back(field_open_door); //Add the "open door" field.
													selected_unit->ground_popup_menu->fields[selected_unit->ground_popup_menu->fields.size() - 1].parent_menu = selected_unit->ground_popup_menu; //Assign the new field's parent menu.
												}
											}
										}

										cout << "Storing popup menu of the unit.\n"; //Debugging output.
									}

									rightclick_tile_id = -1; //Reset this so that units don't go walking around when you issue this...
								}
							}

						}
					}
				}
			}

			if(event_struct.type == SDL_KEYDOWN)
			{
				switch(event_struct.key.keysym.sym)
				{
					case SDLK_p: //Here, we check if the p key was pressed...
						if(!paused)
						{
							paused = true; //If the game isn't paused, pause the game.
							std::cout << "Paused.\n"; //Debugging output.
							out_string << "Paused.\n";
						}
						else
						{
							paused = false; //Unpuase the game if it's paused.
							std::cout << "Unpaused.\n"; //Debugging output.
							out_string << "Unpaused.\n";
						}
						break;
					case SDLK_2:
						//Check if the camera is on the last layer...
						if(PCamera->layer < num_layers  - 1)
						{
							PCamera->layer++; //If so, move it up a layer.
							std::cout << "\nMoving camera up a layer\n"; //Debugging output.
							out_string << "\nMoving camera up a layer\n"; //Debugging output.

							//current_layer_sprite = NULL; //Reset current_layer_sprite so that it doesn't keep expanding it with new messages.
							current_layer_string.str(""); //Reset current_layer_string so that it doesn't keep expanding it with new messages.
							current_layer_string << "Current layer: " << PCamera->layer; //The text that informs the player what layer they're on.
							current_layer_sprite = TTF_RenderText_Solid(font1, current_layer_string.str().c_str(), c_white); //Render the current layer message onto current_layer_sprite.

							//Now add all the tiles that have come into the camera's view, and remove the old ones.
							int layer_offset = (num_row_objects * num_col_objects * PCamera->layer); //Assign the layer offset.
							int current_tile = layer_offset; //The current tile it's working on.

							Draw_Map.clear(); //Empty Draw_Map.

							while(current_tile < layer_offset + (num_row_objects * num_col_objects)) //While current_tile is still on this same layer.
							{
								if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wx() + Map[current_tile].get_width() >= PCamera->wx && Map[current_tile].get_wx() <= (PCamera->wx + SCREEN_WIDTH) && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //If the tile is onscreen...
								{
									Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
								}

								current_tile++; //Increment current tile.
							}
						}
						break;

					case SDLK_3:
						//Check if the camera is on the last layer...
						if(PCamera->layer > 0)
						{
							PCamera->layer--; //If so, move it up a layer.
							std::cout << "\nMoving camera down a layer\n"; //Debugging output.
							out_string << "\nMoving camera down a layer\n";

							current_layer_string.str(""); //Reset current_layer_string so that it doesn't keep expanding it with new messages.
							current_layer_string << "Current layer: " << PCamera->layer; //The text that informs the player what layer they're on.
							current_layer_sprite = TTF_RenderText_Solid(font1, current_layer_string.str().c_str(), c_white); //Render the current layer message onto current_layer_sprite.

							//Now add all the tiles that have come into the camera's view, and remove the old ones.
							int layer_offset = (num_row_objects * num_col_objects * PCamera->layer); //Assign the layer offset.
							int current_tile = layer_offset; //The current tile it's working on.

							Draw_Map.clear(); //Empty Draw_Map.

							while(current_tile < layer_offset + (num_row_objects * num_col_objects)) //While current_tile is still on this same layer.
							{
								if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wx() + Map[current_tile].get_width() >= PCamera->wx && Map[current_tile].get_wx() <= (PCamera->wx + SCREEN_WIDTH) && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //If the tile is onscreen...
								{
									Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
								}

								current_tile++; //Increment current tile.
							}
						}
						break;
					case SDLK_LEFT:
						move_issued = true;
						break;
					case SDLK_RIGHT:
						move_issued = true;
						break;
					case SDLK_UP:
						move_issued = true;
						break;
					case SDLK_DOWN:
						move_issued = true;
						break;
				}
			}
		}
	}
}
