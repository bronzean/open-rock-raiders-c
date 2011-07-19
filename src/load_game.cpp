/* Copyright the ORR-C Dev Team */
#include "main.hpp"
#include "engine/EObject.hpp"
#include "engine/Interface.hpp"

/* --------------------------------------------------------------
 * Loads the level and whatnot. Also cleans up the update.cpp file a bit!
 * ----------------------------------------------------------- */

bool load_game()
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
	c_wall.init("wall", true, false, false, 0, 0, "data/construction/wall/sprite.png"); //Initialize the wall construction.
	if(c_wall.sprite == NULL)
	{
		throw 0;
	}
	//c_floor.init(); //TODO: Ya, this needs to be done...
	c_door.init("door", false, false, true, 2, 1, "data/construction/door/sprite.png");
	if(c_door.sprite == NULL)
	{
		throw 0;
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
			//cout << Map[Draw_Map[Draw_Map.size() - 1]].ID << "\n";
			//out_string << Map[Draw_Map[Draw_Map.size() - 1]].ID << "\n";
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

	if(map_folder_path == "maps/default/")
	{
		Map[74].construct_construction(c_door);
	}

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
	GameState = Level; //Done loading everything. Enter the level now.

	return true; //Success!
}
