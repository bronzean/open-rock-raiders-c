/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp
#include "../engine/Interface.hpp"

/* --------------------------------------------------------------
 * Everything related to updating the wall_popup_menu thing is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::rubble_popup_menu_update() //Update the wall_popup_menu.
{
	if(rubble_popup_menu->has_clicked_field) //Check if the rubble popup menu has a clicked field.
	{
		if(rubble_popup_menu->clicked_field->field_data == "shovel rubble") //Check if the clicked field is a "shovel rubble" field.
		{
			cout << "\nI see my shovel rubble field has been clicked.\n"; //Debugging output.

			tile* event_tile = rubble_popup_menu->event_tile; //Copy this over so that there's no need to write the shovel_popup_menu_part.

			move = true; //Let the game know this unit is moving.
			move_destination = event_tile->ID; //Let the game know where the unit is going.
			shovel_on_reach_goal = true; //Tells the unit to shovel the rubble once it reaches its goal.
			job_state = "shoveling";

			cout << "Event tile ID: " << event_tile->ID << "\n";

			int layer_offset = (num_row_objects * num_col_objects * event_tile->layer); //Assign the layer offset.

			bool found_path = true;

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
