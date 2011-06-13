/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp

/* --------------------------------------------------------------
 * Everything related to the unit constructing stuff is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::construct_construction() //Does the stuff related to constructions.
{
	if(!move) //If the unit has reached the construction site...
	{
		try
		{
			//Draw_Message_Handler.add_message(wx + 32, wy, PCamera->layer, TTF_RenderText_Solid(font1, "Bob the builder!", c_green), 0); //Draw the "I'm bob the builder!" message.
			Draw_Message_Handler.add_message(wx + 32, wy, PCamera->layer, constructing_message_spr, 1, false); //Draw the "I'm bob the builder!" message.


			my_job->construction_health -= construct_rate;
			//my_job.construction_health -= construct_rate;

			if(my_job->construction_health <= 0 && construction_repositioning == 2)
			//if(my_job.construction_health <= 0)
			{
				cout << "Done building!\n";

				int i2 = 0;
				vector<job>::iterator iterator2;

				bool done = false;

				/*while(!done)
				{
					//if((unsigned)i2 >= Job_Que.jobs.size())
					if(i2 >= Job_Que.jobs.size())
					{
						cout << "FATAL: ERROR CODE 2: Failed to remove job from job que.\n";
						out_string << "FATAL: ERROR CODE 2: Failed to remove job from job que.\n";
						throw "FATAL: ERROR CODE 2";
					}

					//cout << "this->type = " << my_job->type << " and JOB->type = " << Job_Que.jobs[i2].type << "\n";
					//cout << "this->construction_type = " << my_job->construction_type << " and JOB->construction_type = " << Job_Que.jobs[i2].construction_type << "\n";
					//cout << "this->tasked_tile->ID = " << my_job->tasked_tile->ID << " and JOB->tasked_tile->ID = " << Job_Que.jobs[i2].tasked_tile->ID << "\n";
					//cout << "this->taken = " << my_job->taken << " and JOB->taken = " << Job_Que.jobs[i2].taken << "\n";
					//cout << "this->construction_health = " << my_job->construction_health << " and JOB->construction_health = " << Job_Que.jobs[i2].construction_health << "\n";

					cout << "this->type = " << my_job->type << "\n";
					cout << "this->construction_type = " << my_job->construction_type << "\n";
					cout << "this->tasked_tile->ID = " << my_job->tasked_tile->ID << "\n";
					cout << "this->taken = " << my_job->taken << " and JOB->taken = " << "\n";
					cout << "this->construction_health = " << my_job->construction_health << "\n";

					//if(&Job_Que.jobs[i2] == my_job)
					//if(my_job->compare(Job_Que.jobs[i2]))
					//if(Job_Que.jobs[i2].compare(*&my_job))
					if(Job_Que.jobs[i2].compare(my_job))
					{
						cout << "Done constructing!\n";
						out_string << "Done constructing!\n";

						if(my_job->construction_type == "wall")
						{
							my_job->tasked_tile->construct_construction(c_wall); //Transform specified tile into a wall.
						}

						Job_Que.jobs.erase(Job_Que.jobs.begin() + i2); //Remove this job from the job que.
						done = true;

						my_job = NULL;

						job_state = "idle";
					}

					i2++;
					iterator2++;
				}*/

				
				cout << "Done constructing!\n";
				out_string << "Done constructing!\n";

				if(my_job->construction_type == "wall")
				{
					my_job->tasked_tile->construct_construction(c_wall); //Add the wall construction to the specified tile.
				}
				else if(my_job->construction_type == "door")
				{
					my_job->tasked_tile->construct_construction(c_door); //Add the door construction to the specified tile.
				}

				delete my_job;
				my_job = NULL;

				construction_repositioning = 0; //Reset this so the raider moves off the tile next time too.
				//my_job.nullify(); //Similar to "my_job = NULL;"

				job_state = "idle";
			}
			else if(my_job->construction_health <= 0 && construction_repositioning == 0)
			{
				//heck if the raider can move off this tile once the construction is built.
				int layer_offset = (num_row_objects * num_col_objects * Map[my_job->tasked_tile->ID].layer); //Assign the layer offset.
				move_destination = (((((Map[my_job->tasked_tile->ID].wx) / 32) + ((Map[my_job->tasked_tile->ID].wy) / 32)) + ((num_row_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / 32)) ) ) - 1) + layer_offset; //grab tile to the left.
				move = true;
				construction_repositioning = 1;

				cout << "WX = " << Map[my_job->tasked_tile->ID].wx << ", WY = " << Map[my_job->tasked_tile->ID].wy << ", layer_offset = " << layer_offset << ", move_destination = " << move_destination << ".\n";

				/*if(calculate_path() == false)
				{
					if(move_destination > 0 && move_destination < num_tiles)
					{
						if(calculate_path() == false)
						{
							move_destination = (((((Map[my_job->tasked_tile->ID].wx) / 32) + ((Map[my_job->tasked_tile->ID].wy) / 32)) + ((num_row_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / 32)) ) ) + 1) + layer_offset; //It failed again. Grab the tile to the right.
							if(move_destination > 0 && move_destination < num_tiles)
							{
								if(calculate_path() == false)
								{
									move_destination = (((((Map[my_job->tasked_tile->ID].wx) / 32) + ((Map[my_job->tasked_tile->ID].wy) / 32)) + ((num_row_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / 32) - 1) ) ) - 1) + layer_offset; //Oh dear, it failed yet again. Grab the tile to the north.
									if(move_destination > 0 && move_destination < num_tiles)
									{
										if(calculate_path() == false)
										{
											move_destination = (((((Map[my_job->tasked_tile->ID].wx) / 32) + ((Map[my_job->tasked_tile->ID].wy) / 32)) + ((num_col_objects - 1)* ((wy / 32) + 1) ) ) + 1) + layer_offset; //You know the drill. Tile to the south now.
											if(move_destination > 0 && move_destination < num_tiles)
											{
												if(calculate_path() == false)
												{
													//OH COME ON. WHAT IS WRONG WITH THIS PLAYER. THEY CLICKED ON AN INACCESSIBLE TILE!
													move = false; //Tell the unit it's staying put
													move_destination = 0; //Reset the unit's move destination.
													construction_repositioning = 0;

													cout << "No place to move from here, fool.\n";
												}
											}
											else
											{
												move = false; //Tell the unit it's staying put
												move_destination = 0; //Reset the unit's move destination.

												construction_repositioning = 0;

												cout << "Can't move to a nonexistant tile1!\n";
											}
										}
									}
									else
									{
										move = false; //Tell the unit it's staying put
										move_destination = 0; //Reset the unit's move destination.

										construction_repositioning = 0;

										cout << "Can't move to a nonexistant tile2!\n";
									}
								}
							}
							else
							{
								move = false; //Tell the unit it's staying put

								construction_repositioning = 0;
								cout << "Can't move to a nonexistant tile3!\n";
							}
						}
					}
				}*/

				if((move_destination > 0 && move_destination < num_tiles))
				{
					if(calculate_path() == false || Map[move_destination].local_construction->door == true)
					{
						move_destination = (((((Map[my_job->tasked_tile->ID].wx) / 32) + ((Map[my_job->tasked_tile->ID].wy) / 32)) + ((num_row_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / 32)) ) ) + 1) + layer_offset; //It failed again. Grab the tile to the right.
						if(move_destination > 0 && move_destination < num_tiles)
						{
							if(calculate_path() == false || Map[move_destination].local_construction->door == true)
							{
								move_destination = (((((Map[my_job->tasked_tile->ID].wx) / 32) + ((Map[my_job->tasked_tile->ID].wy) / 32)) + ((num_row_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / 32) - 1) ) ) - 1) + layer_offset; //Oh dear, it failed yet again. Grab the tile to the north.
								if((move_destination > 0 && move_destination < num_tiles))
								{
									if(calculate_path() == false || Map[move_destination].local_construction->door == true)
									{
										move_destination = (((((Map[my_job->tasked_tile->ID].wx) / 32) + ((Map[my_job->tasked_tile->ID].wy) / 32)) + ((num_col_objects - 1)* ((Map[my_job->tasked_tile->ID].wy / 32) + 1) ) ) + 1) + layer_offset; //You know the drill. Tile to the south now.
										if((move_destination > 0 && move_destination < num_tiles))
										{
											if(calculate_path() == false || Map[move_destination].local_construction->door == true)
											{
												//OH COME ON. WHAT IS WRONG WITH THIS PLAYER. THEY CLICKED ON AN INACCESSIBLE TILE!
												move = false; //Tell the unit it's staying put
												move_destination = 0; //Reset the unit's move destination.
												construction_repositioning = 0;

												cout << "What? Failed all the checks...\n";
											}
										}
										else
										{
											move = false; //Tell the unit it's staying put
											move_destination = 0; //Reset the unit's move destination.
											construction_repositioning = 0;
											cout << "Can't move to a nonexistant tile!\n";
										}
									}
								}
								else
								{
									move = false; //Tell the unit it's staying put
									move_destination = 0; //Reset the unit's move destination.
									construction_repositioning = 0;
									cout << "Can't move to a nonexistant tile!\n";
								}
							}
						}
						else
						{
							move = false; //Tell the unit it's staying put
							construction_repositioning = 0;
							cout << "Can't move to a nonexistant tile!\n";
						}
					}
				}
				else
				{
					move = false; //Tell the unit it's staying put
					move_destination = 0;

					construction_repositioning = 0;
					cout << "Can't move to a nonexistant tile!\n";
				}

				if(construction_repositioning == 0)
				{
					//Add job back to job que.
					Job_Que.jobs.push_back(*my_job);
					delete my_job;
					job_state = "idling";
					cout << "What? Something failed.\n";
				}
			}
			else if(construction_repositioning == 1 && move == false)
			{
				construction_repositioning = 2;
			}
		}
		catch(string error)
		{
			cout << "Blarg it failed.\n";
			//return "";
			return;
		}
		catch(char const *error)
		{
			cout << "Blarg it failed.\n";
			//return "";
			return;
		}
		catch(...) //Oops, something borked. General error. Abort!
		{
			gameover = true; //Tells the game to stop running.
			throw; //Quit this function.
		}
	}
	else //The unit hasn't yet reached the destination.
	{
		//SDL_Surface* temp_surf = TTF_RenderText_Solid(font1, "Here I come my aunt cinnamon!", c_green);
		//Draw_Message_Handler.add_message(wx + 32, wy, PCamera->layer, construct_walking_message_spr, 0, false); //Draw the "I'm coming to construct stuff!" message.
		if(/*frames_since_last_move != 1 &&*/ !allow_move)
		{
			//if(allow_draw)
			//{
				Draw_Message_Handler.add_message(wx + 32, wy, PCamera->layer, construct_walking_message_spr, 1, false); //Draw the "I'm coming to construct stuff!" message.
			//}
		}
		//SDL_FreeSurface(temp_surf);
		//TODO: Check if the unit has anywhere to move from here. If it doesn't, remove this job from the job que.
		/*
		if(can't_move_off_this_tile)
		{
			draw_message("I'm sorry sir, I can't let you mmmmmmmmmm do that.");
		}
		*/
	}
}
