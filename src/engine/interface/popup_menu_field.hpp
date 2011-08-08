/* Copyright the ORR-C Dev Team */
#pragma once
#include "../../main.hpp"
#include "../../Engine.hpp"

class popup_menu;

class popup_menu_field //The popup menu class.
{
public:
	SDL_Surface *sprite; //The sprite of the popup menu.
	int x, y;
	popup_menu* parent_menu; //A pointer to the popup_menu containing this field.
	std::string field_data; //Used to determine what type of field this even is.

	popup_menu_field(); //Constructor.
	~popup_menu_field(); //Deconstructor.

	bool load_sprite(std::string filepath); //Load the field's sprite.
	bool render_field_sprite(std::string render_text); //Don't want to load a sprite? Then simply render the field's text!

	void draw_sprite(); //Draw the sprite of this field.

	bool clicked(); //Was the field clicked?

	void set_parent_menu(popup_menu *POPUP_MENU); //Sets the pointer parent_menu to the specified popup_menu.
};

extern popup_menu_field field_drill_wall; //This field is used whenever a "Drill this wall" field is needed in a popup menu.
extern popup_menu_field field_shovel_rubble; //This field is used whenever a "Shovel this rubble" field is needed in a popup menu.
extern popup_menu_field field_moveto; //This field is used whenever a "Move to this tile" field is needed in a popup menu.
extern popup_menu_field field_construct_wall; //This field is used whenever a "Construct a wall on this tile" field is needed in a popup menu.
extern popup_menu_field field_construct_door; //This field is used whenever a "Construct a door on this tile" field is needed in a popup menu.
extern popup_menu_field field_construct_teleporter1; //This field is used whenever a "Construct a teleporter1 on this tile" field is needed in a popup menu.
extern popup_menu_field field_pickup_ore; //This field is used whenever a "Pick up ore" field is needed in a popup menu.
extern popup_menu_field field_pickup_any_ore; //This field is used whenever a "Pick up any ore" field is needed in a popup menu.
extern popup_menu_field field_pickup_all_ore; //This field is used whenever a "Pick up all ore" field is needed in a popup menu.
extern popup_menu_field field_drop_carried; //This field is used whenever a "Drop what you're carrying" field is needed in a popup menu.
extern popup_menu_field field_open_door; //This field is used whenever a "open door" field is needed in a popup menu.
extern popup_menu_field field_close_door; //This field is used whenever a "close door" field is needed in a popup menu.
