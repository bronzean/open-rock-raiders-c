/* Copright the ORR-C Dev Team */
#pragma once
#include "../main.hpp"
#include "../Engine.hpp"

class interface
{
public:
	button g_teleport_button;

	void update();
	void draw_ui();
};

extern interface Interface;
