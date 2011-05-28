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
}

void construction::init(std::string NAME, bool WALL, bool FLOOR, bool DOOR, int TYPE_ID, string SPRITE) //Initalize a new construction type.
{
	name = NAME;
	wall = WALL;
	floor = FLOOR;
	door = DOOR;
	type_id = TYPE_ID;
	//sprite = img_load3(SPRITE);
	if(SPRITE != "")
	{
		img_load_safe(SPRITE, &sprite);
	}
}

void construction::copy_from(construction Construction)
{
	name = Construction.name;
	wall = Construction.wall;
	floor = Construction.floor;
	type_id = Construction.type_id;
	sprite = Construction.sprite;
	door = Construction.door;
}

construction c_wall;
construction c_floor;
construction c_door;
