/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include unit.hpp
#include <iostream>
using namespace std;

/* --------------------------------------------------------------
 * Everything related to the unit constructing stuff is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::construct_construction() //Does the stuff related to constructions.
{
	if(!move) //Just make sure the raider ain't trying to go anywhere.
	{
		try
		{
			if(!paused)
			{
				//-------------------------------------
				//Here the construction is constructed.
				//-------------------------------------

				Draw_Message_Handler.add_message(wx + tile_width, wy, PCamera->layer, constructing_message_spr, 1, false); //Draw the "I'm Bob the builder!" message.

				my_job->construction_health -= construct_rate; //Progress the construction.
				my_job->tasked_tile->construction_in_progress = true;
				my_job->tasked_tile->qued_construction = false;

				//TODO: Progress the construction animation.

				if(my_job->_animation) //Check if the job has an animation.
				{
					cout << "Has build animation.\n";
					//TODO: Check if it's time to progress the animation.
					//(float)open_ammount / (float)open_time >= (float)animations[open_animation_entry].current_frame + 1
					//if((float)my_job->construction_health / (float)my_job->build_time >= (float)my_job->_animation->current_frame + 1)
					if( (float)((my_job->build_time * my_job->_animation->num_frames) - my_job->construction_health) / (float)my_job->build_time >= (float)my_job->_animation->current_frame + 1)
					{
						my_job->_animation->proceed_animation();

						cout << "Time to increase the sprite.\n";
					}

					my_job->tasked_tile->construction_in_progress_animation = my_job->_animation;

					//my_job->_animation->draw_sprite(my_job->tasked_tile->wx, my_job->tasked_tile->wy, my_job->tasked_tile->layer);
				}

				if(my_job->construction_health <= 0 /*&& construction_repositioning == 2*/) //Check if it's done constructing, and if the unit has already moved off the building's tile.
				{
					//-------------------------------------
					//Here the construction is finished.
					//-------------------------------------

					cout << "Done constructing!\n"; //Debugging output.
					out_string << "Done constructing!\n"; //Debugging output.

					if(my_job->construction_type == "wall") //Check if the unit is building a wall.
					{
						my_job->tasked_tile->construct_construction(c_wall); //Add the wall construction to the specified tile.
					}
					else if(my_job->construction_type == "door") //Check if the unit is building a door.
					{
						my_job->tasked_tile->construct_construction(c_door); //Add the door construction to the specified tile.
					}

					my_job->tasked_tile->construction_in_progress = false;

					delete my_job; //Free that memory!!!
					my_job = NULL; //Reset this.

					construction_repositioning = 0; //Reset this so the raider moves off the tile next time too.

					//job_state = "idle"; //Unit's done building. Now it's time for it to idle again.

					cancel_current_activity();
				}
				/*else if(my_job->construction_health <= 0 && construction_repositioning == 0) //Check if it's time to move off the tile.
				{
					//-------------------------------------
					//Check if the raider can move off this tile once the construction is built.
					//-------------------------------------

					construction_repositioning = 1; //Let the game know this unit is relocating itself.

					if(get_free_neighbor_tile(my_job->tasked_tile) == NULL) //See if it can find a free neighbor tile.
					{
						cout << "Failed to find empty tile.\n";

						cancel_current_activity(); //Blarg. Can't finish construction. Cancel it.
						return;
					}

					//TODO: Make sure the unit is not moving on a tile with the construction in progress variable set to true (in terrain.cpp)
				}
				else if(construction_repositioning == 1 && move == false) //Checks if the unit has relocated and is now pending construction finalisation.
				{
					construction_repositioning = 2; //YARR. Means the construction will finalise.
				}*/
			}
		}
		catch(string error)
		{
			cout << "ERROR CODE 3: Construction has failed. Error message: " << error << "\n"; //Debugging output.
			out_string << "ERROR CODE 3: Construction has failed. Error message: " << error << "\n"; //Log the error.
			return;
		}
		catch(char const *error)
		{
			cout << "ERROR CODE 3: Construction has failed. Error message: " << error << "\n"; //Debugging output.
			out_string << "ERROR CODE 3: Construction has failed. Error message: " << error << "\n"; //Log the error.
			return;
		}
		catch(...) //Oops, something borked. General error. Abort!
		{
			cout << "ERROR CODE 3: Construction has failed. NO ERROR MESSAGE AVAILABLE. " << "\n"; //Debugging output.
			out_string << "ERROR CODE 3: Construction has failed. NO ERROR MESSAGE AVAILABLE. " << "\n"; //Log the error.
			gameover = true; //Tells the game to stop running.
			throw; //Quit this function.
		}
	}
	else //The unit hasn't yet reached the destination.
	{
		if(!allow_move)
		{
			if(allow_draw)
			{
				//Draw_Message_Handler.add_message(wx + tile_width, wy, PCamera->layer, construct_walking_message_spr, 1, false); //Draw the "I'm coming to construct stuff!" message.
			}
		}
	}
}
