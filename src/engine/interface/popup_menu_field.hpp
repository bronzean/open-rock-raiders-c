/* Copyright the ORR-C Dev Team */
#pragma once
#include "../../main.hpp"
#include "../../Engine.hpp"

class popup_menu_field //The popup menu class.
{
public:
	SDL_Surface *sprite; //The sprite of the popup menu.

	popup_menu_field(); //Constructor.
	~popup_menu_field(); //Deconstructor.

	bool load_sprite(std::string filepath); //Load the field's sprite.
	bool render_field_sprite(std::string render_text); //Don't want to load a sprite? Then simply render the field's text!
};

extern popup_menu_field field_drill_wall; //This field is used whenever a "Drill this wall" field is needed in a popup menu.
extern popup_menu_field field_shovel_rubble; //This field is used whenever a "Shovel this rubble" field is needed in a popup menu.
extern popup_menu_field field_moveto; //This field is used whenever a "Move to this tile" field is needed in a popup menu.
extern popup_menu_field field_construct_wall; //This field is used whenever a "Construct a wall on this tile" field is needed in a popup menu.
extern popup_menu_field field_pickup_ore; //This field is used whenever a "Pick up ore" field is needed in a popup menu.
extern popup_menu_field field_pickup_any_ore; //This field is used whenever a "Pick up any ore" field is needed in a popup meny.
