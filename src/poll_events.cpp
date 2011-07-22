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
						std::cout << "Left click\n"; //Debugging output.
						out_string << "Left click\n"; //Debugging output.

						if(Interface.g_teleport_button.clicked()) //Check this first, so that it doesn't deselect or select anything if true is returned.
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
													//TODO: Bring up an 'actions' menu (Like in LRR).
												}
											}


											run = false;
										}
									}
								}
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

								if(tile_id <= -1 || Map[tile_id].wall == true || Map[tile_id].tree == true || Map[tile_id].has_construction == true)
								{
									cout << "Invalid tile!\n";
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

								if(tile_id <= -1 || Map[tile_id].wall == true || Map[tile_id].tree == true || Map[tile_id].has_construction == true)
								{
									cout << "Invalid tile!\n";
								}
								else
								{
                                                                            //TODO: add a construct door command to the job que.
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
                                                            out_string << "\nMoving camera up a layer\n";

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
