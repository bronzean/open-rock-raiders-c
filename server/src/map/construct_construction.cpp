/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * The function that adds a wall construction onto this tile is defined here.
 * ----------------------------------------------------------- */

#include "tile.hpp"

void tile::construct_construction(construction c_type) //Creates a construction here.
{
	local_construction = new construction; //Create the construction.
	local_construction->init(c_type.name, c_type.wall, c_type.floor, c_type.type_id, ""); //Copy *most* of the variables.
	local_construction->sprite = c_type.sprite; //Copy the sprite over too!
	has_construction = true; //Let's the game know that this tile has a construction.
	if(c_type.wall)
	{
		obstruction = true; //Since the construction is a wall, then this tile is an obstruction.
	}
}
