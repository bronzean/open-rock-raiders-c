/* Copyright the ORR-C Dev Team */
#pragma once
#include "../main.hpp"
#include "../Engine.hpp"

class interface //The interface class.
{
public:
	button g_teleport_button; //The global teleport button.
	button construct_wall_button; //The construct wall button.
        button construct_door_button; //The construct door button.

	void update(); //Update whatever needs to be updated.
	void draw_ui(); //Draw everything that needs to be drawn.
};

extern interface Interface; //The interface object.
