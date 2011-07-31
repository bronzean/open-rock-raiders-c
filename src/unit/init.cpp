/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the unit header.
using namespace std;

/* --------------------------------------------------------------
 * The unit's init function is defined here.
 * ----------------------------------------------------------- */

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
