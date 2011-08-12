/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the game object class stuff header file.
using namespace std;

/* --------------------------------------------------------------
 * Unit's constructor is defined here.
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
	sprite_left = NULL;
	sprite_right = NULL;
	sprite_up = NULL;
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
	allow_move = false;
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
	job_state = "idling";
	construct_rate = 1;
	constructing_message_str = "Bob the builder!";
	constructing_message_spr = NULL;
	construct_walking_message_str = "Here I come my aunt cinnamon!";
	construct_walking_message_spr = NULL;
	construction_repositioning = 0;

	wall_popup_menu = NULL;
	rubble_popup_menu = NULL;
	ground_popup_menu = NULL;

	carrying = false;
	drop_carried = false;

	my_job = NULL;

	close_door = false;
	closing_door = false;
	close_door_tile = NULL;
	needs_to_close_door = false;
	needs_to_close_door_tile = NULL;
	moves_till_close_door_time = 0;

	can_mine_wall = false;

	can_shovel_rubble = false;

	//holding_object = false;

	move_left = NULL;
	move_right = NULL;
	move_up = NULL;
	move_down = NULL;
	move_left_carryore = NULL;
	move_right_carryore = NULL;
	move_up_carryore = NULL;
	move_down_carryore = NULL;

	active_animation = NULL;

	taking_out_drill = false;
	drill_out = false;
	putting_drill_away = false;
	takeout_drill_left = NULL;
	takeout_drill_right = NULL;
	takeout_drill_up = NULL;
	takeout_drill_down = NULL;
	drill_left = NULL;
	drill_right = NULL;
	drill_up = NULL;
	drill_down = NULL;
	take_out_drill_time = 0;
	drill_time = 0;
	putaway_drill = NULL;
	putaway_drill_time = 0;
	take_out_drill_progress = 0;
	put_away_drill_progress = 0;
	drill_animation_frame_progress = 0;

	shovel_animation = NULL;
	shovel_time = 0;
	shovel_animation_frame_progress = 0;

	pick_up = NULL;
	pick_up_objects_sprite = NULL;
	pickup_time = 0;
	pickup_progress= 0;
	picked_up = false;

	heading = 180;

	sprite_ore_left = NULL;
	sprite_ore_right = NULL;
	sprite_ore_up = NULL;
	sprite_ore_down = NULL;

	teleport_in_time = 0;
	teleport_in_progress = 0;
	teleport_in_animation = NULL;
	teleport_in_animation_done = false;

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
