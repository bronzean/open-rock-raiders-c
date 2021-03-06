/* Copyright ORR-C dev team */
#include "unit.hpp"
using namespace std;

tile* bClassUnit::get_free_neighbor_tile(tile* src_tile)
{
	int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.

	move = true; //I LIKE TO MOVE IT MOVE IT.

	//First, calculate the path to the tile, and see if the tile right before the destination works. (It should, by the way...)
	move_destination = src_tile->ID;
	if(calculate_path()) //Calculate the path.
	{
		while(path_being_calculated) //While the path is being calculated...
		{
			cout << "Path being calculated.\n";
			SDL_Delay(100); //Pause 100 milliseconds (1/10th of a second).
		}

		if(path_calculated) //Check if the pathfinding was successful.
		{
			move_destination = move_path[move_path.size() - 2];
			if(calculate_path() && Map[move_destination].construction_in_progress == false)
			{
				return &Map[move_destination]; //Return the tile it found.
			}
			else if(Map[move_destination].construction_in_progress == true)
			{
				cout << "Construction in progress on this tile.\n";
			}
		}
	}
	

	bool calculate_next_tile = false; //Set to true if the current tile failed the check.

	cout << "WX = " << src_tile->wx << ", WY = " << src_tile->wy << ", layer_offset = " << layer_offset << "\n"; //Debugging output.

	move_destination = (((((src_tile->wx) / tile_width) + ((src_tile->wy) / tile_height)) + ((num_row_objects - 1)* ((src_tile->wy / tile_height)) ) ) - 1) + layer_offset; //Grab tile to the left, to start things off.

 	cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.


			/*while(path_being_calculated) //While the path is being calculated...
			{
				SDL_Delay(100); //Pause 100 milliseconds (1/10th of a second).
			}*/

	if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile is "in bounds".
	{
		if(calculate_path() == false || Map[move_destination].construction_in_progress == true) //Calculate the path.
		{
			calculate_next_tile = true; //Calculate the next tile to see if it works.

			if(Map[move_destination].construction_in_progress == true) //If a construction is currently in progress on that tile, don't use this tile for the construction path.
			{
				cout << "Construction in progress.\n";
			}
		}
		else
		{
			while(path_being_calculated) //While the path is being calculated...
			{
				cout << "Path being calculated.\n";
				SDL_Delay(100); //Pause 100 milliseconds (1/10th of a second).
			}

			if(path_calculated) //If it found a path...
			{
				return &Map[move_destination]; //Return the tile it found.
			}
			else //Failure!
			{
				calculate_next_tile = true; //Calculate the next tile to see if it works.
				cout << "Failed to find path.\n"; //Debugging output.
			}
		}
	}

	if(calculate_next_tile) //Previous tile failed? Try this one.
	{
		calculate_next_tile = false; //First off, reset this.

		move_destination = (((((src_tile->wx) / tile_width) + ((src_tile->wy) / tile_height)) + ((num_row_objects - 1)* ((src_tile->wy / tile_height)) ) ) + 1) + layer_offset; //Last tile check failed. Grab the tile to the right this time.

 		cout << "Move_destination = " << move_destination << ".\n"; //Debugging output.

		if(move_destination > 0 && move_destination < num_tiles) //Make sure the tile in question even exists!
		{
			if(calculate_path() == false || Map[move_destination].construction_in_progress == true) //Calculate the path.
			{
				calculate_next_tile = true; //Eh, calculate next tile to see if that works.

				if(Map[move_destination].construction_in_progress == true) //If something's being constructed on the destination tile...
				{
					cout << "Construction in progress.\n"; //Debuggint output.
				}
			}
			else
			{
				while(path_being_calculated) //While the path is being calculated...
				{
					cout << "Path being calculated.\n";
					SDL_Delay(100); //Pause 100 milliseconds (1/10th of a second).
				}

				if(path_calculated)
				{
					return &Map[move_destination]; //Return the tile it found.
				}
				else
				{
					calculate_next_tile = true;
					cout << "Failed to find path.\n";
				}
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
			if(calculate_path() == false || Map[move_destination].construction_in_progress == true) //Calculate the path.
			{
				calculate_next_tile = true; //Oh boy, last check to follow.

				if(Map[move_destination].construction_in_progress == true) //If something's being constructed on this tile...
				{
					cout << "Construction in progress.\n"; //Debugging output.
				}
			}
			else
			{
				while(path_being_calculated) //While the path is being calculated...
				{
					cout << "Path being calculated.\n";
					SDL_Delay(100); //Pause 100 milliseconds (1/10th of a second).
				}

				if(path_calculated)
				{
					return &Map[move_destination]; //Return the tile it found.
				}
				else
				{
					calculate_next_tile = true;
					cout << "Failed to find path!\n";
				}
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
			if(calculate_path() == false || Map[move_destination].construction_in_progress == true) //Calculate the path.
			{
				calculate_next_tile = true; //Oh boy, last check to follow.

				if(Map[move_destination].construction_in_progress == true) //If something's being constructed on this tile...
				{
					cout << "Construction in progress.\n"; //Debugging output.
				}
			}
			else
			{
				while(path_being_calculated) //While the path is being calculated...
				{
					cout << "Path being calculated.\n";
					SDL_Delay(100); //Pause 100 milliseconds (1/10th of a second).
				}

				if(path_calculated)
				{
					return &Map[move_destination]; //Return the tile it found.
				}
				else
				{
					calculate_next_tile = true;
					cout << "Failed to find path!\n";
				}
			}
		}
	}

	cout << "Failure aww.\n";

	return NULL; //Failure. Aww.
}
