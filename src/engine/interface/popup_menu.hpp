/* Copyright the ORR-C Dev Team */
#pragma once
#include "../../main.hpp"
#include "../../Engine.hpp"
#include "popup_menu_field.hpp"

class popup_menu_field;
class tile;

class popup_menu //The popup menu class.
{
public:
	std::vector<popup_menu_field> fields; //All the fields of the menu. You know, the little buttons you click on in a popup menu...
	bool has_clicked_field; //Has one of the fields of this popup menu been clicked?
	popup_menu_field* clicked_field; //Pointer to the clicked field.
	tile *event_tile;

	//The following two have to do with the location on the screen to draw the menu.
	int x; 
	int y;

	popup_menu(); //Constructor.
	~popup_menu(); //Deconstructor.

	void update(); //Update whatever needs to be updated.
	void draw_menu(); //Draw all the fields of the popup menu. You know, all those little buttons...

	void add_field(popup_menu_field field); //Add a field to this popup menu. Paramater: the new field to be added, of course.
	bool remove_field(int index); //Remove a field from this popup menu. Paramater: The index of the field in the fields vector.
};
