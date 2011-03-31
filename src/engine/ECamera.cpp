/* Copyright the ORR-C Dev Team */
#include "../Engine.hpp"
#include "EClass.hpp"

/* -------------------------------------------------------
 * Everything related to the camera class is defined here.
 * ---------------------------------------------------- */

//Acts as the class's constructor.
camera::camera(int test)
{
	wx = 0; //The world x is assigned to 0.
	wy = 0; //The world y is assigned to 0.
	layer = 0; //The layer is assigned to 0.
	cout << "Camera layer is: " << layer << "\n"; //Debugging output.

	//current_layer_string.str(""); //The text that informs the player what layer they're on.
	//cout << "test\n";
	//current_layer_string << "Current layer: " << layer;
	//current_layer_sprite = TTF_RenderText_Solid(font1, current_layer_string.str().c_str(), c_white);
}

//Set the object's position.
void camera::set_pos(int WORLDX, int WORLDY)
{
	wx = WORLDX;
	wy = WORLDY;
}

//Get the object's world x.
int camera::get_wx()
{
	return wx;
}

//Get the object's world y.
int camera::get_wy()
{
	return wy;
}

//Centers on an object.
void camera::follow(int WX, int WY)
{
	wx = (WX - (SCREEN_WIDTH / 2));
	wy = (WY - (SCREEN_WIDTH / 2));
}
