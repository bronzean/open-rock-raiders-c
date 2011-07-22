/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp
#include "../engine/Interface.hpp"

/* --------------------------------------------------------------
 * Everything related to updating the wall_popup_menu thing is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::wall_popup_menu_update() //Update the wall_popup_menu.
{
	if(wall_popup_menu->has_clicked_field) //Check if the wall popup menu has a clicked field.
	{
		if(wall_popup_menu->clicked_field->field_data == "drill wall") //Check if the clicked field is a "drill wall" field.
		{
			cout << "\nI see my drill wall field has been clicked.\n"; //Debugging output.

			cancel_current_activity(); //Cancel whatever the unit is currently doing.

			tile* event_tile = wall_popup_menu->event_tile; //Copy this over so that there's no need to write the wall_popup_menu_part.

			move = true; //Let the game know this unit is moving.
			move_destination = event_tile->ID; //Let the game know where the unit is going.
			mine_tile_id = event_tile->ID; //Let the game know what tile the unit is mining.
			this->mine_on_reach_goal = true; //Let the game know the unit is going somewhere specifically to mine a wall.
			job_state = "mining";

			cout << "Event tile ID: " << event_tile->ID << "\n";

			int layer_offset = (num_row_objects * num_col_objects * event_tile->layer); //Assign the layer offset.

			//----------------------------
			//Tell the unit where to go.
			//----------------------------

			bool found_path = true;

			if(calculate_path() == false) //Now, calculate the path. It'll probably return false, since units can't walk through walls, and the destination is a wall.
			{
				bool calculate_next_tile = false;

				move_destination = (((((event_tile->wx) / tile_width) + ((event_tile->wy) / tile_height)) + ((num_row_objects - 1)* ((event_tile->wy / tile_height)) ) ) - 1) + layer_offset; //Grab tile to the left, to start things off.

					cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.


				if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile is "in bounds".
				{
					if(calculate_path() == false) //Calculate the path.
					{
						calculate_next_tile = true; //Calculate the next tile to see if it works.
						cout << "Tile to left failed.\n";
					}
				}

				if(calculate_next_tile) //Previous tile failed? Try this one.
				{
					calculate_next_tile = false; //First off, reset this.

					move_destination = (((((event_tile->wx) / tile_width) + ((event_tile->wy) / tile_height)) + ((num_row_objects - 1)* ((event_tile->wy / tile_height)) ) ) + 1) + layer_offset; //Last tile check failed. Grab the tile to the right this time.


						cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

					if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
					{
						if(calculate_path() == false) //Calculate the path.
						{
							calculate_next_tile = true; //Eh, calculate next tile to see if that works.
							cout << "Tile to right failed.\n";
						}
					}
				}

				if(calculate_next_tile) //Previous tile failed? Try this one.
				{
					calculate_next_tile = false; //Reset this!

					move_destination = (((((event_tile->wx) / tile_width) + ((event_tile->wy) / tile_height)) + ((num_row_objects - 1)* ((event_tile->wy / tile_height) - 1) ) ) - 1) + layer_offset; //Oh dear, it failed yet again. Grab the tile to the north.


						cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

					if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
					{
						if(calculate_path() == false) //Calculate the path.
						{
							calculate_next_tile = true; //Oh boy, last check to follow.
							cout << "Tile to north failed.\n";
						}
					}
				}

				if(calculate_next_tile) //Previous tile failed? Try this one.
				{
					calculate_next_tile = false;

					move_destination = (((((event_tile->wx) / tile_width) + ((event_tile->wy) / tile_height)) + ((num_col_objects - 1)* ((event_tile->wy / tile_height) + 1) ) ) + 1) + layer_offset; //You know the drill. Tile to the south now.


						cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

					if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
					{
						if(calculate_path() == false) //Calculate the path.
						{
							//OH COME ON. WHAT IS WRONG WITH THIS PLAYER. THEY CLICKED ON AN INACCESSIBLE TILE!
							move = false; //Tell the unit it's staying put
							move_destination = 0; //Reset the unit's move destination.
							mine_tile_id = 0; //Reset this.
							mine_on_reach_goal = false; //Let the unit know it isn't gonna mine any walls upon reaching its goal.
							job_state = "idling";

							cout << "What's this? Failed all the checks...\n"; //Debugging output.
							found_path = false;
						}
					}
				}
			}

			/*if(found_path)
			{
				mine_tile_id = event_tile->ID; //Let the game know what tile the unit is mining.
				mine_on_reach_goal = true; //Let the game know the unit is going somewhere specifically to mine a wall.

				cout << "Ensuring unit will mine.\n";
			}*/

			//----------------------------
			//End of telling the unit where to go.
			//----------------------------

			wall_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			wall_popup_menu->clicked_field = NULL; //Reset this.
		}
		else
		{
			cout << "TODO: Find out what field was clicked in the unit's wall_popup_menu.\n"; //Debugging output.

			wall_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			wall_popup_menu->clicked_field = NULL; //Reset this.
		}

		Interface.active_popup_menus.clear(); //Empty this.
		active_popup_menu = false; //No active popup menu...
		allow_unit_selection = true; //Allow units to be selected/deselected.
	}
}
