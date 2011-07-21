/* Copyright the ORR-C Dev Team */
#include "popup_menu_field.hpp"
using namespace std;

popup_menu_field::popup_menu_field() //Constructor.
{
	sprite = NULL;
}

popup_menu_field::~popup_menu_field() //Deconstructor.
{
}

bool popup_menu_field::load_sprite(string filepath) //Load the field's sprite.
{
	//TODO: Load the field's sprite.

	return true;
}

bool popup_menu_field::render_field_sprite(std::string render_text) //Don't want to load a sprite? Then simply render the field's text!
{
	//TODO: Render the field's sprite.

	return true;
}

popup_menu_field field_drill_wall; //This field is used whenever a "Drill this wall" field is needed in a popup menu.
popup_menu_field field_shovel_rubble; //This field is used whenever a "Shovel this rubble" field is needed in a popup menu.
popup_menu_field field_moveto; //This field is used whenever a "Move to this tile" field is needed in a popup menu.
popup_menu_field field_construct_wall; //This field is used whenever a "Construct a wall on this tile" field is needed in a popup menu.
popup_menu_field field_pickup_ore; //This field is used whenever a "Pick up ore" field is needed in a popup menu.
popup_menu_field field_pickup_any_ore; //This field is used whenever a "Pick up any ore" field is needed in a popup meny.
