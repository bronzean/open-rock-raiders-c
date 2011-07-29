/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * The function that adds a wall construction onto this tile is defined here.
 * ----------------------------------------------------------- */

#include "tile.hpp"

void tile::construct_construction(construction c_type) //Creates a construction here.
{
	local_construction = new construction; //Create the construction.
	//local_construction->init(c_type.name, c_type.wall, c_type.floor, c_type.type_id, ""); //Copy *most* of the variables.
	//local_construction->sprite = c_type.sprite; //Copy the sprite over too!
	local_construction->copy_from(c_type);
	has_construction = true; //Let's the game know that this tile has a construction.
	if(c_type.wall)
	{
		obstruction = true; //Since the construction is a wall, then this tile is an obstruction.
	}
	local_construction->containing_tile = this; //Let the construction know what tile contains it.

	if(c_type.teleporter) //Check if the construction is a teleporter.
	{
		bool exists = false;

		for(int i = 0; i < Active_Map.size(); i++)
		{
			if(Active_Map[i] == ID)
			{
				exists = true;
			}
		}

		if(!exists)
		{
			Active_Map.push_back(ID); //Tell the active map this tile needs updating.

			cout << "ID in active map: " << Active_Map[Active_Map.size() - 1] << "\n";
		}
	}
}
