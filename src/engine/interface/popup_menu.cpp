/* Copyright the ORR-C Dev Team */
#include "popup_menu.hpp"
using namespace std;

popup_menu::popup_menu() //Constructor.
{
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
	vector<popup_menu_field>::iterator iterator; //Used to loop through the fields vector.

	//TODO: Loop through all the fields and draw their sprites.
}
