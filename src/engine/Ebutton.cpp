/* Copright the ORR-C Dev Team */

/* ------------------------------------------------------------
 * Everything related to the button base class is defined here.
 * --------------------------------------------------------- */
#include "../Engine.hpp"

//Acts as the class's constructor.
void button::init(int button_width, int button_height, int X, int Y, SDL_Surface *SPRITE, SDL_Surface *D_SPRITE)
{
	x1 = X; //Top right corner's x is assigned.
	x2 = X + button_width; //Bottom left corner's x is assigned.
	dx2 = X + D_SPRITE->w; //Bottom left corner x that is used when the button is disabled is assigned.
	y1 = Y; //Top right corner's y is assigned.
	y2 = Y + button_height; //Bottom right corner's y is assigned.
	dy2 = Y + D_SPRITE->h; //Bottom right corner y that is used when the button is disabled is assigned.
	sprite = SPRITE; //The object's sprite is assigned.
	d_sprite = D_SPRITE; //The object's disabled sprite is assigned.
	enabled = false; //Enabled state of the object is assigned.
	state = 0; //The object's state is assigned.
}

//Acts as the class's constructor.
void button::init(int button_width, int button_height, SDL_Surface *SPRITE, SDL_Surface *D_SPRITE)
{
	x2 = x1 + button_width; //Bottom left corner's x is assigned.
	y2 = y1 + button_height; //Bottom right corner's y is assigned.
	dx2 = x1 + D_SPRITE->w; //Bottom left corner x that is used when the button is disabled is assigned.
	dy2 = y1 + D_SPRITE->h; //Bottom right corner y that is used when the button is disabled is assigned.
	sprite = SPRITE; //The object's sprite is assigned.
	d_sprite = D_SPRITE; //The object's disabled sprite is assigned.
	enabled = false; //Enabled state of the object is assigned.
	state = 0; //The object's state is assigned.
}

//Stuff to do with the mouse and the object.
bool button::clicked()
{
	//Teleportation code. TODO: Update it to use the map system.
	if(event_struct.button.x >= x1 && event_struct.button.x <= x2 && event_struct.button.y >= y1 && event_struct.button.y <= y2 && state == 1)
	{
		/*bool found = false;
		bool continue_ = true;
		for(int i = 0; i < 9; i++)
		{
			if(!found)
			{
				if(teleport_que_name[i] == "")
				found = true;
			}
			if(found && continue_)
			{
				teleport_que_name[i] = "raider";
				teleport_que ++;
				continue_ = false;
				return true;
			}
		}*/
		return true;
	}

	//If the button was clicked when it was disabled...
	else if(event_struct.button.x >= x1 && event_struct.button.x <= dx2 && event_struct.button.y >= y1 && event_struct.button.y <= dy2 && state == 0)
	{
		std::cout << "\nDisabled button was clicked\n"; //Debugging output.
	}

	return false;
}

//Udpate whatever there is to be updated.
void button::update()
{
	//If 'state' equals '1'...
	if(state == 1)
	{
		draw(x1, y1, sprite, screen); //Draw the object's sprite onto the screen.
	}
	//Else if 'state' equals '0'...
	else if(state == 0)
	{
		draw(x1, y1, d_sprite, screen); //Draw the object's disabled sprite onto the screen.
	}
}
