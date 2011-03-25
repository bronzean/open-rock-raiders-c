/* Copright the ORR-C Dev Team */
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
	carrying_message_sprite = TTF_RenderText_Solid(font1, carrying_message_string.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
	carrying_resource = false;
	mine_on_reach_goal = false;
	mine_tile_id = 0;
	mining_mode = false;
	select_wall_to_mine_str = "Select the wall you want to mine. If ya dun know how, READ THE MANUAL."; //This message is displayed when the unit enters mining mode.
	select_wall_to_mine_spr = TTF_RenderText_Solid(font1, select_wall_to_mine_str.c_str(), c_white); //Render the message displayed when the unit enters mining mode.
	mining_message_str = "Whee, mining!"; //This message is displayed while the unit is mining.
	mining_message_spr = TTF_RenderText_Solid(font2, mining_message_str.c_str(), c_green);
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
	select_object_to_pick_up_spr = TTF_RenderText_Solid(font1, select_object_to_pick_up_str.c_str(), c_white);
	player = false;
	chopping_message_str = "Die tree!"; //This message is displayed while the unit is chopping.
	chopping_message_spr = TTF_RenderText_Solid(font2, chopping_message_str.c_str(), c_green);
	chop_on_reach_goal = false;
	chopping = false;
	chop_mode = false;
	select_tree_to_chop_str = "Select a tree to kill. If ya dun know how, READ THE MANUAL.";
	select_tree_to_chop_spr = TTF_RenderText_Solid(font1, select_tree_to_chop_str.c_str(), c_white);
	shovel_on_reach_goal = false;
	shovelling = false;
	shovel_mode = false;
	select_rubble_to_shovel_str = "Select some rubble to shovel. If ya dun know how, READ THE MANUAL.";
	select_rubble_to_shovel_spr = TTF_RenderText_Solid(font1, select_rubble_to_shovel_str.c_str(), c_white);
	shovelling_message_str = "I'mma shovel some rubble!";
	shovelling_message_spr = TTF_RenderText_Solid(font2, shovelling_message_str.c_str(), c_green);
	animation_playing = false;
}

//bClassUnit::bClassUnit(const bClassUnit &source) //Copy constructor.
//{
	/*wx = source.wx;
	wy = source.wy;
	wz = source.wz;
	layer = source.layer;
	move_speed = source.move_speed;
	m_health = source.m_health;
	c_health = source.c_health;
	sprite = source.sprite;
	sprite_select = source.sprite_select;
	width = source.width;
	height = source.height;
	selectable = source.selectable;
	selected = source.selected;
	name = source.name;
	spr_extend = source.spr_extend;
	color_key = source.color_key;
	que_num = source.que_num;
	move_destination = source.move_destination;
	move_destination_ramp = source.move_destination_ramp;
	move_layer_ramp = source.move_layer_ramp;
	move = source.move;
	calculate_need_ramp = source.calculate_need_ramp;
	xmove = source.xmove;
	ymove = source.ymove;
	move_frame = source.move_frame;
	draw_frame = source.draw_frame;
	move_path = source.move_path;
	need_path = source.need_path;
	tool_list = source.tool_list;
	hovering = source.hovering;
	hover_duration = source.hover_duration;
	carrying_message_string = source.carrying_message_string;
	carrying_message_sprite = source.carrying_message_sprite;
	ore_list = source.ore_list;
	energy_crystal_list = source.energy_crystal_list;
	carrying_resource = source.carrying_resource;

	std::vector<tool>::iterator iterator; //Used for navigating the tool list
	std::vector<ore>::iterator iterator2; //Used for navigating the ore list
	std::vector<energy_crystal>::iterator iterator3; //Used for navigating the energy crystal
	bool mining_mode; //Used in the mining code.
	int mine_tile_id; //The ID of the tile the unit needs to mine.
	bool mine_on_reach_goal; //Is the unit moving somewhere to mine a tile.
	std::string select_wall_to_mine_str; //A message that is displayed when the player wants to select a wall to mine.
	SDL_Surface *select_wall_to_mine_spr; //A message that is displayed when the player wants to select a wall to mine.
	bool mining; //Is the unit currently mining a tile? Used in drill times.
	bool allow_move; //Is the unit allowed to move?
	int frames_since_last_move; //The number of frames that have passed since the last move.
	std::string mining_message_str; //A message that is displayed while the unit is mining.
	SDL_Surface *mining_message_spr; //A message that is displayed while the unit is mining.
	int type; //The unit's type.
	bool allow_deselect; //Allow the unit to be deselected?
	bool pick_up_on_reach_goal; //Is the unit moving somewhere to pick up something?
	bool pick_up_mode; //Is the unit waiting for the player to specify what it's going to be picking up?
	int pick_up_object_type; //The type of object the unit is picking up. -1 = not picking up anything. 0 = ore. 1 = Energy Crystal. 2 = tool.
	int pick_up_stage; //Used in the check_pick_up_command function.
	std::string status; //What's it doing? IDLE = not doing anything. Check the ai related files for the rest of the status stuff.
	bool ai_pick_up_ore; //Is the unit allowed to automatically pick up ore?
	std::string select_object_to_pick_up_str; //Used in the "Select object to pick up" stuff.
	SDL_Surface *select_object_to_pick_up_spr; //Used in the "Select object to pick up" stuff.
	bool player; //Is this the player?
	std::string update_return; //Used in update functio...Tells the caller stuff.
	std::string chopping_message_str; //A message that is displayed while the unit is chopping.
	SDL_Surface *chopping_message_spr; //A message that is displayed while the unit is chopping.
	bool chop_on_reach_goal; //Is the unit going to chop down a tree?
	bool chopping; //Is the unit currently chopping a tree?
	bool chop_mode; //Is the game waiting for the player to select a tree to kill?
	std::string select_tree_to_chop_str; //Displayed when the player is selecting a tree to kill.
	SDL_Surface *select_tree_to_chop_spr; //Displayed when the player is selecting a tree to kill.
	bool shovel_on_reach_goal; //Will the unit be shovelling stuff when it reaches its goal?
	bool shovelling; //Is the unit currently shovelling something?
	bool shovel_mode; //Is the game waiting for the player to select some rubble to shovel?
	std::string select_rubble_to_shovel_str; //Displayed when the player is selecting rubble to shovel.
	SDL_Surface *select_rubble_to_shovel_spr; //Displayed when the player is selecting rubble to shovel.
	std::string shovelling_message_str; //A message that is displayed while the unit is shovelling.
	SDL_Surface *shovelling_message_spr; //A message that is displayed while the unit is shovelling.
	bool animation_playing; //Is the unit currently playing an animation?*/
//}

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
}

void bClassUnit::draw_sprite() //Draw the unit's sprite.
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

	if(mining_mode) //If the unit is awaiting the user to tell it which wall to mine.
	{
		Draw_Message_Handler.add_message(PCamera->wx, PCamera->wy, PCamera->layer, select_wall_to_mine_spr, 1); //Draw the "Whee, mining!" message.
		check_mine_command(); //Check if the player is ordering this unit to mine walls.
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

	if(allow_deselect) //If the unit is allowed to be deselected...TODO: If shift or some other key is pressed, make it so that allow_deselect will equal false.
	{
		select(); //Check if the unit has selected/deselected it.
	}

	if(!paused) //If the game is not paused.
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
	if(event_struct.button.button == SDL_BUTTON_LEFT && event_struct.type == SDL_MOUSEBUTTONDOWN && mining_mode == false && selectable == true && allow_deselect == true) //If the left mouse button was pressed and this unit can be selected...
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

bool bClassUnit::check_mine_command() //Checks if a mine command was issued.
{
	int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
	bool run = true;
	if(event_struct.button.button == SDL_BUTTON_LEFT && event_struct.type == SDL_MOUSEBUTTONDOWN)
	{
		allow_deselect = true;
		//Check if a tile was clicked
		for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++)
		{
			if(run)
			{
				//Check if the tile is the one that was clicked on.
				if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
				{
					run = false;

					std::cout << "Position of the tile to be mined: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";
					out_string << "Position of the tile to be mined: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";

					if(Map[i].wall == true)
					{
						mining_mode = false; //let the game know mining mode is off.
						move = true; //Let the game know that the unit is moving somewhere.
						move_destination = i; //Let the game know that the move destination of this unit is the tile that was just clicked on.
						mine_tile_id = i; //Let the game know what the mining target is...
						mine_on_reach_goal = true; //Tells the unit to mine the wall once it reaches its goal.
						layer_offset = (num_row_objects * num_col_objects * Map[i].layer); //Assign the layer offset.

						if(calculate_path() == false) //If it can't calculate find a path...
						{
							move_destination = (((((Map[i].wx) / 32) + ((Map[i].wy) / 32)) + ((num_row_objects - 1)* ((Map[i].wy / 32)) ) ) - 1) + layer_offset; //grab tile to the left.
							if(move_destination > 0 && move_destination < num_tiles)
							{
								if(calculate_path() == false)
								{
									move_destination = (((((Map[i].wx) / 32) + ((Map[i].wy) / 32)) + ((num_row_objects - 1)* ((Map[i].wy / 32)) ) ) + 1) + layer_offset; //It failed again. Grab the tile to the right.
									if(move_destination > 0 && move_destination < num_tiles)
									{
										if(calculate_path() == false)
										{
											move_destination = (((((Map[i].wx) / 32) + ((Map[i].wy) / 32)) + ((num_row_objects - 1)* ((Map[i].wy / 32) - 1) ) ) - 1) + layer_offset; //Oh dear, it failed yet again. Grab the tile to the north.
											if(move_destination > 0 && move_destination < num_tiles)
											{
												if(calculate_path() == false)
												{
													move_destination = (((((Map[i].wx) / 32) + ((Map[i].wy) / 32)) + ((num_col_objects - 1)* ((Map[i].wy / 32) + 1) ) ) + 1) + layer_offset; //You know the drill. Tile to the south now.
													if(move_destination > 0 && move_destination < num_tiles)
													{
														if(calculate_path() == false)
														{
															//OH COME ON. WHAT IS WRONG WITH THIS PLAYER. THEY CLICKED ON AN INACCESSIBLE TILE!
															move = false; //Tell the unit it's staying put
															move_destination = 0; //Reset the unit's move destination.
															mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
															mining = false; //Reset this so that the game knows to not mine the wall...
														}
													}
													else
													{
														move = false; //Tell the unit it's staying put
														move_destination = 0; //Reset the unit's move destination.
														mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
														mining_mode = false; //let the game know mining mode is off.
														mining = false; //Reset this so that the game knows to not mine the wall...
														cout << "Can't move to a nonexistant tile!\n";
													}
												}
											}
											else
											{
												move = false; //Tell the unit it's staying put
												move_destination = 0; //Reset the unit's move destination.
												mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
												mining_mode = false; //let the game know mining mode is off.
												mining = false; //Reset this so that the game knows to not mine the wall...
												cout << "Can't move to a nonexistant tile!\n";
											}
										}
									}
									else
									{
										move = false; //Tell the unit it's staying put
										move_destination = 0; //Reset the unit's move destination.
										mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
										mining_mode = false; //let the game know mining mode is off.
										mining = false; //Reset this so that the game knows to not mine the wall...
										cout << "Can't move to a nonexistant tile!\n";
									}
								}
							}
							else
							{
								move = false; //Tell the unit it's staying put
								move_destination = 0; //Reset the unit's move destination.
								mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
								mining_mode = false; //let the game know mining mode is off.
								mining = false; //Reset this so that the game knows to not mine the wall...
								cout << "Can't move to a nonexistant tile!\n";
							}
						}
					}
					else
					{
						move = false; //Tell the unit it's staying put
						move_destination = 0; //Reset the unit's move destination.
						mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
						mining_mode = false; //let the game know mining mode is off.
						mining = false; //Reset this so that the game knows to not mine the wall...
						cout << "Not a wall!\n";
					}
				}
			}
		}
	}
	return false;
}

bool bClassUnit::check_pick_up_command() //Checks if a pick up object command was issued.
{
	cout << "in check pick up function!\n";
	int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
	if(event_struct.button.button == SDL_BUTTON_LEFT && event_struct.type == SDL_MOUSEBUTTONDOWN && pick_up_stage == 0) //If the left mouse button was clicked and the pick up stage is 0 (Awaiting tile to be selected)
	{
		cout << "chose it!\n";
		allow_deselect = true;
		bool run = true;
		//Check if a tile was clicked
		for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++)
		{
			cout << "I: " << i << "\n";
			if(run)
			{
				//Check if the tile is the one that was clicked on.
				if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
				{
					out_string << "Found it!\n";
					run = false;

					//std::cout << "Position of the tile to be mined: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";
					//out_string << "Position of the tile to be mined: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";

					if(Map[i].wall == false) //If said tile is not a wall...
					{
						//pick_up_mode = false; //let the game know pick up mode is off.
						//move = true; //Let the game know that the unit is moving somewhere.
						//move_destination = i; //Let the game know that the move destination of this unit is the tile that was just clicked on.
						//pick_up_tile_id = i; //Let the game know what the pick up target is...
						//pick_up_on_reach_goal = true; //Tells the unit to pick up the object once it reaches its goal.
						//layer_offset = (num_row_objects * num_col_objects * Map[i].layer); //Assign the layer offset.

						/*if(calculate_path() == false) //If it can't calculate find a path...
						{
							
							//Inaccessible tile...
							move = false; //Tell the unit it's staying put
							move_destination = 0; //Reset the unit's move destination.
							pick_up_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
							picking_up = false; //Reset this so that the game knows to not mine pick up anything...
						}*/

						//TODO: Check if the tile has any objects.
						//TODO: Then check what objects are on there.
						//TODO: If more than 1, create a pop-up menu asking player which one to pick up.
						//TODO: Once the player desides which one, check if the unit can pick it up, then tell the unit to go pick it up.
						//TODO: If just 1, then check if the unit can pick it up, then tell the unit to go pick it up.

						//First, check how many objects the tile has. If it has 0, then let the game know there's nothing for the unit to pick up.
						//If 1, then go to pick up stage 2.
						//If 2+, then go to stage 1.

						//Actually, after further thought, I think stage 1 should be dumped in here.

						bool has_ore = false; //Does the tile have any ore?
						int num_ore = 0; //The number of ore the tile has.
						int total_objects = 0; //How many objects, that can be picked up, are on the tile?

						if(Map[i].orelist.size() < 1) //First check if the object lists are empty. If they all are, there's nothing to pick up here... //TODO: Add the rest of the object lists here.
						{
							//Nothing to pick up
							cout << "Nothing to pick up here!\n";
							out_string << "Nothing to pick up here!\n";

							move = false; //Tell the unit it's staying put.
							move_destination = 0; //Reset the unit's move destination.
							pick_up_on_reach_goal = false; //Nup, no object's getting a free ride home.
							pick_up_mode = false; //Turn off pick up mode...

							return false; //Ya, no use continuing.
						}

						if(Map[i].orelist.size() > 0) //Now we check if it's the orelist that had anything in it.
						{
							has_ore = true; //If it is, let the game know the tile has ore on it.
							num_ore = Map[i].orelist.size(); //Retrieve the number of ore on it.
							total_objects += num_ore; //Add the number of ore on this tile with the total number of objects on this tile.

							cout << "Yay! Has Ore!\nTODO REMINDER: Check what other objects are on the title, and if there are more, as the player which one they want.\nAnother one: If there is more than one ore, ask the player which one they want the unit to pick up. Very important!\n";

							move = true; //Let the game know the unit is moving.
							move_destination = i; //Let the game know what the location of the tile is.
							pick_up_on_reach_goal = true; //Yippie! The unit is gonna be collecting some stuff tonight.
							pick_up_mode = false; //Turn off pick up mode...

							if(calculate_path() == false) //If it can't calculate find a path...
							{
								move = false; //Tell the unit it doesn't have anywhere to go.
								move_destination = 0; //Reset the unit's move destination.
								pick_up_on_reach_goal = false; //Ya, don't want the unit randomaly trying to pick up nonexistant objects.

								cout << "Couldn't find path!\n"; //Debugging output.

								return false;
							}

							return true; //For now, return true. TODO: Later refine this function to check the other objects and also ask the user which object to pick up if there are multiple on the tile.
						}
					}
					else 
					{
						move = false; //Tell the unit it's staying put
						move_destination = 0; //Reset the unit's move destination.
						pick_up_on_reach_goal = false; //Nup, no objects getting a free ride home.
						pick_up_mode = false; //Turn off pick up mode..
						cout << "Can't pick up a wall!\n"; //Debugging output.
						out_string << "Can't pick up a wall!\n";

						return false; //No use in continuing!
					}
				}
			}
		}
	}
	else if(pick_up_stage == 1) //Ok, multiple objects. Create a pop-up menu asking the player to select the object to be picked up from a list.
	{
		//TODO: Create a pop-up menu asking player which object to pick up.
		//TODO: Then check if the player can pick up said object.
		//TODO: And finally, tell the unit to go pick that object up.
	}
	else if(pick_up_stage == 2) //Only one object. PICK IT UP!
	{
		//TODO: Check if the unit can pick up that object.
		//TODO: Then tell the unit to pick it up.
	}

	return false;
}

bool bClassUnit::check_shovel_command() //Checks if a shovel command was issued.
{
	int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
	bool run = true;
	if(event_struct.button.button == SDL_BUTTON_LEFT && event_struct.type == SDL_MOUSEBUTTONDOWN)
	{
		allow_deselect = true;
		//Check if a tile was clicked
		for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++)
		{
			if(run)
			{
				//Check if the tile is the one that was clicked on.
				if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
				{
					run = false;

					std::cout << "Position of the tile to be shovelled: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";
					out_string << "Position of the tile to be shovelled: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";

					if(Map[i].rubble == true)
					{
						shovel_mode = false; //let the game know shovel mode is off.
						move = true; //Let the game know that the unit is moving somewhere.
						move_destination = i; //Let the game know that the move destination of this unit is the tile that was just clicked on.
						shovel_on_reach_goal = true; //Tells the unit to shovel the rubble once it reaches its goal.
						layer_offset = (num_row_objects * num_col_objects * Map[i].layer); //Assign the layer offset.

						if(calculate_path() == false) //If it can't calculate find a path...
						{
							//What...Something done borked. The tile is inaccessible.
							move = false; //Tell the unit it's staying put
							move_destination = 0; //Reset the unit's move destination.
							shovel_on_reach_goal = false; //Ya, let the unit know it ain't shovelling any rubble.
							shovelling = false; //Reset this so that the game knows to not shovel the tile...
						}
					}
					else
					{
						move = false; //Tell the unit it's staying put
						move_destination = 0; //Reset the unit's move destination.
						shovel_on_reach_goal = false; //Ya, let the unit know it ain't shovelling any rubble.
						shovel_mode = false; //let the game know shovel mode is off.
						shovelling = false; //Reset this so that the game knows to not shovel the tile...
						cout << "Not rubble!\n";
					}
				}
			}
		}
	}
	return false;
}

bClassUnit unitlist[1000];
int unitnum = 0;
