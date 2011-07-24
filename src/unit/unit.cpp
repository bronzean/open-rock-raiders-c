/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the game object class stuff header file.
#include "../engine/Interface.hpp"
using namespace std;

/* --------------------------------------------------------------
 * Everything related to the unit base class is defined here.
 * ----------------------------------------------------------- */

bClassUnit::bClassUnit() //Constructor. Initializes an empty unit.
{
	name = "";
	m_health = 100;
	c_health = 100;
	wx = 0;
	wy = 0;
	wz = 0;
	layer = 0;
	sprite = NULL;
	sprite_select = NULL;
	color_key = false;
	que_num = 0;
	spr_extend = "";
	width = 0;
	height = 0;
	selected = false;
	selectable = false;
	move = false;
	move_destination = 0;
	move_destination_ramp = 0;
	move_layer_ramp = 0;
	xmove = 0;
	ymove = 0;
	calculate_need_ramp = false;
	move_frame = 0;
	draw_frame = 0;
	hovering = false;
	hover_duration = 0;
	carrying_message_string = "Inventory: ";
	carrying_message_sprite = NULL;
	carrying_resource = false;
	mine_on_reach_goal = false;
	mine_tile_id = 0;
	mining_mode = false;
	select_wall_to_mine_str = "Select the wall you want to mine. If ya dun know how, READ THE MANUAL."; //This message is displayed when the unit enters mining mode.
	select_wall_to_mine_spr = NULL;
	mining_message_str = "Whee, mining!"; //This message is displayed while the unit is mining.
	mining_message_spr = NULL;
	mining = false;
	allow_move = true;
	frames_since_last_move = 0;
	move_speed = 0;
	type_id = 0;
	need_path = false;
	allow_deselect = true;
	pick_up_on_reach_goal = false;
	pick_up_object_type = -1;
	pick_up_mode = false;
	pick_up_stage = 0;
	status = "";
	ai_pick_up_ore = true; //TODO: Make this be set in the config files or something?
	select_object_to_pick_up_str = "Select an object to pick up. If ya dun know how, READ THE MANUAL.";
	select_object_to_pick_up_spr = NULL;
	player = false;
	chopping_message_str = "Die tree!"; //This message is displayed while the unit is chopping.
	chopping_message_spr = NULL;
	chop_on_reach_goal = false;
	chopping = false;
	chop_mode = false;
	select_tree_to_chop_str = "Select a tree to kill. If ya dun know how, READ THE MANUAL.";
	select_tree_to_chop_spr = NULL;
	shovel_on_reach_goal = false;
	shovelling = false;
	shovel_mode = false;
	select_rubble_to_shovel_str = "Select some rubble to shovel. If ya dun know how, READ THE MANUAL.";
	select_rubble_to_shovel_spr = NULL;
	shovelling_message_str = "I'mma shovel some rubble!";
	shovelling_message_spr = NULL;
	animation_playing = false;
	job_state = "idling";
	construct_rate = 1;
	constructing_message_str = "Bob the builder!";
	constructing_message_spr = NULL;
	construct_walking_message_str = "Here I come my aunt cinnamon!";
	construct_walking_message_spr = NULL;
	drilling_animation_left_entry = 0;
	drilling_animation_left = false;
	construction_repositioning = 0;

	wall_popup_menu = NULL;
	rubble_popup_menu = NULL;
	ground_popup_menu = NULL;

	my_job = NULL;

	close_door = false;
	closing_door = false;
	close_door_tile = NULL;

	can_mine_wall = false;

	can_shovel_rubble = false;

	//TODO: Remove the need of this being here. Only the base unit should have this, and then every other unit should 'inherit' it.
	carrying_message_sprite = TTF_RenderText_Solid(font1, carrying_message_string.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
	select_wall_to_mine_spr = TTF_RenderText_Solid(font1, select_wall_to_mine_str.c_str(), c_white); //Render the message displayed when the unit enters mining mode.
	mining_message_spr = TTF_RenderText_Solid(font2, mining_message_str.c_str(), c_green);
	select_object_to_pick_up_spr = TTF_RenderText_Solid(font1, select_object_to_pick_up_str.c_str(), c_white);
	chopping_message_spr = TTF_RenderText_Solid(font2, chopping_message_str.c_str(), c_green);
	select_tree_to_chop_spr = TTF_RenderText_Solid(font1, select_tree_to_chop_str.c_str(), c_white);
	shovelling_message_spr = TTF_RenderText_Solid(font2, shovelling_message_str.c_str(), c_green);
	select_rubble_to_shovel_spr = TTF_RenderText_Solid(font1, select_rubble_to_shovel_str.c_str(), c_white);
	constructing_message_spr = TTF_RenderText_Solid(font1, constructing_message_str.c_str(), c_green);
	construct_walking_message_spr = TTF_RenderText_Solid(font1, construct_walking_message_str.c_str(), c_green);
}

//Initialize a new unit type.
void bClassUnit::init(int ID, SDL_Surface *SPRITE, std::string NAME, SDL_Surface *SPRITE_SELECT, bool SELECTABLE, int MOVE_SPEED, int MAX_HEALTH)
{
	name = NAME;
	m_health = MAX_HEALTH;
	sprite = SPRITE;
	sprite_select = SPRITE_SELECT;
	width = SPRITE->w;
	height = SPRITE->h;
	selectable = SELECTABLE;
	move_speed = MOVE_SPEED;
	type_id = ID;
	carrying_message_sprite = TTF_RenderText_Solid(font1, carrying_message_string.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
	select_wall_to_mine_spr = TTF_RenderText_Solid(font1, select_wall_to_mine_str.c_str(), c_white); //Render the message displayed when the unit enters mining mode.
	mining_message_spr = TTF_RenderText_Solid(font2, mining_message_str.c_str(), c_green);
	select_object_to_pick_up_spr = TTF_RenderText_Solid(font1, select_object_to_pick_up_str.c_str(), c_white);
	chopping_message_spr = TTF_RenderText_Solid(font2, chopping_message_str.c_str(), c_green);
	select_tree_to_chop_spr = TTF_RenderText_Solid(font1, select_tree_to_chop_str.c_str(), c_white);
	shovelling_message_spr = TTF_RenderText_Solid(font2, shovelling_message_str.c_str(), c_green);
	select_rubble_to_shovel_spr = TTF_RenderText_Solid(font1, select_rubble_to_shovel_str.c_str(), c_white);
	constructing_message_spr = TTF_RenderText_Solid(font1, constructing_message_str.c_str(), c_green);
	construct_walking_message_spr = TTF_RenderText_Solid(font1, construct_walking_message_str.c_str(), c_green);

	cout << "Initialising new unit.\n"; //Debugging output.
}

void bClassUnit::draw_sprite() //Draw the unit's sprite.
{
	if(allow_draw)
	{
		if(wx + width >= PCamera->wx && wx <= (PCamera->wx + SCREEN_WIDTH) && wy + height >= PCamera->wy && wy <= (PCamera->wy + SCREEN_HEIGHT) && layer == PCamera->layer) //If the sprite is onscreen...
		{
			if(selected == false) //If the unit is not selected...
			{
				draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite, screen); //Draw the 'normal' sprite.
			}
			else //If it is selected...
			{
				draw(wx - (PCamera->wx), wy - (PCamera->wy), sprite_select, screen); //Draw the selected sprite...
				//cout << "Unit job state: " << job_state << "\n";
			}
		}
		if(selected || player) //If the unit is selected...Or it is th player's unit...
		{
			if(tool_list.size() != 0) //If the unit's tool list size is not equal to 0.
			{
				draw_inventory(); //Let the player know what tools this guy is carrying.
			}

			cout << "Job state: " << job_state << "\n";
		}
	}
}

std::string bClassUnit::update()
{
	update_return = ""; //The variable it returns.

	if(allow_deselect && allow_unit_selection) //If the unit is allowed to be deselected...TODO: If shift or some other key is pressed, make it so that allow_deselect will equal false.
	{
		select(); //Check if the unit has selected/deselected it.
	}

	//Check how many frames have passed since last move.
	//Ff the number frames >= the move speed, then allow movement.
	if(allow_move == false) //If the unit is not allowed to move...
	{
		if(frames_since_last_move >= move_speed) //If the number of frames that have passed >= the move speed...
		{
			allow_move = true; //Allow movement again.
			frames_since_last_move = 0; //Reset frames_since_last_move.
		}
		frames_since_last_move++; //Increment the frames that have passed since the last move.
	}

	if(closing_door)
	{
		if(close_door_tile->has_construction) //Check if the tile has a construction, and if the construction is a door, check if its open.
		{
			if(close_door_tile->local_construction->door) //Check if that tile even has a door.
			{
				if(close_door_tile->local_construction->construction_open) //Check if the door is open.
				{
					close_door_tile->local_construction->close_thyself(false); //Close the door!
				}
				else //Door is open.
				{
					cout << "Done closing door.\n"; //Debugging output.

					cancel_current_activity(); //Wrap things up.
				}
			}
		}
	}

	if(!server)
	{
		if(mining_mode) //If the unit is awaiting the user to tell it which wall to mine.
		{
			//Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, select_wall_to_mine_spr, 1); //Draw the "Whee, mining!" message.
			Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, select_wall_to_mine_spr, 1, false);
			check_mine_command(); //Check if the player is ordering this unit to mine walls.

			cout << "Mining mode.\n";
		}

		if(!mining_mode) //So, it isn't mining mode...
		{
			if(keystates[SDLK_4] && selected == true) //If '4' was pressed
			{
				bool found = false; //Did the game find a drill in the player's inventory?

				for(unsigned int i = 0; i < tool_list.size(); i++) //Find out if the unit is carrying a drill.
				{
					if(tool_list[i].can_drill_wall == true) //If the the tool at index i in this tile's tool_list is able to drill walls...

					{
						found = true; //Let's the game know it found a drill in the unit's inventory.
					}
				}

				if(found == true) //If it found a drill.
				{				
					mining_mode = true; //Let the game know that the player is going to mine a wall.
					allow_deselect = false; //Don't allow the player to deselect this unit.
					job_state = "mining";
				}
				else //Didn't find a drill
				{
					cout << "You need a drill to mine walls!\n"; //Debugging output.
				}
			}
		}

		if(!pick_up_mode) //Here the game checks if the player is ordering this unit to get out its axe.
		{
			if(keystates[SDLK_g] && selected == true) //If the key 'g' was pressed.
			{
				allow_deselect = false; //Make sure the unit is not allowed to be deselected...

				pick_up_mode = true; //Let the game know the unit is waiting for the player to specify what it will pick up.
				job_state = "picking_up";
			}
		}
		else //Ok, so pick up mode equals true.
		{
			draw(0, 0, select_object_to_pick_up_spr, screen); //Draw message "Select an object to pick up." TODO: Make this use messages...
			check_pick_up_command(); //Check if the player is ordering the unit to pick up an object.
		}

		if(!chop_mode) //So, is chop mode equal to false?
		{
			if(keystates[SDLK_c]) //Check if the 'c' key was pressed.
			{
				if(selected == true || player == true) //If the unit is selected or it is the player...
				{

					bool found = false; //Did the game find an axe or something in the player's inventory?

					for(unsigned int i = 0; i < tool_list.size(); i++) //Find out if the unit is carrying a tool that can chop trees.
					{
						if(tool_list[i].can_chop_tree == true) //If the tool at index i of this tile's tool list is able to chop trees...
						{
							found = true; //Let's the game know it found a tool that can chop trees in the unit's inventory.
						}
					}

					if(found == true) //If it found a tool that can chop trees...
					{				
						chop_mode = true; //Let the game know that the player is going to chop a tree.
						allow_deselect = false; //Make sure the unit can't be unselected...
						job_state = "chopping";
					}
					else //Didn't find an axe.
					{
						cout << "You need a tool that can chop trees!\n"; //Debugging output.
					}
				}
			}
		}
		else //Ok, this means that the game is waiting for the user to tell the unit which tree to chop.
		{
			draw(0, 0, select_tree_to_chop_spr, screen); //Draw message "Select an object to pick up." TODO: Make this use messages...
		}

		if(!shovel_mode) //If the user hasn't allready given the unit a shovel order...
		{
			if(keystates[SDLK_r] && selected == true) //Check if the 'r' key was pressed.
			{
				bool found = false; //Did the game find a shovel in the player's inventory?

				for(unsigned int i = 0; i < tool_list.size(); i++) //Find out if the unit is carrying a shovel.
				{
					if(tool_list[i].can_clear_rubble == true) //If the tool at index i of this unit's tool list is able to clear rubble...
					{
						found = true; //Let's the game know it found a shovel in the unit's inventory.
					}
				}

				if(found == true) //If it found a shovel.
				{				
					shovel_mode = true; //Let the game know that the player is going to shovel a wall.
					allow_deselect = false; //Make sure the unit will not be deselected...
					job_state = "shoveling";
				}
				else //Didn't find a shovel.
				{
					cout << "You need a shovel to clear rubble!\n"; //Let the user know the unit needs a shovel to shovel rubble.
				}
			}
		}
		else //So, a shovel command has allready been issued.
		{
			draw(0, 0, select_rubble_to_shovel_spr, screen); //Draw the "select rubble to shovel" message.
			check_shovel_command(); //Check if the player is ordering the unit to shovel rubble.
		}

		if(active_popup_menu)
		{
			if(wall_popup_menu != NULL) //Make sure that wall_popup_menu even exists.
			{
				if(!wall_popup_menu->fields.empty()) //Make sure that wall_popup_menu is not empty.
				{
					wall_popup_menu_update(); //Update the wall_popup_menu.
				}
			}

			if(rubble_popup_menu != NULL) //Make sure that rubble_popup_menu even exists.
			{
				if(!rubble_popup_menu->fields.empty()) //Make sure that rubble_popup_menu is not empty.
				{
					rubble_popup_menu_update(); //Update the rubble_popup_menu.
				}
			}

			if(ground_popup_menu != NULL) //Make sure that ground_popup_menu even exists.
			{
				if(!ground_popup_menu->fields.empty()) //Make sure that ground_popup_menu is not empty.
				{
					ground_popup_menu_update(); //Update the ground_popup_menu.
				}
			}
		}
	}

	if(job_state == "idling")
	{
		check_job(); //Since the unit is idling, might as well give it something to do.
	}
	else if(job_state == "constructing")
	{
		construct_construction(); //Build the construction!!!
	}

	if(!paused && !server) //If the game is not paused.
	{
		if(keystates[SDLK_RIGHT]) //If the user has pressed the right arrow key.
		{
			if(selected == true || player == true) //If the unit is selected or it is the player's unit.
			{
				update_return = "m_right"; //Tell the calling tile that the unit is moving to the tile to the right.
			}
		}

		if(keystates[SDLK_LEFT]) //If the user has pressed the left arrow key.
		{
			if(selected == true || player == true) //If the unit is selected or it is the player's unit.
			{

				update_return = "m_left"; //Tell the calling tile that the unit is moving to the tile to the left.
			}
		}

		if(keystates[SDLK_UP]) //If the user has pressed the up arrow key.
		{
			if(selected == true || player == true) //If the unit is selected or it is the player's unit.
			{
				update_return = "m_up"; //Tell the calling tile that the unit is moving to the tile north of it.
			}
		}

		if(keystates[SDLK_DOWN]) //If the user has pressed the down arrow key.
		{
			if(selected == true || player == true) //If the unit is selected or it is the player's unit.
			{
				update_return = "m_down"; //Tell the calling tile that the unit is moving to the tile south of it.
			}
		}
	}

	return update_return; //Return. update_return stores various information for the calling function to process.
}



void bClassUnit::set_pos(int WORLD_X, int WORLD_Y, int WORLD_Z) //Set's the unit's position.
{
	wx = WORLD_X; //Sets the unit's world x.
	wy = WORLD_Y; //Sets the unit's world y.
	wz = WORLD_Z; //Sets the unit's world z.
}

int bClassUnit::get_wx() //Returns the unit's world x.
{
	return wx;
}

int bClassUnit::get_wy() //Returns the unit's world y.
{
	return wy;
}

int bClassUnit::get_wz() //Returns the unit's world z.
{
    return wz;
}

int bClassUnit::get_width() //Returns the width of the unit.
{
	return width;
}

int bClassUnit::get_height() //Returns the height of the unit.
{
	return height;
}


void bClassUnit::select() //Checks if the player selected/deselected the unit.
{
	if(event_struct.button.button == SDL_BUTTON_LEFT && event_struct.type == SDL_MOUSEBUTTONDOWN && mining_mode == false && selectable == true && allow_deselect == true && allow_unit_selection) //If the left mouse button was pressed and this unit can be selected...
	{
		if(event_struct.button.x + PCamera->wx >= wx && event_struct.button.x + PCamera->wx <= wx + width && event_struct.button.y + PCamera->wy >= wy && event_struct.button.y + PCamera->wy <= wy + height && mining_mode != true && shovel_mode != true /*&& leftclick_tile_id != -1*/) //Checks if the mouse clicked on this unit.
		{
			if(!unit_selected)
			{
				if(selected == false) //If the unit is not selected allready.
				{
					std::cout << "\nSelected " << name << "\n"; //Let the user know this unit was selected.
				}
				selected = true; //Let's the game know this unit has been selected.

				unit_selected = true; //Let the game know a unit is selected.
				selected_unit = this; //Let the game know which unit is selected.
			}
		}
		else //Ok, the user did not click on this unit.
		{
			if(selected == true) //If the unit is selected.
			{
				std::cout << "\nDeselected " << name << "\n"; //Let the user know the unit has been deselected.
				mining_mode = false; //No use to keep mining mode on anymore since it's not even selected anymore.
				shovel_mode = false; //No use to keep shovelling mode on anymore since it's not even selected anymore. 
				unit_selected = false; //Let the game know no unit is currently selected.
				selected_unit = NULL; //Reset this.
			}

			selected = false; //Let's the game know this unit is not selected.
		}
	}
}

void bClassUnit::draw_inventory() //Lets the player know what tools this guy is carrying.
{
	int counter = 0; //Used in the for loop below...
	int draw_x = carrying_message_sprite->w + 10; //The x of where to draw the next tool's icon...
	int draw_y = SCREEN_HEIGHT; //The y of where to draw the next tool's icon...

	draw(0, (SCREEN_HEIGHT - carrying_message_sprite->h), carrying_message_sprite, screen); //Draw the carrying message onto the screen.

	for(iterator = tool_list.begin(); iterator < tool_list.end(); iterator++, counter++) //Loop through the tool list
	{
		draw_y = SCREEN_HEIGHT - tool_list[counter].icon_sprite->h; //Assign draw_y to be the screen's y resolution minus the tool's icon's height.

		draw(draw_x, draw_y, tool_list[counter].icon_sprite, screen); //Now draw the tool's icon's sprite.

		draw_x += tool_list[counter].icon_sprite->w; //Add the icon's width onto draw x.
		draw_x += 10; //Add 10 onto draw x.
	}



	//Now we go draw the ore he's carrying.
	counter = 0; //Reset counter...

	for(iterator2 = ore_list.begin();  iterator2 < ore_list.end(); iterator2++, counter++) //Loop through the ore list.
	{
		draw_y = SCREEN_HEIGHT - ore_list[counter].sprite->h;  //Assign draw_y to be the screen's y resolution minus the ore's sprite.

		draw(draw_x, draw_y, ore_list[counter].sprite, screen); //Now draw the ore's sprite.

		draw_x += ore_list[counter].sprite->w; //Add the sprite's width onto draw x.
		draw_x += 10; //Add 10 onto draw x.
	}

	//Now we go draw the energy crystal he's carrying.
	counter = 0; //Reset counter...

	for(iterator3 = energy_crystal_list.begin();  iterator3 < energy_crystal_list.end(); iterator3++, counter++) //Loop through the energy crystal list.
	{
		draw_y = SCREEN_HEIGHT - energy_crystal_list[counter].sprite->h;  //Assign draw_y to be the screen's y resolution minus the energy crystal's sprite.

		draw(draw_x, draw_y, energy_crystal_list[counter].sprite, screen); //Now draw the energy crystal's sprite.

		draw_x += energy_crystal_list[counter].sprite->w; //Add the sprite's width onto draw x.
		draw_x += 10; //Add 10 onto draw x.
	}
}

bClassUnit unitlist[1000];
int unitnum = 0;
