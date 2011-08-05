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

	//Check if the tiles around this tile have constructions on them, and change the sprites accordingally.
	int the_tile_id = ID - 1; //First check the tile to the left.
	tile* the_tile = NULL;
	if(the_tile_id > 0 && the_tile_id < num_tiles) //If tile exists.
	{
		the_tile = &Map[the_tile_id];

		if(the_tile->has_construction) //If the tile has a construction.
		{
			if(the_tile->local_construction->wall)
			{
				local_construction->neighbour_left = the_tile->local_construction; //Assign the neighbour.

				the_tile->local_construction->neighbour_right = local_construction; //Assign the other construction's neighbour.
			}
		}
	}
	the_tile_id = ID + 1; //Check tile to right.
	the_tile = NULL;
	if(the_tile_id > 0 && the_tile_id < num_tiles) //If tile exists.
	{
		the_tile = &Map[the_tile_id];

		if(the_tile->has_construction) //If the tile has a construction.
		{
			if(the_tile->local_construction->wall)
			{
				local_construction->neighbour_right = the_tile->local_construction; //Assign the neighbour.

				the_tile->local_construction->neighbour_left = local_construction; //Assign the other construction's neighbour.
			}
		}
	}
	the_tile_id = ID - num_row_objects; //Check tile to north.
	the_tile = NULL;
	if(the_tile_id > 0 && the_tile_id < num_tiles) //If tile exists.
	{
		the_tile = &Map[the_tile_id];

		if(the_tile->has_construction) //If the tile has a construction.
		{
			if(the_tile->local_construction->wall)
			{
				local_construction->neighbour_up = the_tile->local_construction; //Assign the neighbour.

				the_tile->local_construction->neighbour_down = local_construction; //Assign the other construction's neighbour.
			}
		}
	}
	the_tile_id = ID + num_row_objects; //Check tile to south.
	the_tile = NULL;
	if(the_tile_id > 0 && the_tile_id < num_tiles) //If tile exists.
	{
		the_tile = &Map[the_tile_id];

		if(the_tile->has_construction) //If the tile has a construction.
		{
			if(the_tile->local_construction->wall)
			{
				local_construction->neighbour_down = the_tile->local_construction; //Assign the neighbour.

				the_tile->local_construction->neighbour_up = local_construction; //Assign the other construction's neighbour.
			}
		}
	}
	constructions_on_map.push_back(local_construction); //Let the game know this construction exists.
}
