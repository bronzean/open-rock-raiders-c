/* Copyright the ORR-C Dev Team */
#include "construction.hpp"

construction::construction() //Constructor. Initializes an empty construction.
{
	name = "";
	wall = false;
	type_id = 0;
	sprite = NULL;
	floor = false;
	door = false;
	door_strength = 0;
	door_locked = false;
	door_open_time = 0;

	/*door_open_animation = false;
	door_close_animation = false;
	door_open_animation_entry = 0;
	door_close_animation_entry = 0;*/

	active_animation = false;
	active_animation_entry = 0;

	open_animation = false;
	open_animation_entry = 0;
	close_animation = false;
	close_animation_entry = 0;
}

void construction::init(std::string NAME, bool WALL, bool FLOOR, bool DOOR, int DOOR_STRENGTH, int TYPE_ID, std::string SPRITE) //Initalize a new construction type.
{
	name = NAME;
	wall = WALL;
	floor = FLOOR;
	type_id = TYPE_ID;
	//sprite = img_load3(SPRITE);
	if(SPRITE != "")
	{
		img_load_safe(SPRITE, &sprite);
	}
	door = DOOR;
	door_strength = DOOR_STRENGTH;
}

void construction::copy_from(construction Construction) //Give this tile the properties of the one being copied.
{
	name = Construction.name;
	wall = Construction.wall;
	floor = Construction.floor;
	type_id = Construction.type_id;
	sprite = Construction.sprite;
	door = Construction.door;
	door_locked = Construction.door_locked;
	door_strength = Construction.door_strength;
}

void construction::draw_sprite(int wx, int wy, int layer) //Draw the construction's sprite.
{
	if(active_animation == true) //If an animation is going on...
	{
		animations[active_animation_entry].draw_sprite(wx, wy, layer); //Draw the animation.
	}
	else
	{
		draw((wx) - (PCamera->wx), (wy) - (PCamera->wy), sprite, screen); //Now draw the sprite to the screen.
	}
}

/*void bClassUnit::select() //Checks if the player selected/deselected the unit.
{

	if(event_struct.button.button == SDL_BUTTON_LEFT && event_struct.type == SDL_MOUSEBUTTONDOWN && mining_mode == false && selectable == true && allow_deselect == true && allow_unit_selection) //If the left mouse button was pressed and this unit can be selected...
	{
		if(event_struct.button.x + PCamera->wx >= wx && event_struct.button.x + PCamera->wx <= wx + width && event_struct.button.y + PCamera->wy >= wy && event_struct.button.y + PCamera->wy <= wy + height && mining_mode != true && shovel_mode != true ) //Checks if the mouse clicked on this unit.
		{
			if(selected == false) //If the unit is not selected allready.
			{
				std::cout << "\nSelected " << name << "\n"; //Let the user know this unit was selected.
			}
			selected = true; //Let's the game know this unit has been selected.
		}
		else //Ok, the user did not click on this unit.
		{
			if(selected == true) //If the unit is selected.
			{
				std::cout << "\nDeselected " << name << "\n"; //Let the user know the unit has been deselected.
				mining_mode = false; //No use to keep mining mode on anymore since it's not even selected anymore.
				shovel_mode = false; //No use to keep shovelling mode on anymore since it's not even selected anymore.
			}

			selected = false; //Let's the game know this unit is not selected.
		}
	}
}*/

construction c_wall;
construction c_floor;
construction c_door;
