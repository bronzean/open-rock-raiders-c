/* Copyright the ORR-C Dev Team */
#pragma once
#include "../main.hpp"
#include "../Engine.hpp"
#include "sprite/sprite.hpp"
#include "interface/popup_menu.hpp"

class interface //The interface class.
{
public:
	button g_teleport_button; //The global teleport button.
	button construct_wall_button; //The construct wall button.
	button construct_door_button; //The construct door button.
	button construct_teleporter_button; //The construct teleporter button.

	std::vector<popup_menu*> active_popup_menus; //Vector containin the active popup menus.

	std::vector<sprite_wrapper*> sprites_to_draw; //Vector of pointers to the sprites that need to be drawn.

	interface(); //Constructor.
	~interface(); //Deconstructor.

	void update(); //Update whatever needs to be updated.
	void draw_ui(); //Draw everything that needs to be drawn.

	void draw_sprites_that_need_drawing(); //Draw the sprites that need drawing.
	void add_sprite_that_needs_drawing(sprite_wrapper *_sprite); //Add a sprite to the sprites_to_draw vector.
};

extern interface Interface; //The interface object.
