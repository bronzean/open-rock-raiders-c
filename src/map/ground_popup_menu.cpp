/* Copyright the ORR-C Dev Team */
#include "tile.hpp" //Blablabla, include tile.hpp
#include "../engine/Interface.hpp"

/* --------------------------------------------------------------
 * Everything related to updating the ground_popup_menu thing is defined here.
 * ----------------------------------------------------------- */

void tile::ground_popup_menu_update() //Update the tile_popup_menu.
{
	if(ground_popup_menu->has_clicked_field) //Check if the ground popup menu has a clicked field.
	{
		if(ground_popup_menu->clicked_field->field_data == "pickup any ore") //Check if the clicked field is a "pickup any ore" field.
		{
			cout << "\nI see my pickup any ore field has been clicked.\n"; //Debugging output.

			//Add a pick up ore job.

			job new_job; //The new job.

			new_job.type = "pick up ore"; //Set the job type.
			new_job.tasked_tile = this; //Tell the game which tile is involved with this job.

			Job_Que.add_job(new_job); //Add the job to the job que.

			cout << "Added job!\n"; //Debugging output.

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "pickup all ore") //Check if the clicked field is a "pickup all ore" field.
		{
			cout << "\nI see my pickup all ore field has been clicked.\n"; //Debugging output.

			//Add a pick up ore job.

			for(int i = 0; i < orelist.size(); i++)
			{
				job new_job; //The new job.

				new_job.type = "pick up ore"; //Set the job type.
				new_job.tasked_tile = this; //Tell the game which tile is involved with this job.

				Job_Que.add_job(new_job); //Add the job to the job que.

				cout << "Added job!\n"; //Debugging output.
			}

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "construct wall") //Check if the clicked field is a "construct wall" field.
		{
			cout << "\nI see my construct wall field has been clicked.\n"; //Debugging output.

			//Add a construct wall command to the job que.
			job new_job;

			new_job.type = "construct";
			new_job.construction_type = "wall";
			new_job.tasked_tile = this;
			new_job.build_time = c_wall.build_time;

			if(c_wall.build_animation) //Check if the wall construction has a build animation.
			{
				new_job.construction_health = new_job.build_time * c_wall.animations[c_wall.build_animation_entry].num_frames; //Set the health of the construction accordingally.
				new_job._animation = new animation;
				*new_job._animation = c_wall.animations[c_wall.build_animation_entry]; //Assign a pointer to the build animation.

				cout << "Wall construction has a build animation.\n"; //Debugging output.
			}
			else //Does not have an animation.
			{
				new_job.construction_health = new_job.build_time; //Set the construct time.
			}

			Job_Que.add_job(new_job);

			cout << "Added job!\n";

			qued_construction = true;
			qued_construction_sprite = c_wall.construction_qued_sprite;

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "construct door") //Check if the clicked field is a "construct door" field.
		{
			cout << "\nI see my construct wall field has been clicked.\n"; //Debugging output.

			//Add a construct door command to the job que.
			job new_job;

			new_job.type = "construct";
			new_job.construction_type = "door";
			new_job.tasked_tile = this;
			new_job.build_time = c_door.build_time;

			if(c_door.build_animation) //Check if the door construction has a build animation.
			{
				new_job.construction_health = new_job.build_time * c_door.animations[c_door.build_animation_entry].num_frames; //Set the health of the construction accordingally.
				new_job._animation = new animation;
				*new_job._animation = c_door.animations[c_door.build_animation_entry]; //Assign a pointer to the build animation.

				cout << "Door construction has a build animation.\n"; //Debugging output.
			}
			else //Does not have an animation.
			{
				new_job.construction_health = new_job.build_time; //Set the construct time.
			}

			Job_Que.add_job(new_job);

			cout << "Added job!\n";

			qued_construction = true;
			qued_construction_sprite = c_door.construction_qued_sprite;

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "construct teleporter1") //Check if the clicked field is a "construct teleporter1" field.
		{
			cout << "\nI see my construct teleporter1 field has been clicked.\n"; //Debugging output.

			//Add a construct teleporter1 command to the job que.
			job new_job;

			new_job.type = "construct";
			new_job.construction_type = "teleporter1";
			new_job.tasked_tile = this;
			new_job.build_time = c_teleporter1.build_time;

			if(c_teleporter1.build_animation) //Check if the teleporter1 construction has a build animation.
			{
				new_job.construction_health = new_job.build_time * c_teleporter1.animations[c_teleporter1.build_animation_entry].num_frames; //Set the health of the construction accordingally.
				new_job._animation = new animation;
				*new_job._animation = c_teleporter1.animations[c_teleporter1.build_animation_entry]; //Assign a pointer to the build animation.

				cout << "Teleporter1 construction has a build animation.\n"; //Debugging output.
			}
			else //Does not have an animation.
			{
				new_job.construction_health = new_job.build_time; //Set the construct time.
			}

			Job_Que.add_job(new_job);

			cout << "Added job!\n";

			qued_construction = true;
			qued_construction_sprite = c_teleporter1.construction_qued_sprite;

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "open door") //Check if the clicked field is a "open door" field.
		{
			cout << "\nI see my open door field has been clicked.\n"; //Debugging output.

			//Add an open door command to the job que.
			job new_job;

			new_job.type = "open door";
			new_job.tasked_tile = this;

			Job_Que.add_job(new_job);

			cout << "Added job!\n";

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "close door") //Check if the clicked field is a "close door" field.
		{
			cout << "\nI see my close door field has been clicked.\n"; //Debugging output.

			//Add a close door command to the job que.
			job new_job;

			new_job.type = "incide_usa";
			new_job.tasked_tile = this;

			Job_Que.add_job(new_job);

			cout << "Added job!\n";

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else
		{
			cout << "TODO: Find out what field was clicked in the tile's ground_popup_menu.\n"; //Debugging output.

			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}

		Interface.active_popup_menus.clear(); //Empty this.
		active_popup_menu = false; //No active popup menu...
		allow_unit_selection = true; //Allow units to be selected/deselected.
		selected = false; //This tile is selected no longer.
		tile_selected = false; //No selected tile.
		selected_tile = NULL; //Reset this.
	}
}
