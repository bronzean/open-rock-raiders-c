/* Copyright the ORR-C Dev Team */
#include "tile.hpp" //Blablabla, include tile.hpp
#include "../engine/Interface.hpp"

/* --------------------------------------------------------------
 * Everything related to updating the rubble_popup_menu thing is defined here.
 * ----------------------------------------------------------- */

void tile::rubble_popup_menu_update() //Update the wall_popup_menu.
{
	if(rubble_popup_menu->has_clicked_field) //Check if the rubble popup menu has a clicked field.
	{
		if(rubble_popup_menu->clicked_field->field_data == "shovel rubble") //Check if the clicked field is a "shovel rubble" field.
		{
			rubble_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			rubble_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(rubble_popup_menu->clicked_field->field_data == "moveto") //Check if the clicked field is a "moveto" field.
		{
			rubble_popup_menu->has_clicked_field = false; //Has a clicked field no longer.
			rubble_popup_menu->clicked_field = NULL; //Reset this.
		}
		else if(rubble_popup_menu->clicked_field->field_data == "pickup any ore") //Check if the clicked field is a "pickup any ore" field.
		{
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
	}
}
