/* Copyright the ORR-C Dev Team */
#include "construction.hpp"

construction::construction() //Constructor. Initializes an empty construction.
{
	name = "";
	type_id = 0;

	wall = false;

	floor = false;

	sprite = NULL;
	sprite_select = NULL;
	sprite_open = NULL;
	construction_qued_sprite = NULL;

	teleporter = false;
	teleport_signal_strength = 0;
	teleport_unit_type = NULL;

	door = false;
	door_strength = 0;
	locked = false;
	open_time = 0;
	close_time = 0;
	construction_open = false;
	opening = false;
	closing = false;
	open_ammount = 0;
	close_ammount = 0;
	can_automatic_open = false;

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
	build_animation = false;
	build_animation_entry = 0;

	build_time = 25;

	containing_tile = NULL;

	selectable = false;
	selected = false;
	allow_deselect = true;
}

void construction::init(std::string NAME, bool WALL, bool FLOOR, bool DOOR, bool TELEPORTER, int DOOR_STRENGTH, int TYPE_ID, std::string SPRITE) //Initalize a new construction type.
{
	name = NAME;
	wall = WALL;
	floor = FLOOR;
	type_id = TYPE_ID;
	teleporter = TELEPORTER;
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
	type_id = Construction.type_id;

	wall = Construction.wall;

	floor = Construction.floor;

	sprite = Construction.sprite;
	sprite_select = Construction.sprite_select;
	sprite_open = Construction.sprite_open;

	selectable = Construction.selectable;

	door = Construction.door;
	locked = Construction.locked;
	door_strength = Construction.door_strength;
	open_time = Construction.open_time;
	close_time = Construction.close_time;
	construction_open = Construction.construction_open;
	opening = Construction.opening;
	closing = Construction.closing;
	open_ammount = Construction.open_ammount;
	close_ammount = Construction.close_ammount;
	can_automatic_open = Construction.can_automatic_open;

	active_animation = Construction.active_animation;
	active_animation_entry = Construction.active_animation_entry;

	animations = Construction.animations;
	open_animation = Construction.open_animation;
	open_animation_entry = Construction.open_animation_entry;
	close_animation = Construction.close_animation;
	close_animation_entry = Construction.close_animation_entry;
	build_animation = Construction.build_animation;
	build_animation_entry = Construction.build_animation_entry;

	teleporter = Construction.teleporter;
	teleport_signal_strength = Construction.teleport_signal_strength;
	teleport_unit_type = Construction.teleport_unit_type;

	construction_qued_sprite = Construction.construction_qued_sprite;

	build_time = Construction.build_time;
}

void construction::draw_sprite(int wx, int wy, int layer) //Draw the construction's sprite.
{
	if(active_animation == true) //If an animation is going on...
	{
		animations[active_animation_entry].draw_sprite(wx, wy, layer); //Draw the animation.
	}
	else
	{
		if(construction_open == true) //Check if the construction is open. (Like, an open door or something)
		{
			draw((wx) - (PCamera->wx), (wy) - (PCamera->wy), sprite_open, screen); //Now draw the sprite to the screen.

			//cout << "Sprite open.\n";
		}
		else //Not open? Ok then, draw the normal sprite (Which doubles as the closed sprite for constructions which also have a sprite_open).
		{
			if(selected)
			{
				draw((wx) - (PCamera->wx), (wy) - (PCamera->wy), sprite_select, screen); //Now draw the sprite to the screen.
			}
			else
			{
				draw((wx) - (PCamera->wx), (wy) - (PCamera->wy), sprite, screen); //Now draw the sprite to the screen.
			}
		}
	}
}

void construction::open_thyself(bool automatic)  //Open the construction! (Door, for example.)
{
	if(!locked)
	{
		if(automatic && can_automatic_open) //Check if it is set to automatically open, and check if it even CAN automatically open.
		{
			opening = true; //Yay, automatic opening.
		}

		if(open_animation) //If it has an opening animation...
		{
			active_animation = true;
			active_animation_entry = open_animation_entry;
			if(open_ammount >= open_time * animations[open_animation_entry].num_frames) //Check if it is done opening.
			{
				opening = false; //Not opening anymore, it is open!
				construction_open = true; //Let the game know the door is now open.
				active_animation = false; //Let the game know the animation is over.
				active_animation_entry = 0; //Let the game know the active animation's entry.
				close_ammount = 0;
				open_ammount = 0;
				animations[open_animation_entry].current_frame = 0;

				cout << "Door opened.\n"; //Debugging output.
			}

			if((float)open_ammount / (float)open_time >= (float)animations[open_animation_entry].current_frame + 1) //Check if it's time to progress the opening animation.
			{
				animations[open_animation_entry].proceed_animation(); //Proceed the animation.
			}
		}
		else
		{
			construction_open = true; //Let the game know the construction is now open.
			close_ammount = 0;
			open_ammount = 0;
		}

		open_ammount++;
	}
	else
	{
		cout << "Can't open a locked door foo!\n"; //Yell at user.
	}
}

void construction::close_thyself(bool automatic) //Close the construction! (Door, for example.)
{
	if(automatic && can_automatic_open) //Check if it is set to automatically open, and check if it even CAN automatically open.
	{
		closing = true; //Yay, automatic opening.
	}

	if(close_animation) //If it has a closing animation...
	{
		active_animation = true;
		active_animation_entry = close_animation_entry;
		if(close_ammount >= close_time * animations[close_animation_entry].num_frames) //Check if it is done closing.
		{
			closing = false; //Not closing anymore, it is closed!
			construction_open = false; //Let the game know the door is now closed.
			active_animation = false; //Let the game know the animation is over.
			active_animation_entry = 0; //Let the game know the active animation's entry.
			close_ammount = 0;
			open_ammount = 0;
			animations[close_animation_entry].current_frame = 0;

			cout << "Door closed.\n"; //Debugging output.

			cout << "Num_frames: " << animations[close_animation_entry].num_frames << "\nclose ammount: " << close_ammount << "\nclose_time: " << close_time << "\n\n";
		}

		if((float)close_ammount / (float)close_time >= (float)animations[close_animation_entry].current_frame + 1) //Check if it's time to progress the closing animation.
		{
			animations[close_animation_entry].proceed_animation(); //Proceed the animation.
		}
	}
	else
	{
		closing = false;
		construction_open = false; //Let the game know the costruction is now closed.
		close_ammount = 0;
		open_ammount = 0;

		cout << "Door closed. No animation.n";
	}

	close_ammount++;
}

void construction::select() //Checks if the player selected/deselected the construction.
{
	if(event_struct.button.button == SDL_BUTTON_LEFT && selectable == true && allow_deselect == true) //If the left mouse button was pressed and this construction can be selected...
	{
		if(event_struct.button.x + PCamera->wx >= containing_tile->wx && event_struct.button.x + PCamera->wx <= containing_tile->wx + sprite->w && event_struct.button.y + PCamera->wy >= containing_tile->wy && event_struct.button.y + PCamera->wy <= containing_tile->wy + sprite->h) //Checks if the mouse clicked on this construction.
		{
			if(selected == false) //If the construction is not selected already.
			{
				std::cout << "\nSelected " << name << "\n"; //Let the user know this construction was selected.
			}
			selected = true; //Lets the game know this construction has been selected.
		}
		else //Ok, the user did not click on this construction.
		{
			if(selected == true) //If the construction is selected.
			{
				std::cout << "\nDeselected " << name << "\n"; //Let the user know the construction has been deselected.
				if(construction_selected)
				{
					if(selected_construction == this)
					{
						construction_selected = false;
						selected_construction = NULL;

						allow_unit_selection = true;
					}
				}
			}

			selected = false; //Let's the game know this construction is not selected.
		}
	}
}

construction c_wall;
construction c_floor;
construction c_door;
construction c_teleporter1; //Teleportation device.
