/* Copyright the ORR-C Dev Team */
#include "main.hpp"
#include "engine/EObject.hpp"
#include "engine/Interface.hpp"

/* --------------------------------------------------------------
 * Loads the level and whatnot. Also cleans up the update.cpp file a bit!
 * ----------------------------------------------------------- */

bool load_game() //Load the game.
{
	string load_text = "";
	SDL_Surface *load_text_sprite = NULL;


	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
	//Let the user know the interface stuff is being loaded...
	load_text = "Loading Interface stuff.";
	load_text_sprite = TTF_RenderText_Solid(font1, load_text.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
	draw((SCREEN_WIDTH / 2) - (load_text_sprite->w / 2), (SCREEN_HEIGHT / 2) - (load_text_sprite->h / 2), load_text_sprite, screen);
	SDL_FreeSurface(load_text_sprite);
	if(SDL_Flip(screen) == -1)
	{
		std::cerr << "\nError Updating Screen\n";
		out_string << "\nError Updating Screen\n";
		fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
		fflush(GameLog);

		return false;
	}

	cout << "Loading and initializing popup_menu_fields.\n"; //Debugging output.
	//TODO: Load popup_menu_field types.
	if(!field_drill_wall.load_sprite("data/resource/interface/menu/fields/drill_wall.png")) //Load the drill wall popup menu field's sprite. With error checking.
	{
		cout << "Failed to load drill_wall popup_menu_field sprite.\n"; //Debugging output.
		out_string << "Failed to load drill_wall popup_menu_field sprite.\n"; //Debugging output.

		return false;
	}
	field_drill_wall.field_data = "drill wall"; //Let the game know that this is a drill wall field.

	if(!field_shovel_rubble.load_sprite("data/resource/interface/menu/fields/shovel_rubble.png")) //Load the shovel rubble popup menu field's sprite. With error checking.
	{
		cout << "Failed to load shovel_rubble popup_menu_field sprite.\n"; //Debugging output.
		out_string << "Failed to load load shovel_rubble popup_menu_field sprite.\n"; //Debugging output.

		return false;
	}
	field_shovel_rubble.field_data = "shovel rubble"; //Let the game know that this is a shovel rubble field.

	if(!field_moveto.load_sprite("data/resource/interface/menu/fields/moveto.png"))
	{
		cout << "Failed to load moveto popup_menu_field sprite.\n"; //Debugging output.
		out_string << "Failed to load moveto popup_menu_field sprite.\n"; //Debugging output.

		return false;
	}
	field_moveto.field_data = "moveto"; //Let the game know that this is a moveto field.

	if(!field_pickup_any_ore.load_sprite("data/resource/interface/menu/fields/pickup_any_ore.png"))
	{
		cout << "Failed to load pickup_any_ore popup_menu_field sprite.\n"; //Debugging output.
		out_string << "Failed to load pickup_any_ore popup_menu_field sprite.\n"; //Debugging output.

		return false;
	}
	field_pickup_any_ore.field_data = "pickup any ore"; //Let the game know that this is a pickup any ore field.

	if(!field_construct_wall.load_sprite("data/resource/interface/menu/fields/construct_wall.png"))
	{
		cout << "Failed to load construct_wall popup_menu_field sprite.\n"; //Debugging output.
		out_string << "Failed to load construct_wall popup_menu_field sprite.\n"; //Debugging output.

		return false;
	}
	field_construct_wall.field_data = "construct wall"; //Let the game know that this is a construct wall field.

	if(!field_construct_door.load_sprite("data/resource/interface/menu/fields/construct_door.png"))
	{
		cout << "Failed to load construct_door popup_menu_field sprite.\n"; //Debugging output.
		out_string << "Failed to load construct_door popup_menu_field sprite.\n"; //Debugging output.

		return false;
	}
	field_construct_door.field_data = "construct door"; //Let the game know that this is a construct door field.

	if(!field_open_door.load_sprite("data/resource/interface/menu/fields/open_door.png"))
	{
		cout << "Failed to load open_door popup_menu_field sprite.\n"; //Debugging output.
		out_string << "Failed to open_door popup_menu_field sprite.\n"; //Debugging output.

		return false;
	}
	field_open_door.field_data = "open door"; //Let the game know that this is a close door field.

	if(!field_close_door.load_sprite("data/resource/interface/menu/fields/close_door.png"))
	{
		cout << "Failed to load close_door popup_menu_field sprite.\n"; //Debugging output.
		out_string << "Failed to close_door popup_menu_field sprite.\n"; //Debugging output.

		return false;
	}
	field_close_door.field_data = "close door"; //Let the game know that this is a close door field.

	cout << "\n\n";
	out_string << "\n\n";
	fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
	fflush(GameLog);
	out_string.str(""); //Reset out_string


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
		return false;
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
		return false;
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
		return false;
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
		return false;
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
		return false;
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
		return false;
	}

	//Here all the constructions are initlialized and resources loaded.
	c_wall.init("wall", true, false, false, false, 0, 0, "data/construction/wall/sprite.png"); //Initialize the wall construction.
	if(c_wall.sprite == NULL)
	{
		return false;
	}
	//c_floor.init(); //TODO: Ya, this needs to be done...

	c_teleporter1.init("teleporter1", false, false, false, true, 0, 2, "data/construction/teleporter1/sprite.png");
	if(c_teleporter1.sprite == NULL)
	{
		return false;
	}
	c_teleporter1.selectable = true; //This can be selected.
	img_load_safe("data/construction/teleporter1/sprite_select.png", &c_teleporter1.sprite_select);
	if(!c_teleporter1.sprite_select)
	{
		return false;
	}

	c_door.init("door", false, false, true, false, 2, 1, "data/construction/door/sprite.png");
	if(c_door.sprite == NULL)
	{
		return false;
	}
	img_load_safe("data/construction/door/sprite_open.png", &c_door.sprite_open);
	if(c_door.sprite_open == NULL)
	{
		return false;
	}
	if(!c_door.load_config("data/construction/door/"))
	{
		cout << "Failed to load door construction configuration.\n"; //Debugging output.
		out_string << "Failed to load door construction configuration.\n"; //Debugging output.
		return false; //ABORT.
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
		return false;
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
		return false;
	}
	//TODO: load whatever else needs to be loaded...
	//Interface.g_teleport_button.init(teleport_button_spr->w, teleport_button_spr->h, teleport_button_spr, no_teleport_button_spr); //Initialize the teleport button.
	fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
	fflush(GameLog);
	out_string.str(""); //Reset out_string

	if(map_folder_path == "maps/default/")
	{
		Map[26].construct_construction(c_teleporter1);
	}

	if(map_folder_path == "maps/default/")
	{
		Map[74].construct_construction(c_door);
	}

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); //Clear the screen.
	GameState = Level; //Done loading everything. Enter the level now.

	return true; //Success!
}
