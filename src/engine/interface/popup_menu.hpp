/* Copyright the ORR-C Dev Team */
#pragma once
#include "../../main.hpp"
#include "../../Engine.hpp"
#include "popup_menu_field.hpp"

class popup_menu //The popup menu class.
{
public:
	std::vector<popup_menu_field> fields; //All the fields of the menu. You know, the little buttons you click on in a popup menu...

	popup_menu(); //Constructor.
	~popup_menu(); //Deconstructor.

	void update(); //Update whatever needs to be updated.
	void draw_menu(); //Draw all the fields of the popup menu. You know, all those little buttons...
};
