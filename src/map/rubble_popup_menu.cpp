/* Copyright the ORR-C Dev Team */
#include "tile.hpp" //Blablabla, include tile.hpp
#include "../engine/Interface.hpp"

/* --------------------------------------------------------------
 * Everything related to updating the rubble_popup_menu thing is defined here.
 * ----------------------------------------------------------- */

void tile::rubble_popup_menu_update() //Update the wall_popup_menu.
{
	cout << "In rubble popup menu update.\n"; //Debugging output.

	if(rubble_popup_menu->has_clicked_field) //Check if the rubble popup menu has a clicked field.
	{
		if(rubble_popup_menu->clicked_field->field_data == "shovel rubble") //Check if the clicked field is a "shovel rubble" field.
		{
			cout << "\nI see my shovel rubble field has been clicked.\n"; //Debugging output.

			//Add a shovel rubble job.

			job new_job; //The new job.

			new_job.type = "shovel rubble"; //Set the job type.
			new_job.tasked_tile = this; //Tell the game which tile is involved with this job.

			Job_Que.add_job(new_job); //Add the job to the job que.

			cout << "Added job!\n"; //Debugging output.

			rubble_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			rubble_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(rubble_popup_menu->clicked_field->field_data == "pickup any ore") //Check if the clicked field is a "pickup any ore" field.
		{
			cout << "\nI see my pickup any ore field has been clicked.\n"; //Debugging output.

			//Add a pick up ore job.

			job new_job; //The new job.

			new_job.type = "pick up ore"; //Set the job type.
			new_job.tasked_tile = this; //Tell the game which tile is involved with this job.

			Job_Que.add_job(new_job); //Add the job to the job que.

			cout << "Added job!\n"; //Debugging output.

			rubble_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			rubble_popup_menu->clicked_field = NULL; //Reset this.
		}
		else
		{
			cout << "TODO: Find out what field was clicked in the tile's rubble_popup_menu.\n"; //Debugging output.

			rubble_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			rubble_popup_menu->clicked_field = NULL; //Reset this.
		}

		Interface.active_popup_menus.clear(); //Empty this.
		active_popup_menu = false; //No active popup menu...
		allow_unit_selection = true; //Allow units to be selected/deselected.
		selected = false; //This tile is selected no longer.
		tile_selected = false; //No selected tile.
		selected_tile = NULL; //Reset this.
	}
}
