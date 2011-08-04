/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp

void bClassUnit::cancel_current_activity() //Instead of always writing "mining = false; shovelling = false; etc", simply call this function and it'll do it ALL.
{
	move_path.clear();
	move = false;
	move_destination = -1;
	move_destination_ramp = -1;
	calculate_need_ramp = false;
	need_path = false;

	mining = false;
	mining_mode = false;
	mine_on_reach_goal = false;
	mine_tile_id = 0;

	shovelling = false;
	shovel_on_reach_goal = false;
	shovel_mode = false;

	chopping = false;
	chop_on_reach_goal = false;
	chop_mode = false;

	pick_up_on_reach_goal = false;
	pick_up_mode = false;
	pick_up_object_type = -1;
	pick_up_stage = 0;

	close_door = false;
	closing_door = false;
	close_door_tile = NULL;

	drill_out = false;
	taking_out_drill = false;
	putting_drill_away = false;

	drill_animation_frame_progress = 0;

	picked_up = false;
	pickup_progress = 0;

	active_animation = NULL;

	if(shovel_animation)
	{
		shovel_animation->current_frame = 0;
	}
	if(pick_up)
	{
		pick_up->current_frame = 0;
	}
	if(takeout_drill_left)
	{
		takeout_drill_left->current_frame = 0;
	}
	if(takeout_drill_right)
	{
		takeout_drill_right->current_frame = 0;
	}
	if(takeout_drill_up)
	{
		takeout_drill_up->current_frame = 0;
	}
	if(takeout_drill_down)
	{
		takeout_drill_down->current_frame = 0;
	}
	if(drill_left)
	{
		drill_left->current_frame = 0;
	}
	if(drill_right)
	{
		drill_right->current_frame = 0;
	}
	if(drill_up)
	{
		drill_up->current_frame = 0;
	}
	if(drill_down)
	{
		drill_down->current_frame = 0;
	}
	if(putaway_drill)
	{
		putaway_drill->current_frame = 0;
	}
	if(move_left)
	{
		move_left->current_frame = 0;
	}
	if(move_right)
	{
		move_right->current_frame = 0;
	}
	if(move_up)
	{
		move_up->current_frame = 0;
	}
	if(move_down)
	{
		move_down->current_frame = 0;
	}
	if(move_left_carryore)
	{
		move_left_carryore->current_frame = 0;
	}
	if(move_right_carryore)
	{
		move_right_carryore->current_frame = 0;
	}
	if(move_up_carryore)
	{
		move_up_carryore->current_frame = 0;
	}
	if(move_down_carryore)
	{
		move_down_carryore->current_frame = 0;
	}

	job_state = "idling";
	if(my_job /* && my_job_is_global */)
	{
		my_job->taken = false;
		Job_Que.jobs.push_back(*my_job);
		delete my_job;
		my_job = NULL;
	}
}
