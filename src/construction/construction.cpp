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
	door_open_animation = false;
	door_close_animation = false;
	door_open_animation_entry = 0;
	door_close_animation_entry = 0;
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

void construction::copy_from(construction Construction)
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

construction c_wall;
construction c_floor;
construction c_door;
