/* Copright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the game object class stuff header file.

bool bClassUnit::check_mine_command() //Checks if a mine command was issued.
{
	int layer_offset = (num_row_objects * num_col_objects * layer); //Assign the layer offset.
	bool run = true;
	if(event_struct.button.button == SDL_BUTTON_LEFT && event_struct.type == SDL_MOUSEBUTTONDOWN)
	{
		allow_deselect = true;
		//Check if a tile was clicked
		for(int i = 0; i < (num_col_objects * num_row_objects) * num_layers; i++)
		{
			if(run)
			{
				//Check if the tile is the one that was clicked on.
				if(event_struct.button.x + PCamera->wx >= Map[i].wx && event_struct.button.x + PCamera->wx <= Map[i].wx + Map[i].width && event_struct.button.y + PCamera->wy >= Map[i].wy && event_struct.button.y + PCamera->wy <= Map[i].wy + Map[i].height && PCamera->layer == Map[i].layer)
				{
					run = false;

					std::cout << "Position of the tile to be mined: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";
					out_string << "Position of the tile to be mined: (" << Map[i].wx << "," << Map[i].wy << "," << Map[i].layer << ") and index is: " << i << "\n";

					if(Map[i].wall == true)
					{
						mining_mode = false; //let the game know mining mode is off.
						move = true; //Let the game know that the unit is moving somewhere.
						move_destination = i; //Let the game know that the move destination of this unit is the tile that was just clicked on.
						mine_tile_id = i; //Let the game know what the mining target is...
						mine_on_reach_goal = true; //Tells the unit to mine the wall once it reaches its goal.
						layer_offset = (num_row_objects * num_col_objects * Map[i].layer); //Assign the layer offset.

						if(calculate_path() == false) //If it can't calculate find a path...
						{
							move_destination = (((((Map[i].wx) / 32) + ((Map[i].wy) / 32)) + ((num_row_objects - 1)* ((Map[i].wy / 32)) ) ) - 1) + layer_offset; //grab tile to the left.
							if(move_destination > 0 && move_destination < num_tiles)
							{
								if(calculate_path() == false)
								{
									move_destination = (((((Map[i].wx) / 32) + ((Map[i].wy) / 32)) + ((num_row_objects - 1)* ((Map[i].wy / 32)) ) ) + 1) + layer_offset; //It failed again. Grab the tile to the right.
									if(move_destination > 0 && move_destination < num_tiles)
									{
										if(calculate_path() == false)
										{
											move_destination = (((((Map[i].wx) / 32) + ((Map[i].wy) / 32)) + ((num_row_objects - 1)* ((Map[i].wy / 32) - 1) ) ) - 1) + layer_offset; //Oh dear, it failed yet again. Grab the tile to the north.
											if(move_destination > 0 && move_destination < num_tiles)
											{
												if(calculate_path() == false)
												{
													move_destination = (((((Map[i].wx) / 32) + ((Map[i].wy) / 32)) + ((num_col_objects - 1)* ((Map[i].wy / 32) + 1) ) ) + 1) + layer_offset; //You know the drill. Tile to the south now.
													if(move_destination > 0 && move_destination < num_tiles)
													{
														if(calculate_path() == false)
														{
															//OH COME ON. WHAT IS WRONG WITH THIS PLAYER. THEY CLICKED ON AN INACCESSIBLE TILE!
															move = false; //Tell the unit it's staying put
															move_destination = 0; //Reset the unit's move destination.
															mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
															mining = false; //Reset this so that the game knows to not mine the wall...
														}
													}
													else
													{
														move = false; //Tell the unit it's staying put
														move_destination = 0; //Reset the unit's move destination.
														mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
														mining_mode = false; //let the game know mining mode is off.
														mining = false; //Reset this so that the game knows to not mine the wall...
														cout << "Can't move to a nonexistant tile!\n";
													}
												}
											}
											else
											{
												move = false; //Tell the unit it's staying put
												move_destination = 0; //Reset the unit's move destination.
												mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
												mining_mode = false; //let the game know mining mode is off.
												mining = false; //Reset this so that the game knows to not mine the wall...
												cout << "Can't move to a nonexistant tile!\n";
											}
										}
									}
									else
									{
										move = false; //Tell the unit it's staying put
										move_destination = 0; //Reset the unit's move destination.
										mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
										mining_mode = false; //let the game know mining mode is off.
										mining = false; //Reset this so that the game knows to not mine the wall...
										cout << "Can't move to a nonexistant tile!\n";
									}
								}
							}
							else
							{
								move = false; //Tell the unit it's staying put
								move_destination = 0; //Reset the unit's move destination.
								mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
								mining_mode = false; //let the game know mining mode is off.
								mining = false; //Reset this so that the game knows to not mine the wall...
								cout << "Can't move to a nonexistant tile!\n";
							}
						}
					}
					else
					{
						move = false; //Tell the unit it's staying put
						move_destination = 0; //Reset the unit's move destination.
						mine_on_reach_goal = false; //Ya, let the unit know it ain't mining anything tonight.
						mining_mode = false; //let the game know mining mode is off.
						mining = false; //Reset this so that the game knows to not mine the wall...
						cout << "Not a wall!\n";
					}
				}
			}
		}
	}
	return false;
}
