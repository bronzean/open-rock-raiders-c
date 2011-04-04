/* Copyright the ORR-C Dev Team */
#include "construction.hpp"

construction::construction() //Constructor. Initializes an empty construction.
{
	name = "";
	wall = false;
	type_id = 0;
	sprite = NULL;
	floor = false;
}

void construction::init(std::string NAME, bool WALL, bool FLOOR, int TYPE_ID, string SPRITE) //Initalize a new construction type.
{
	name = NAME;
	wall = WALL;
	floor = FLOOR;
	type_id = TYPE_ID;
	sprite = img_load3(SPRITE);
}
