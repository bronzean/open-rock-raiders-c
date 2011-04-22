/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the game object class stuff header file.
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
	type = 0;
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
	job_state = "idle";
	construct_rate = 1;
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
	type = ID;
	carrying_message_sprite = TTF_RenderText_Solid(font1, carrying_message_string.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
	select_wall_to_mine_spr = TTF_RenderText_Solid(font1, select_wall_to_mine_str.c_str(), c_white); //Render the message displayed when the unit enters mining mode.
	mining_message_spr = TTF_RenderText_Solid(font2, mining_message_str.c_str(), c_green);
	select_object_to_pick_up_spr = TTF_RenderText_Solid(font1, select_object_to_pick_up_str.c_str(), c_white);
	chopping_message_spr = TTF_RenderText_Solid(font2, chopping_message_str.c_str(), c_green);
	select_tree_to_chop_spr = TTF_RenderText_Solid(font1, select_tree_to_chop_str.c_str(), c_white);
	shovelling_message_spr = TTF_RenderText_Solid(font2, shovelling_message_str.c_str(), c_green);
	select_rubble_to_shovel_spr = TTF_RenderText_Solid(font1, select_rubble_to_shovel_str.c_str(), c_white);
}

void bClassUnit::draw_sprite() //Draw the unit's sprite.
{
	if(screen_needs_updating == false)
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
				cout << "Unit job state: " << job_state << "\n";
			}
		}
		if(selected || player) //If the unit is selected...Or it is th player's unit...
		{
			if(tool_list.size() != 0) //If the unit's tool list size is not equal to 0.
			{
				draw_inventory(); //Let the player know what tools this guy is carrying.
			}
		}
	}
}

std::string bClassUnit::update()
{
	update_return = ""; //The variable it returns.

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

	if(job_state == "idle")
	{
		check_job(); //Since the unit is idling, might as well give it something to do.
	}
	else if(job_state == "constructing")
	{
		if(!move) //If the unit has reached the construction site...
		{
			Draw_Message_Handler.add_message(wx + 32, wy, PCamera->layer, TTF_RenderText_Solid(font1, "Bob the builder!", c_green), 0); //Draw the "I'm bob the builder!" message.

			my_job->construction_health -= construct_rate;

			if(my_job->construction_health <= 0)
			{
				cout << "Done building!\n";

				int i2 = 0;
				vector<job>::iterator iterator2;

				bool done = false;

				while(!done)
				{
					if(i2 >= Job_Que.jobs.size())
					{
						cout << "FATAL: ERROR CODE 2: Failed to remove job from job que.\n";
						out_string << "FATAL: ERROR CODE 2: Failed to remove job from job que.\n";
						throw;
					}

					if(&Job_Que.jobs[i2] == my_job)
					{
						cout << "Done constructing!\n";
						out_string << "Done constructing!\n";

						if(my_job->construction_type == "wall")
						{
							my_job->tasked_tile->construct_construction(c_wall); //Transform specified tile into a wall.
						}

						Job_Que.jobs.erase(Job_Que.jobs.begin() + i2); //Remove this job from the job que.
						done = true;
					}

					i2++;
					iterator2++;
				}

				my_job = NULL;

				job_state = "idle";
			}
		}
		else //The unit hasn't yet reached the destination.
		{
			Draw_Message_Handler.add_message(wx + 32, wy, PCamera->layer, TTF_RenderText_Solid(font1, "Here I come my aunt cinnamon!", c_green), 0); //Draw the "I'm bob the builder!" message.
		}
	}

	if(allow_deselect) //If the unit is allowed to be deselected...TODO: If shift or some other key is pressed, make it so that allow_deselect will equal false.
	{
		select(); //Check if the unit has selected/deselected it.
	}

	if(!paused) //If the game is not paused.
	{
	}

	return update_return; //Return. update_return stores various information for the calling function to process.
}

void bClassUnit::set_sprite(std::string sprite_name) //Obsolete?
{
	if(color_key)
	{
		sprite = img_load2("data/unit/" + name + "/resource/" + name + spr_extend);
		sprite_select = img_load2("data/unit/" + name + "/resource/select_" + name + spr_extend);
	}
	else
	{
		sprite = img_load3("data/unit/" + name + "/resource/" + name + spr_extend);
		sprite_select = img_load3("data/unit/" + name + "/resource/select_" + name + spr_extend);
	}
	if(&sprite == NULL)
	{
		std::cout << "\n" << name << "_object.sprite == NULL\n";
	}
	width = sprite->w;
	height = sprite->h;
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
			if(selected == false) //If the unit is not selected allready.
			{
				std::cout << "\nSelected " << name << "\n"; //Let the user know this unit was selected.
			}
			selected = true; //Let's the game know this unit has been selected.
		}
		else //Ok, the user did not click on this unit.
		{
			if(selected == true) //If the unit is selected.
			{
				std::cout << "\nDeselected " << name << "\n"; //Let the user know the unit has been deselected.
				mining_mode = false; //No use to keep mining mode on anymore since it's not even selected anymore.
				shovel_mode = false; //No use to keep shovelling mode on anymore since it's not even selected anymore.
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
