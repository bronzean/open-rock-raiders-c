/* Copyright ORR-C dev team */
#include "unit.hpp"
using namespace std;

tile* bClassUnit::get_free_neighbor_tile(tile* src_tile)
{
	int layer_offset = (num_row_objects * num_col_objects * src_tile->layer); //Assign the layer offset.

	move = true; //I LIKE TO MOVE IT MOVE IT.

	bool calculate_next_tile = false; //Set to true if the current tile failed the check.

	cout << "WX = " << src_tile->wx << ", WY = " << src_tile->wy << ", layer_offset = " << layer_offset << "\n"; //Debugging output.

	move_destination = (((((src_tile->wx) / tile_width) + ((src_tile->wy) / tile_height)) + ((num_row_objects - 1)* ((src_tile->wy / tile_height)) ) ) - 1) + layer_offset; //Grab tile to the left, to start things off.

 	cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.


	if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile is "in bounds".
	{
		if(calculate_path() == false) //Calculate the path.
		{
			calculate_next_tile = true; //Calculate the next tile to see if it works.
		}
		else
		{
			return &Map[move_destination]; //Return the tile it found.
		}
	}

	if(calculate_next_tile) //Previous tile failed? Try this one.
	{
		calculate_next_tile = false; //First off, reset this.

		move_destination = (((((src_tile->wx) / tile_width) + ((src_tile->wy) / tile_height)) + ((num_row_objects - 1)* ((src_tile->wy / tile_height)) ) ) + 1) + layer_offset; //Last tile check failed. Grab the tile to the right this time.

 		cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

		if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
		{
			if(calculate_path() == false) //Calculate the path.
			{
				calculate_next_tile = true; //Eh, calculate next tile to see if that works.
			}
			else
			{
				return &Map[move_destination]; //Return the tile it found.
			}
		}
	}

	if(calculate_next_tile) //Previous tile failed? Try this one.
	{
		calculate_next_tile = false; //Reset this!

		move_destination = (((((src_tile->wx) / tile_width) + ((src_tile->wy) / tile_height)) + ((num_row_objects - 1)* ((src_tile->wy / tile_height) - 1) ) ) - 1) + layer_offset; //Oh dear, it failed yet again. Grab the tile to the north.


 		cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

		if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
		{
			if(calculate_path() == false) //Calculate the path.
			{
				calculate_next_tile = true; //Oh boy, last check to follow.
			}
			else
			{
				return &Map[move_destination]; //Return the tile it found.
			}
		}
	}

	if(calculate_next_tile) //Previous tile failed? Try this one.
	{
		calculate_next_tile = false;

		move_destination = (((((src_tile->wx) / tile_width) + ((src_tile->wy) / tile_height)) + ((num_col_objects - 1)* ((src_tile->wy / tile_height) + 1) ) ) + 1) + layer_offset; //You know the drill. Tile to the south now.

 		cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

		if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
		{
			if(calculate_path() == false) //Calculate the path.
			{
				//OH COME ON. WHAT IS WRONG WITH THIS PLAYER. THEY CLICKED ON AN INACCESSIBLE TILE!
				move = false; //Tell the unit it's staying put
				move_destination = 0; //Reset the unit's move destination.

				cout << "What's this? Failed all the checks...\n"; //Debugging output.
			}
		}
		else
		{
			return &Map[move_destination]; //Return the tile it found.
		}
	}

	return NULL; //Failure. Aww.
}
