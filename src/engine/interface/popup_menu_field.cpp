/* Copyright the ORR-C Dev Team */
#include "popup_menu_field.hpp"
using namespace std;

popup_menu_field::popup_menu_field() //Constructor.
{
	sprite = NULL;
	x = 0;
	y = 0;
	parent_menu = NULL;
	field_data = "";
}

popup_menu_field::~popup_menu_field() //Deconstructor.
{
}

bool popup_menu_field::load_sprite(string filepath) //Load the field's sprite.
{
	//TODO: Load the field's sprite.

	if(!img_load_safe(filepath, &sprite)) //Load the sprite. With error checking.
	{
		return false; //Error. Abort! Abort!
	}

	return true; //Success!
}

bool popup_menu_field::render_field_sprite(std::string render_text) //Don't want to load a sprite? Then simply render the field's text!
{
	//TODO: Render the field's sprite.

	return true;
}

void popup_menu_field::draw_sprite() //Draw the sprite of this field.
{
	draw(x, y, sprite, screen); //Draw the sprite.
}

bool popup_menu_field::clicked() //Was the field clicked?
{
	if(event_struct.button.x >= x && event_struct.button.x <= (x + sprite->w) && event_struct.button.y >= y && event_struct.button.y <= (y + sprite->h)) //Check if the mouse click was on this field.
	{
		//Let the popup_menu containing this field know that this field was clicked.
		parent_menu->has_clicked_field = true;
		parent_menu->clicked_field = this;

		return true; //Yep, this field was clicked.
	}

	return false; //Nope, this field wasn't clicked.
}

void popup_menu_field::set_parent_menu(popup_menu *POPUP_MENU) //Sets the pointer parent_menu to the specified popup_menu.
{
	parent_menu = POPUP_MENU; //Assign the pointer.
}

popup_menu_field field_drill_wall; //This field is used whenever a "Drill this wall" field is needed in a popup menu.
popup_menu_field field_shovel_rubble; //This field is used whenever a "Shovel this rubble" field is needed in a popup menu.
popup_menu_field field_moveto; //This field is used whenever a "Move to this tile" field is needed in a popup menu.
popup_menu_field field_construct_wall; //This field is used whenever a "Construct a wall on this tile" field is needed in a popup menu.
popup_menu_field field_construct_door; //This field is used whenever a "Construct a door on this tile" field is needed in a popup menu.
popup_menu_field field_construct_teleporter1; //This field is used whenever a "Construct a teleporter1 on this tile" field is needed in a popup menu.
popup_menu_field field_pickup_ore; //This field is used whenever a "Pick up ore" field is needed in a popup menu.
popup_menu_field field_pickup_any_ore; //This field is used whenever a "Pick up any ore" field is needed in a popup menu.
popup_menu_field field_pickup_all_ore; //This field is used whenever a "Pick up any ore" field is needed in a popup menu.
popup_menu_field field_drop_carried; //This field is used whenever a "Drop what you're carrying" field is needed in a popup menu.
popup_menu_field field_open_door; //This field is used whenever a "open door" field is needed in a popup menu.
popup_menu_field field_close_door; //This field is used whenever a "close door" field is needed in a popup menu.
