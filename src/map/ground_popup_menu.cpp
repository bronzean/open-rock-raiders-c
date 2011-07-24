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
		if(ground_popup_menu->clicked_field->field_data == "moveto") //Check if the clicked field is a "moveto" field.
		{
			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "pickup any ore") //Check if the clicked field is a "pickup any ore" field.
		{
			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "construct wall") //Check if the clicked field is a "construct wall" field.
		{
			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "construct door") //Check if the clicked field is a "construct door" field.
		{
			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "open door") //Check if the clicked field is a "open door" field.
		{
			ground_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			ground_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(ground_popup_menu->clicked_field->field_data == "close door") //Check if the clicked field is a "close door" field.
		{
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
	}
}
