/* Copyright the ORR-C Dev Team */
#include "tile.hpp"

tile::tile() //Constructor. Initialize an empty tile.
{
	type_id = 0;
	sprite = NULL;
	name = "";
	wx = 0;
	wy = 0;
	layer = 0;
	plane = 0;
	width = 0;
	height = 0;
	ID = 0;
	temp = "";
	new_tile = 0;
	ramp = false;
	up_ramp = false;
	down_ramp = false;
	wall = false;
	self_supporting = false;
	ore_type = 0;
	can_mine = false;
	minimumn_mining_power = 0;
	air = false;
	turn_to_ground = false;
	ground_type = 0;
	generate_ore_on_mine = false;
	num_ore_to_generate = 0;
	tree = false;
	important = false;
	rubble = false;
	Active_Map_Entry = -1;
	active_animation = false;
	active_animation_entry = 0;
	has_construction = false;
	obstruction = false;
	ground = false;
	construction_in_progress = false;
	selected = false;
	visible = false;

	construction_in_progress_animation = NULL;

	qued_construction = false;
	qued_construction_sprite = NULL;

	wall_popup_menu = NULL;
	ground_popup_menu = NULL;
	rubble_popup_menu = NULL;

	targeted_for_drilling = false;
	sprite_targeted_for_drilling_spr = NULL;
}
