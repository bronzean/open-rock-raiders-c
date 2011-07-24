/* Copyright the ORR-C Dev Team */
#include "tile.hpp" //Blablabla, include tile.hpp
#include "../engine/Interface.hpp"

/* --------------------------------------------------------------
 * Everything related to updating the wall_popup_menu thing is defined here.
 * ----------------------------------------------------------- */

void tile::wall_popup_menu_update() //Update the wall_popup_menu.
{
	if(wall_popup_menu->has_clicked_field) //Check if the wall popup menu has a clicked field.
	{
		if(wall_popup_menu->clicked_field->field_data == "drill wall") //Check if the clicked field is a "drill wall" field.
		{
			cout << "\nI see my drill wall field has been clicked.\n"; //Debugging output.

			//Add a drill wall job.

			job new_job; //The new job.

			new_job.type = "drill wall"; //Set the job type.
			new_job.tasked_tile = this; //Tell the game which tile is involved with this job.

			Job_Que.add_job(new_job); //Add the job to the job que.

			cout << "Added job!\n"; //Debugging output.

			wall_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			wall_popup_menu->clicked_field = NULL; //Reset this.
		}
		else
		{
			cout << "TODO: Find out what field was clicked in the tile's wall_popup_menu.\n"; //Debugging output.

			wall_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			wall_popup_menu->clicked_field = NULL; //Reset this.
		}

		Interface.active_popup_menus.clear(); //Empty this.
		active_popup_menu = false; //No active popup menu...
		allow_unit_selection = true; //Allow units to be selected/deselected.
		selected = false; //This tile is selected no longer.
		tile_selected = false; //No selected tile.
		selected_tile = NULL; //Reset this.
	}
}
