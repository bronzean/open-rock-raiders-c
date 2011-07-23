/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp
#include "../engine/Interface.hpp"

/* --------------------------------------------------------------
 * Everything related to updating the rubble_popup_menu thing is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::rubble_popup_menu_update() //Update the wall_popup_menu.
{
	if(rubble_popup_menu->has_clicked_field) //Check if the rubble popup menu has a clicked field.
	{
		if(rubble_popup_menu->clicked_field->field_data == "shovel rubble") //Check if the clicked field is a "shovel rubble" field.
		{
			cout << "\nI see my shovel rubble field has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = rubble_popup_menu->event_tile; //Copy this over so that there's no need to write the rubble_popup_menu part.

			move = true; //Let the game know this unit is moving.
			move_destination = event_tile->ID; //Let the game know where the unit is going.
			shovel_on_reach_goal = true; //Tells the unit to shovel the rubble once it reaches its goal.
			job_state = "shoveling";

			cout << "Event tile ID: " << event_tile->ID << "\n";

			int layer_offset = (num_row_objects * num_col_objects * event_tile->layer); //Assign the layer offset.

			if(calculate_path() == false) //Now, calculate the path.
			{
				//What...Something done borked. The tile is inaccessible.
				move = false; //Tell the unit it's staying put
				move_destination = 0; //Reset the unit's move destination.
				shovel_on_reach_goal = false; //Ya, let the unit know it ain't shoveling any rubble.
				shovelling = false; //Reset this so that the game knows to not shovel the tile...
			}

			rubble_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			rubble_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(rubble_popup_menu->clicked_field->field_data == "moveto") //Check if the clicked field is a "moveto" field.
		{
			cout << "\nI see my moveto has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = rubble_popup_menu->event_tile; //Copy this over so that there's no need to write the rubble_popup_menu part.

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

			rubble_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			rubble_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(rubble_popup_menu->clicked_field->field_data == "pickup any ore") //Check if the clicked field is a "pickup any ore" field.
		{
			cout << "\nI see my pickup any ore field has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = rubble_popup_menu->event_tile; //Copy this over so that there's no need to write the rubble_popup_menu part.

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

			rubble_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			rubble_popup_menu->clicked_field = NULL; //Reset this.
		}
		else
		{
			cout << "TODO: Find out what field was clicked in the unit's rubble_popup_menu.\n"; //Debugging output.

			rubble_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			rubble_popup_menu->clicked_field = NULL; //Reset this.
		}

		Interface.active_popup_menus.clear(); //Empty this.
		active_popup_menu = false; //No active popup menu...
		allow_unit_selection = true; //Allow units to be selected/deselected.
	}
}
