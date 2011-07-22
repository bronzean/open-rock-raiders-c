/* Copyright the ORR-C Dev Team */
#include "popup_menu.hpp"
using namespace std;

popup_menu::popup_menu() //Constructor.
{
	x = 0;
	y = 0;
	has_clicked_field = false;
	clicked_field = NULL;
}

popup_menu::~popup_menu() //Deconstructor.
{
}

void popup_menu::update()
{
	if(!server)
	{
		//TODO: Check if one of the fields were clicked.
	}

	if(screen_needs_updating == false)
	{
		draw_menu();
	}
}

void popup_menu::draw_menu()
{
	//The following two are used in succesively drawing the sprites of the field menus.
	int new_x = x;
	int new_y = y;

	vector<popup_menu_field>::iterator iterator = fields.begin(); //Used to loop through the fields vector.

	//TODO: Loop through all the fields and draw their sprites.
	for(int i = 0; iterator < fields.end(); i++, iterator++)
	{
		fields[i].x = new_x;
		fields[i].y = new_y;
		fields[i].draw_sprite(); //Draw the sprite of the field.

		new_y += fields[i].sprite->h; //This ensures the next field will be drawn at the correct position.
	}
}

void popup_menu::add_field(popup_menu_field field) //Add a field to this popup menu. Paramater: the new field to be added, of course.
{
	fields.push_back(field); //Add the field to the fields vector.
}

bool popup_menu::remove_field(int index) //Remove a field from this popup menu. Paramater: The index of the field in the fields vector.
{
	if(index >= fields.size()) //Check if the index even exists.
	{
		return false; //Oop, doesn't exist. Notify the calling function that it failed to remove the field.
	}

	fields.erase(fields.begin() + index); //Remove the field from the fields vector.

	return true;
}
