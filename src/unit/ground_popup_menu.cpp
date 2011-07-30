/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp
#include "../engine/Interface.hpp"

/* --------------------------------------------------------------
 * Everything related to updating the ground_popup_menu thing is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::ground_popup_menu_update() //Update the ground_popup_menu.
{
	if(ground_popup_menu->has_clicked_field) //Check if the ground popup menu has a clicked field.
	{
		if(ground_popup_menu->clicked_field->field_data == "moveto") //Check if the clicked field is a "moveto" field.
		{
			cout << "\nI see my moveto has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = ground_popup_menu->event_tile; //Copy this over so that there's no need to write the ground_popup_menu part.

			move = true; //Let the game know this unit is moving.
			move_destination = event_tile->ID;
			job_state = "moving";

			int layer_offset = (num_row_objects * num_col_objects * event_tile->layer); //Assign the layer offset.

			if(calculate_path() == false) //Now, calculate the path.
			{
				cout << "Foolish mortal. You doin' it wrong.\n"; //Yell at the user.

				move = false; //Tell the unit it's staying put
				move_destination = 0; //Reset the unit's move destination.
			}

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "pickup any ore") //Check if the clicked field is a "pickup any ore" field.
		{
			cout << "\nI see my pickup any ore field has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = ground_popup_menu->event_tile; //Copy this over so that there's no need to write the ground_popup_menu part.

			move = true; //Let the game know this unit is moving.
			move_destination = event_tile->ID; //Let the game know where the unit is going.
			pick_up_on_reach_goal = true; //Tells the unit to pick up the specified object once it reaches its goal.
			pick_up_object_type = 0; //Tell the unit what type of object it shall pick up. (Ore in this case)
			job_state = "picking_up";

			cout << "Event tile ID: " << event_tile->ID << "\n";

			int layer_offset = (num_row_objects * num_col_objects * event_tile->layer); //Assign the layer offset.

			if(calculate_path() == false) //Now, calculate the path.
			{
				//What...Something done borked. The tile is inaccessible.
				move = false; //Tell the unit it's staying put
				move_destination = 0; //Reset the unit's move destination.
				pick_up_on_reach_goal = false; //Ya, let the unit know it ain't shoveling any rubble.
				pick_up_object_type = -1; //Reset this so that the game knows to not shovel the tile...
			}

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "construct wall") //Check if the clicked field is a "construct wall" field.
		{
			cout << "\nI see my construct wall field has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = ground_popup_menu->event_tile; //Copy this over so that there's no need to write the ground_popup_menu part.

			move = true; //Let the game know this unit is moving.
			move_destination = event_tile->ID; //Let the game know where the unit is going.

			cout << "Event tile ID: " << event_tile->ID << "\n";

			int layer_offset = (num_row_objects * num_col_objects * event_tile->layer); //Assign the layer offset.

			if(!get_free_neighbor_tile(event_tile)) //Now, calculate the path.
			{
				//What...Something done borked. The tile is inaccessible.
				move = false; //Tell the unit it's staying put
				move_destination = 0; //Reset the unit's move destination.
			}
			else
			{
				//Create the new job.
				job_state = "constructing";
				my_job = new job;
				my_job->type = "construct";
				my_job->construction_type = "wall";
				my_job->tasked_tile = event_tile;
				my_job->taken = true;
				my_job->build_time = c_wall.build_time;

				if(c_wall.build_animation) //Check if the wall construction has a build animation.
				{
					my_job->construction_health = my_job->build_time * c_wall.animations[c_wall.build_animation_entry].num_frames; //Set the health of the construction accordingally.
					my_job->_animation = new animation;
					*my_job->_animation = c_wall.animations[c_wall.build_animation_entry]; //Assign a pointer to the build animation.

					cout << "Wall construction has an animation.\n"; //Debugging output.
				}
				else //Does not have an animation.
				{
					my_job->construction_health = my_job->build_time; //Set the construct time.
				}

				event_tile->qued_construction = true;
				event_tile->qued_construction_sprite = c_wall.construction_qued_sprite;
			}

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "construct door") //Check if the clicked field is a "construct door" field.
		{
			cout << "\nI see my construct door field has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = ground_popup_menu->event_tile; //Copy this over so that there's no need to write the ground_popup_menu part.

			move = true; //Let the game know this unit is moving.
			move_destination = event_tile->ID; //Let the game know where the unit is going.

			cout << "Event tile ID: " << event_tile->ID << "\n";

			int layer_offset = (num_row_objects * num_col_objects * event_tile->layer); //Assign the layer offset.

			if(!get_free_neighbor_tile(event_tile)) //Now, calculate the path.
			{
				//What...Something done borked. The tile is inaccessible.
				move = false; //Tell the unit it's staying put
				move_destination = 0; //Reset the unit's move destination.
			}
			else
			{
				//Create the new job.
				job_state = "constructing";
				my_job = new job;
				my_job->type = "construct";
				my_job->construction_type = "door";
				my_job->tasked_tile = event_tile;
				my_job->taken = true;

				event_tile->qued_construction = true;
				event_tile->qued_construction_sprite = c_door.construction_qued_sprite;
			}

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "open door") //Check if the clicked field is a "open door" field.
		{
			cout << "\nI see my open door field has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = ground_popup_menu->event_tile; //Copy this over so that there's no need to write the ground_popup_menu part.

			move = true; //Let the game know this unit is moving.
			move_destination = event_tile->ID; //Let the game know where the unit is going.

			cout << "Event tile ID: " << event_tile->ID << "\n";

			int layer_offset = (num_row_objects * num_col_objects * event_tile->layer); //Assign the layer offset.

			if(calculate_path() == false) //Now, calculate the path.
			{
				//What...Something done borked. The tile is inaccessible.
				move = false; //Tell the unit it's staying put
				move_destination = 0; //Reset the unit's move destination.
			}
			else
			{
				job_state = "moving";
			}

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "close door") //Check if the clicked field is a "close door" field.
		{
			//TODO: OPEN THE DOOR.
			cout << "\nI see my close door field has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = ground_popup_menu->event_tile; //Copy this over so that there's no need to write the ground_popup_menu part.

			//move = true; //Let the game know this unit is moving.
			//move_destination = event_tile->ID; //Let the game know where the unit is going.

			cout << "Event tile ID: " << event_tile->ID << "\n";

			int layer_offset = (num_row_objects * num_col_objects * event_tile->layer); //Assign the layer offset.

			/*if(calculate_path() == false) //Now, calculate the path.
			{
				//What...Something done borked. The tile is inaccessible.
				move = false; //Tell the unit it's staying put
				move_destination = 0; //Reset the unit's move destination.
			}
			else
			{
				//Create the new job.
				job_state = "incide_usa";
			}*/
			job_state = "incide_usa";

			close_door = true; //Let the unit know it gonna be closing a door.
			close_door_tile = event_tile; //Let the game know which tile contains the door the unit hath been commanded to close.

			tile* destination_tile = NULL;
			destination_tile = get_free_neighbor_tile(event_tile); //Assign the move destination to be a neighbour of the door tile.
			if(!destination_tile) //Error checking.
			{
				cout << "Can't find path to door!\n";
				cancel_current_activity();
			}

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.

			cout << "\n";
		}
		else
		{
			cout << "TODO: Find out what field was clicked in the unit's ground_popup_menu.\n"; //Debugging output.

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}

		Interface.active_popup_menus.clear(); //Empty this.
		active_popup_menu = false; //No active popup menu...
		allow_unit_selection = true; //Allow units to be selected/deselected.
	}
}
