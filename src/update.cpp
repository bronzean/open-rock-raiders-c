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
		}
		SDL_Delay(GFPS); //Pause the thread.
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

        if(construction_wall_location_select && !server) //Is the user selecting the location of a wall construction?
	{
                Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, choose_wall_location_spr , 1, false); //Displays the "Choose location of wall construction" message.
	}

        if(construction_door_location_select && !server) //Is the user selecting the location of a door construction?
        {
                Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, choose_door_location_spr, 1, false); //Displays the "Choose location of door construction" message.
        }

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
                                    //I wonder if I should move code into the interface update function...
                                    if(event_struct.button.button == SDL_BUTTON_LEFT)
                                    {
                                            if(!server) //If not in server mode...
                                            {
                                                    std::cout << "Left click\n"; //Debugging output.
                                                    out_string << "Left click\n";
                                                    if(Interface.g_teleport_button.clicked()) //Check this first, so that it doesn't deselect or select anything if true is returned.
                                                    {
                                                            //Teleport code here
                                                            std::cout << "\nGlobal teleport button clicked.\n";
                                                            out_string << "\nGlobal teleport button clicked.\n";
                                                            bool found = false;
                                                            bool continue_ = true;
                                                            for(int i = 0; i < 9; i++)
                                                            {
                                                                    if(!found)
                                                                    {
                                                                            if(g_teleport_que_name[i] == "")
                                                                                    found = true;
                                                                    }
                                                                    if(found && continue_)
                                                                    {
                                                                            g_teleport_que_name[i] = "raider";
                                                                            g_teleport_que ++;
                                                                            continue_ = false;
                                                                    }
                                                            }
                                                    }
                                                    else if(Interface.construct_wall_button.clicked() && !construction_location_select /*construction_wall_location_select*/)
                                                    {
                                                            std::cout << "\nConstruct wall button clicked.\n";

                                                            Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, choose_wall_location_spr, 1, false); //Adds a message to be drawn.
                                                            allow_unit_selection = false; //Since the construct wall button was clicked, disable selection of units and whatnot.
                                                            construction_wall_location_select = true; //Let the game know the user is going to select the location for a construction.
                                                            construction_location_select = true;
                                                    }
                                                    else if(Interface.construct_door_button.clicked() && !construction_location_select)
                                                    {
                                                            std::cout << "\nConstruct door button clicked.\n";

                                                            Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, choose_door_location_spr, 1, false); //Adds a message to be drawn.
                                                            allow_unit_selection = false; //Since the construct door button was clicked, disable selection of units and whatnot.
                                                            construction_door_location_select = true;
                                                            construction_location_select = true;
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
                                                                                                    cout << "Does not have units on it, saving tile id!\n";
                                                                                                    leftclick_tile_id = i; //Save the ID of this tile only if no units are on this tile.

                                                                                                    std::cout << "\nFound the tile that the left click took place over...\n";
                                                                                                    out_string << "\nFound the tile that the left click took place over...\n";
                                                                                                    std::cout << "Position of that tile: (" << Map[leftclick_tile_id].wx << "," << Map[leftclick_tile_id].wy << "," << Map[leftclick_tile_id].layer << ") and index is: " << i << "\n";
                                                                                                    out_string << "Position of that tile: (" << Map[leftclick_tile_id].wx << "," << Map[leftclick_tile_id].wy << "," << Map[leftclick_tile_id].layer << ") and index is: " << i << "\n";
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

		if(screen_needs_updating == false)
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
                                if(!threed_gfx)
                                {
                                        for(iterator2 = Draw_Map.begin(); iterator2 < Draw_Map.end(); iterator2++, counter++) //Loop through unit_type_list
                                        {
                                                Map[Draw_Map[counter]].draw_sprite(); //Draw all the tiles that need drawing.
                                        }
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

	if(allow_draw)
	{
		//cout << "Setting screen to be updated\n";
		screen_needs_updating = true;
		allow_draw = false;
	}

	return 0;
}
