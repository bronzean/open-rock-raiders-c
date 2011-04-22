/* Copyright the ORR-C Dev Team */
#include "main.hpp"
#include "engine/EObject.hpp"
#include "engine/Interface.hpp"

void *DrawScreen(void *param)
{
	//int _GFPS = GFPS; //Copy this so that it won't be using the global one, which is subject to change, and might cause a crash...
	while(!gameover)
	{
		if(screen_needs_updating == true)
		{
			if(SDL_Flip(screen) == -1)
			{
				std::cerr << "\nError Updating Screen\n";
				out_string << "\nError Updating Screen\n";
				fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
				fflush(GameLog);
				screen_needs_updating = false;
				pthread_exit(NULL);
			}
			SDL_FillRect(screen, NULL, 0x00000000);

			screen_needs_updating = false;
		}
		SDL_Delay(GFPS);
	}
	pthread_exit(NULL);
}

int update()
{
	rightclick_tile_id = -1; //Reset rightclick_tile_id
	leftclick_tile_id = -1; //Reset leftclick_tile_id

	while(SDL_PollEvent(&event_struct))
	{
		//when the user presses close window...
		if(event_struct.type == SDL_QUIT)
		{
			//Quit the program
			gameover = 1;
		}

		if(GameState == Level)
		{
			if(event_struct.type == SDL_MOUSEBUTTONDOWN)
        		{
				if(event_struct.button.button == SDL_BUTTON_LEFT)
				{
					std::cout << "Left click\n"; //Debugging output.
					out_string << "Left click\n";
				}
				if(event_struct.button.button == SDL_BUTTON_RIGHT)
				{
					std::cout << "Right click\n"; //Debugging output.
					out_string << "Right click\n";
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

	//If the escape key was pressed...
	if(keystates[SDLK_ESCAPE])
	{
		gameover = 1;
		std::cout << "Escape pressed, quiting.\n"; //Debugging output.
		out_string << "Escape pressed, quiting.\n";
	}

	//If the 'n' key was pressed...
	if(keystates[SDLK_n])
	{
		FPS++; //Increase FPS cap.
		std::cout << "Increasing fps cap. Current:" << FPS << "\n"; //Debugging output.
		out_string << "Increasing fps cap. Current:" << FPS << "\n";
	}

	//If the 'm' key was pressed...
	if(keystates[SDLK_m] && FPS > 1)
	{
		FPS--; //Decrease FPS cap.
		std::cout << "Decreasing fps cap. Current:" << FPS << "\n"; //Debugging output.
		out_string << "Decreasing fps cap. Current:" << FPS << "\n";
	}

	if(GameState == Title && gameover != true)
	{
		//TODO: Replace this with the "lobby" thing.
		if(keystates[SDLK_RETURN]) //If enter was pressed...
		{
			GameState = Loading; //Load everything.
		}

		if(screen_needs_updating == false)
		{
			draw(0, 0, title_screen, screen); //Draw the title screen's background.
		}
	}

	else if(GameState == Loading && gameover != true)
	{
		try
		{
			string load_text = "";
			SDL_Surface *load_text_sprite = NULL;

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
			//Let the user know the tile types are being loaded...
			load_text = "Loading tile types";
			load_text_sprite = TTF_RenderText_Solid(font1, load_text.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
			draw((SCREEN_WIDTH / 2) - (load_text_sprite->w / 2), (SCREEN_HEIGHT / 2) - (load_text_sprite->h / 2), load_text_sprite, screen);
			SDL_FreeSurface(load_text_sprite);
			if(SDL_Flip(screen) == -1)
			{
				std::cerr << "\nError Updating Screen\n";
				out_string << "\nError Updating Screen\n";
				fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
				fflush(GameLog);
				return 1;
			}
			Tile_Type_Manager.load_types_from_file("data/terrain.cfg"); //load tile types
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
			//Let the user know the tool types are being loaded...
			load_text = "Loading tool types";
			load_text_sprite = TTF_RenderText_Solid(font1, load_text.c_str(), c_white); //Render the text onto the sprite
			draw((SCREEN_WIDTH / 2) - (load_text_sprite->w / 2), (SCREEN_HEIGHT / 2) - (load_text_sprite->h / 2), load_text_sprite, screen);
			SDL_FreeSurface(load_text_sprite);
			if(SDL_Flip(screen) == -1)
			{
				std::cerr << "\nError Updating Screen\n";
				out_string << "\nError Updating Screen\n";
				fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
				fflush(GameLog);
				return 1;
			}
			Tool_Type_Manager.load_types_from_file("data/tools.cfg"); //load tool types
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
			//Let the user know the ore types are being loaded...
			load_text = "Loading ore types";
			load_text_sprite = TTF_RenderText_Solid(font1, load_text.c_str(), c_white); //Render the text onto the sprite
			draw((SCREEN_WIDTH / 2) - (load_text_sprite->w / 2), (SCREEN_HEIGHT / 2) - (load_text_sprite->h / 2), load_text_sprite, screen);
			SDL_FreeSurface(load_text_sprite);
			if(SDL_Flip(screen) == -1)
			{
				std::cerr << "\nError Updating Screen\n";
				out_string << "\nError Updating Screen\n";
				fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
				fflush(GameLog);
				return 1;
			}
			Ore_Type_Manager.load_types_from_file("data/ore.cfg"); //load ore types
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
			//Let the user know the energy crystal types are being loaded...
			load_text = "Loading energy crystal types";
			load_text_sprite = TTF_RenderText_Solid(font1, load_text.c_str(), c_white); //Render the text onto the sprite
			draw((SCREEN_WIDTH / 2) - (load_text_sprite->w / 2), (SCREEN_HEIGHT / 2) - (load_text_sprite->h / 2), load_text_sprite, screen);
			SDL_FreeSurface(load_text_sprite);
			if(SDL_Flip(screen) == -1)
			{
				std::cerr << "\nError Updating Screen\n";
				out_string << "\nError Updating Screen\n";
				fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
				fflush(GameLog);
				return 1;
			}
			Energy_Crystal_Type_Manager.load_types_from_file("data/energy_crystal.cfg"); //load energy_crystal types
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
			//Let the user know the unit types are being loaded...
			load_text = "Loading unit types";
			load_text_sprite = TTF_RenderText_Solid(font1, load_text.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
			draw((SCREEN_WIDTH / 2) - (load_text_sprite->w / 2), (SCREEN_HEIGHT / 2) - (load_text_sprite->h / 2), load_text_sprite, screen);
			SDL_FreeSurface(load_text_sprite);
			if(SDL_Flip(screen) == -1)
			{
				std::cerr << "\nError Updating Screen\n";
				out_string << "\nError Updating Screen\n";
				fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
				fflush(GameLog);
				return 1;
			}
			Unit_Type_Manager.load_types_from_file("data/unit.cfg"); //Load the unit types.
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
			//Let the user know the level is being loaded...
			load_text = "Initializing constructions.";
			load_text_sprite = TTF_RenderText_Solid(font1, load_text.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
			draw((SCREEN_WIDTH / 2) - (load_text_sprite->w / 2), (SCREEN_HEIGHT / 2) - (load_text_sprite->h / 2), load_text_sprite, screen);
			SDL_FreeSurface(load_text_sprite);
			if(SDL_Flip(screen) == -1)
			{
				std::cerr << "\nError Updating Screen\n";
				out_string << "\nError Updating Screen\n";
				fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
				fflush(GameLog);
				return 1;
			}
			//Here all the constructions are initlialized and resources loaded.
			c_wall.init("wall", true, false, 0, "data/construction/wall/sprite.png"); //Initialize the wall construction.
			if(c_wall.sprite == NULL)
			{
				throw;
			}
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
			//Let the user know the level is being loaded...
			load_text = "Loading level";
			load_text_sprite = TTF_RenderText_Solid(font1, load_text.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
			draw((SCREEN_WIDTH / 2) - (load_text_sprite->w / 2), (SCREEN_HEIGHT / 2) - (load_text_sprite->h / 2), load_text_sprite, screen);
			SDL_FreeSurface(load_text_sprite);
			if(SDL_Flip(screen) == -1)
			{
				std::cerr << "\nError Updating Screen\n";
				out_string << "\nError Updating Screen\n";
				fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
				fflush(GameLog);
				return 1;
			}
			//load the level...
			std::string map_path = map_folder_path;
			map_path += "cfg";
			if(!Parser.parse_map_cfg2(map_path.c_str()))
			{
				gameover = true; //It failed, so quit.
			}
			if(!Parser.parse_map_layer(map_folder_path.c_str())) //Parse the map's actual files.
			{
			gameover = true; //It failed, so quit.
			}
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string
			//Now add all the tiles that are initially in the camera's view.
			int layer_offset = (num_row_objects * num_col_objects * PCamera->layer); //Assign the layer offset.
			int current_tile = layer_offset; //The current tile it's working on.
			while(current_tile < layer_offset + (num_row_objects * num_col_objects)) //While current_tile is still on this same layer.
			{
				if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wx() + Map[current_tile].get_width() >= PCamera->wx && Map[current_tile].get_wx() <= (PCamera->wx + SCREEN_WIDTH) && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //If the tile is onscreen...
				{
					Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
					cout << Map[Draw_Map[Draw_Map.size() - 1]].ID << "\n";
					out_string << Map[Draw_Map[Draw_Map.size() - 1]].ID << "\n";
				}

				current_tile++; //Increment current tile.
			}

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
			//Let the user know that whatever else needs to be loaded is being loaded.
			load_text = "Loading everything else";
			load_text_sprite = TTF_RenderText_Solid(font1, load_text.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
			draw((SCREEN_WIDTH / 2) - (load_text_sprite->w / 2), (SCREEN_HEIGHT / 2) - (load_text_sprite->h / 2), load_text_sprite, screen);
			SDL_FreeSurface(load_text_sprite);
			if(SDL_Flip(screen) == -1)
			{
				std::cerr << "\nError Updating Screen\n";
				out_string << "\nError Updating Screen\n";
				fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
				fflush(GameLog);
				return 1;
			}
			//TODO: load whatever else needs to be loaded...
			//Interface.g_teleport_button.init(teleport_button_spr->w, teleport_button_spr->h, teleport_button_spr, no_teleport_button_spr); //Initialize the teleport button.
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
			GameState = Level; //Done loading everything. Enter the level now.
		}
		catch(...)
		{		
			std::cerr << "Failed to load everything.\n";
			out_string << "Failed to laod everything.\n";
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog); //Write out_string to the log.
			fflush(GameLog); //Force it to write.
			fclose(GameLog); //Close the log file.
		}
	}

	else if(GameState == Level && gameover != true)
	{
		vector<int>::iterator iterator2; //Used for navigating the int array that stores the indexes of all the tiles that are to be drawn.
		int counter = 0; //Used in the for loop below...

		try
		{
			for(iterator2 = Active_Map.begin(); iterator2 < Active_Map.end(); iterator2++, counter++) //Loop through Active_Map.
			{
				Map[Active_Map[counter]].update(); //Update all the tiles it holds.
			}
		}
		catch(...)
		{
			cerr << "Caught exception when updating Active_Map.\n";
			out_string << "Caught exception when updating Active_Map.\n";
		}
		counter = 0;
		if(screen_needs_updating == false)
		{
			for(iterator2 = Draw_Map.begin(); iterator2 < Draw_Map.end(); iterator2++, counter++) //Loop through unit_type_list
			{
				Map[Draw_Map[counter]].draw_sprite(); //Draw all the tiles that need drawing.
			}
		}

		if(keystates[SDLK_a])
		{
			PCamera->set_pos(PCamera->get_wx() - camera_move_speed, PCamera->get_wy());
			std::cout << "\nCamera world x = " << PCamera->get_wx() << std::endl;
			out_string << "\nCamera world x = " << PCamera->get_wx() << "\n";
			std::cout << "\nCamera world y = " << PCamera->get_wy() << std::endl;
			out_string << "\nCamera world y = " << PCamera->get_wy() << "\n";

			//Now add all the tiles that have come into the camera's view, and remove the old ones.
			int layer_offset = (num_row_objects * num_col_objects * PCamera->layer); //Assign the layer offset.
			int current_tile = layer_offset; //The current tile it's working on.
			int num_rows_done = 0; //The number of rows it's calculated.

			bool done = false; //Is it done calculating the new Draw_Map?

			/* ----Calculate the starting tile's ID.---- */ //TODO: Oops! Need to take y into consideration!
			int start_id = 0; //The ID of the starting tile.
			int camera_wx = 0;
			int camera_wy = 0;

			if(PCamera->wx >= 0 && PCamera->wx <= num_row_objects * 32)
			{
				camera_wx = PCamera->wx; //Since the wx of the camera is positive, copy it over.
				cout << "Camera is in bounds wx-wise.\n";
			}

			if(PCamera->wy >= 0 && PCamera->wy <= num_col_objects * 32)
			{
				camera_wy = PCamera->wy; //Since the wy of the camera is positive, copy it over.
				cout << "Camera is in bounds wy-wise.\n";
			}

			start_id = (((((camera_wx) / 32) + ((camera_wy) / 32)) + ((num_col_objects - 1)* (((camera_wy) / 32)) ) )) + layer_offset; //Grab the ID of the topleftmost visible tile.
			cout << "Start_id = " << start_id << "\n"; //Debugging output.
			/* ------------------------------------ */

			Draw_Map.clear(); //Empty Draw_Map.

			while(!done)
			{
				if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wx() + Map[current_tile].get_width() >= PCamera->wx && Map[current_tile].get_wx() <= (PCamera->wx + SCREEN_WIDTH) && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //If the tile is onscreen...
				{
					Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
					current_tile++;
				}
				else //Oh dear, it's not onscreen. Find out more.
				{
					num_rows_done++; //It finished a row. So increment this.
					current_tile = start_id + (num_rows_done * num_row_objects); //Move to the leftmost visible tile of the next row.
					if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //Try again...
					{
						//Ok, it was simply the end of the row.
						Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
						current_tile++;
					}
					else
					{
						done = true; //No use going on. No more tiles will be onscreen from here on out.
					}
				}
			}
		}

		if(keystates[SDLK_d])
		{
			PCamera->set_pos(PCamera->get_wx() + camera_move_speed, PCamera->get_wy());
			std::cout << "\nCamera world x = " << PCamera->get_wx() << std::endl;
			out_string << "\nCamera world x = " << PCamera->get_wx() << "\n";
			std::cout << "\nCamera world y = " << PCamera->get_wy() << std::endl;
			out_string << "\nCamera world y = " << PCamera->get_wy() << "\n";

			//Now add all the tiles that have come into the camera's view, and remove the old ones.
			int layer_offset = (num_row_objects * num_col_objects * PCamera->layer); //Assign the layer offset.
			int current_tile = layer_offset; //The current tile it's working on.
			int num_rows_done = 0; //The number of rows it's calculated.

			bool done = false; //Is it done calculating the new Draw_Map?

			/* ----Calculate the starting tile's ID.---- */ //TODO: Oops! Need to take y into consideration!
			int start_id = 0; //The ID of the starting tile.
			int camera_wx = 0;
			int camera_wy = 0;

			if(PCamera->wx >= 0 && PCamera->wx <= num_row_objects * 32)
			{
				camera_wx = PCamera->wx; //Since the wx of the camera is positive, copy it over.
				cout << "Camera is in bounds wx-wise.\n";
			}

			if(PCamera->wy >= 0 && PCamera->wy <= num_col_objects * 32)
			{
				camera_wy = PCamera->wy; //Since the wy of the camera is positive, copy it over.
				cout << "Camera is in bounds wy-wise.\n";
			}

			start_id = (((((camera_wx) / 32) + ((camera_wy) / 32)) + ((num_col_objects - 1)* (((camera_wy) / 32)) ) )) + layer_offset; //Grab the ID of the topleftmost visible tile.
			cout << "Start_id = " << start_id << "\n"; //Debugging output.
			/* ------------------------------------ */

			Draw_Map.clear(); //Empty Draw_Map.

			while(!done)
			{
				if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wx() + Map[current_tile].get_width() >= PCamera->wx && Map[current_tile].get_wx() <= (PCamera->wx + SCREEN_WIDTH) && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //If the tile is onscreen...
				{
					Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
					current_tile++;
				}
				else //Oh dear, it's not onscreen. Find out more.
				{
					num_rows_done++; //It finished a row. So increment this.
					current_tile = start_id + (num_rows_done * num_row_objects); //Move to the leftmost visible tile of the next row.
					if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //Try again...
					{
						//Ok, it was simply the end of the row.
						Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
						current_tile++;
					}
					else
					{
						done = true; //No use going on. No more tiles will be onscreen from here on out.
					}
				}
			}
		}

		if(keystates[SDLK_w])
		{
			PCamera->set_pos(PCamera->get_wx(), PCamera->get_wy() - camera_move_speed);
			std::cout << "\nCamera world x = " << PCamera->get_wx() << std::endl;
			out_string << "\nCamera world x = " << PCamera->get_wx() << "\n";
			std::cout << "\nCamera world y = " << PCamera->get_wy() << std::endl;
			out_string << "\nCamera world y = " << PCamera->get_wy() << "\n";

			//Now add all the tiles that have come into the camera's view, and remove the old ones.
			int layer_offset = (num_row_objects * num_col_objects * PCamera->layer); //Assign the layer offset.
			int current_tile = layer_offset; //The current tile it's working on.
			int num_rows_done = 0; //The number of rows it's calculated.

			bool done = false; //Is it done calculating the new Draw_Map?

			/* ----Calculate the starting tile's ID.---- */ //TODO: Oops! Need to take y into consideration!
			int start_id = 0; //The ID of the starting tile.
			int camera_wx = 0;
			int camera_wy = 0;

			if(PCamera->wx >= 0 && PCamera->wx <= num_row_objects * 32)
			{
				camera_wx = PCamera->wx; //Since the wx of the camera is positive, copy it over.
				cout << "Camera is in bounds wx-wise.\n";
			}

			if(PCamera->wy >= 0 && PCamera->wy <= num_col_objects * 32)
			{
				camera_wy = PCamera->wy; //Since the wy of the camera is positive, copy it over.
				cout << "Camera is in bounds wy-wise.\n";
			}

			start_id = (((((camera_wx) / 32) + ((camera_wy) / 32)) + ((num_col_objects - 1)* (((camera_wy) / 32)) ) )) + layer_offset; //Grab the ID of the topleftmost visible tile.
			cout << "Start_id = " << start_id << "\n"; //Debugging output.
			/* ------------------------------------ */

			Draw_Map.clear(); //Empty Draw_Map.

			while(!done)
			{
				if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wx() + Map[current_tile].get_width() >= PCamera->wx && Map[current_tile].get_wx() <= (PCamera->wx + SCREEN_WIDTH) && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //If the tile is onscreen...
				{
					Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
					current_tile++;
				}
				else //Oh dear, it's not onscreen. Find out more.
				{
					num_rows_done++; //It finished a row. So increment this.
					current_tile = start_id + (num_rows_done * num_row_objects); //Move to the leftmost visible tile of the next row.
					if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //Try again...
					{
						//Ok, it was simply the end of the row.
						Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
						current_tile++;
					}
					else
					{
						done = true; //No use going on. No more tiles will be onscreen from here on out.
					}
				}
			}
		}

		if(keystates[SDLK_s])
		{
			PCamera->set_pos(PCamera->get_wx(), PCamera->get_wy() + camera_move_speed);
			std::cout << "\nCamera world x = " << PCamera->get_wx() << std::endl;
			out_string << "\nCamera world x = " << PCamera->get_wx() << "\n";
			std::cout << "\nCamera world y = " << PCamera->get_wy() << std::endl;
			out_string << "\nCamera world y = " << PCamera->get_wy() << "\n";

			//Now add all the tiles that have come into the camera's view, and remove the old ones.
			int layer_offset = (num_row_objects * num_col_objects * PCamera->layer); //Assign the layer offset.
			int current_tile = layer_offset; //The current tile it's working on.
			int num_rows_done = 0; //The number of rows it's calculated.

			bool done = false; //Is it done calculating the new Draw_Map?

			/* ----Calculate the starting tile's ID.---- */ //TODO: Oops! Need to take y into consideration!
			int start_id = 0; //The ID of the starting tile.
			int camera_wx = 0;
			int camera_wy = 0;

			if(PCamera->wx >= 0 && PCamera->wx <= num_row_objects * 32)
			{
				camera_wx = PCamera->wx; //Since the wx of the camera is positive, copy it over.
				cout << "Camera is in bounds wx-wise.\n";
			}

			if(PCamera->wy >= 0 && PCamera->wy <= num_col_objects * 32)
			{
				camera_wy = PCamera->wy; //Since the wy of the camera is positive, copy it over.
				cout << "Camera is in bounds wy-wise.\n";
			}

			start_id = (((((camera_wx) / 32) + ((camera_wy) / 32)) + ((num_col_objects - 1)* (((camera_wy) / 32)) ) )) + layer_offset; //Grab the ID of the topleftmost visible tile.
			cout << "Start_id = " << start_id << "\n"; //Debugging output.
			/* ------------------------------------ */

			Draw_Map.clear(); //Empty Draw_Map.

			while(!done)
			{
				if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wx() + Map[current_tile].get_width() >= PCamera->wx && Map[current_tile].get_wx() <= (PCamera->wx + SCREEN_WIDTH) && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //If the tile is onscreen...
				{
					Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
					current_tile++;
				}
				else //Oh dear, it's not onscreen. Find out more.
				{
					num_rows_done++; //It finished a row. So increment this.
					current_tile = start_id + (num_rows_done * num_row_objects); //Move to the leftmost visible tile of the next row.
					if(Map[current_tile].layer == PCamera->layer && Map[current_tile].get_wy() + Map[current_tile].get_height() >= PCamera->wy && Map[current_tile].get_wy() <= (PCamera->wy + SCREEN_HEIGHT)) //Try again...
					{
						//Ok, it was simply the end of the row.
						Draw_Map.push_back(current_tile); //Add the ID of this tile to the Draw_Map array. (Might it have been better to say vector? But, after all, vectors are really arays in the end...
						current_tile++;
					}
					else
					{
						done = true; //No use going on. No more tiles will be onscreen from here on out.
					}
				}
			}
		}
	}

	Interface.update();


	try
	{
		fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog); //Write the contents of out_string to the gamelog file.
		fflush(GameLog); //Force the file changes to be written.
		out_string.str(""); //Reset out_string
	}
	catch(...)
	{
		cerr << "Failed to write to gamelog!\n";
	}

	if(screen_needs_updating == false)
	{
		//cout << "Setting screen to be updated\n";
		screen_needs_updating = true;
	}

	return 0;
}
