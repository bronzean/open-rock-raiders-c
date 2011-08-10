/* Copyright the ORR-C Dev Team */
#include "main.hpp"
#include "engine/EObject.hpp"
#include "engine/Interface.hpp"

//Example of getting the mouse's current position
/*
int MouseX, MouseY;//for mouse coordinates

SDL_GetMouseState(&MouseX, &MouseY);//get the coordinates of the mouse on the screen
*/

void *DrawScreen(void *param) //Draw everything.
{
	//int _GFPS = GFPS; //Copy this so that it won't be using the global one, which is subject to change, and might cause a crash...
	while(!gameover) //While the game's not over. Durr.
	{
		if(screen_needs_updating == true) //Check if screen needs to be redrawn.
		{
			//Draw_Message_Handler.draw_all();
			//std::cout << "\nNeeds updating!\n";
			if(GameState != Loading) //Make sure the game isn't on the load screen (using different drawing).
			{
				//cout << "Gamestate != loading!\n";
				if(SDL_Flip(screen) == -1) //Flip the double buffers (aka draw to the screen).
				{
					//This code run only if there's an error flipping the buffers.
					std::cerr << "\nError Updating Screen\n"; //Debugging output.
					out_string << "\nError Updating Screen\n"; //Debugging output.
					fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
					fflush(GameLog);
					screen_needs_updating = false; //Reset this just cuz.
					gameover = true; //Tell the game it's all over.
					pthread_exit(NULL); //Terminate this thread.
				}
				//cout << "Updated screen!\n";
				//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
				SDL_FillRect(screen, NULL, 0x00000000);
				//cout << "Cleared screen!\n";
			}

			screen_needs_updating = false; //Reset this.
			//cout << "Screen set to not needing updating!\n";

			//cout << "Done with delay!\n";
			SDL_Delay(GFPS); //Pause the thread.
		}
	}
	pthread_exit(NULL); //We have no use for this anymore; the game is over. Terminate it.
}

int update()
{
	if(screen_needs_updating == false) //Check if the drawing thread has drawn.
	{
		//cout << "Setting screen to be updated\n";
		//screen_needs_updating = true;
		allow_draw = true; //This barialbe lets everything now it's time to draw their sprites.
	}

	/*if(num_worker_threads == 0) //If not running with threads...
	{
		if(SDL_Flip(screen) == -1)
		{
			std::cerr << "\nError Updating Screen\n";
			out_string << "\nError Updating Screen\n";
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			return 1;
		}
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
		allow_draw = false;
	}*/

	rightclick_tile_id = -1; //Reset rightclick_tile_id
	leftclick_tile_id = -1; //Reset leftclick_tile_id

	poll_events(); //Event handling.

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

	//if(keystates[SDLK_LSHIFT] || keystates [SDLK_RSHIFT])
	//{
	//	shift_modifier = true;
	//}

	if(GameState == Title && gameover != true)
	{
		if(keystates[SDLK_RETURN]) //If enter was pressed...
		{
			GameState = Loading; //Load everything.
		}

		if(screen_needs_updating == false) //Make sure it's ok to draw this.
		{
			draw(0, 0, title_screen, screen); //Draw the title screen's background.
		}
	}

	else if(GameState == Loading && gameover != true)
	{
		try
		{
			if(!load_game())
			{
				gameover = true;
				return 1;
			}
		}
		catch(...)
		{		
			std::cerr << "Failed to load everything.\n";
			out_string << "Failed to load everything.\n";
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog); //Write out_string to the log.
			fflush(GameLog); //Force it to write.
			fclose(GameLog); //Close the log file.
		}
	}

	else if(GameState == Level && gameover != true)
	{
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

		vector<int>::iterator iterator2; //Used for navigating the int array that stores the indexes of all the tiles that are to be drawn.
		int counter = 0; //Used in the for loop below...

		try
		{
			//out_string << "active map's size: " << Active_Map.size() << "\n";
			for(counter = 0; counter < Active_Map.size(); counter++) //Loop through Active_Map.
			{
				//cout << "active map's size: " << Active_Map.size() << "\n";
				//cout << "counter: " << counter << "\n";
				//cout << "Value: " << Active_Map[counter] << "\n";
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
			if(!threed_gfx)
			{
				for(iterator2 = Draw_Map.begin(); iterator2 < Draw_Map.end(); iterator2++, counter++) //Loop through unit_type_list
				{
					Map[Draw_Map[counter]].draw_sprite(); //Draw all the tiles that need drawing.
				}
			}
		}
	}

	if(construction_wall_location_select == true && server == false) //Is the user selecting the location of a wall construction?
	{
		Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, choose_wall_location_spr , 1, false); //Displays the "Choose location of wall construction" message.
	}

	if(construction_door_location_select && !server) //Is the user selecting the location of a door construction?
	{
		Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, choose_door_location_spr, 1, false); //Displays the "Choose location of door construction" message.
	}

	if(construction_teleporter1_location_select && !server) //Is the user selecting the location of a teleporter construction?
	{
		Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, choose_teleporter1_location_spr, 1, false); //Displays the "Choose location of teleporter construction" message.
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

	if(allow_draw)
	{
		//cout << "Setting screen to be updated\n";
		screen_needs_updating = true;
		allow_draw = false;
	}

	return 0;
}
