/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the game object class stuff header file.
using namespace std;

/* --------------------------------------------------------------
 * Everything related to the checking for jobs it can do is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::check_job() //Give the unit something to do out of the job que.
{
	if(!checking_job) //If not already checking for jobs.
	{
		if(Job_Que.jobs.size() > 0) //If there are even any jobs.
		{
			cout << "Spawning check job thread.\n";
			checking_job = true;
			done_checking_job = false;

			//spawn thread here.
			if(!check_job_thread) //If the unit's check job thread pointer is null (thus meaning no thread)...
			{
				pthread_t new_thread; //The new thread.
				threads.push_back(new_thread); //Add it to the list of threads.
				check_job_thread = &threads[threads.size() - 1]; //Assign the pointer.
				pthread_create(check_job_thread, NULL, bClassUnit::spawn_check_job_thread, this); //Then tell the check job thread to get to finding a job.

				cout << "Created a new check job thread.\n";
			}
			else
			{
				pthread_create(check_job_thread, NULL, bClassUnit::spawn_check_job_thread, this); //Then tell the check job thread to get to finding a job.
			}
		}
	}
	else
	{
		cout << "Already checking job!!!\n";
	}
}

void bClassUnit::actually_check_job() //Give the unit something to do out of the job que.
{
	/*if(!pthread_mutex_trylock(&Job_Que.job_mutex)) //If it can't get a lock on the job que, then cancel the job.
	{
		checking_job = false;
		done_checking_job = false;

		//cout << "Please wait for the other check job thread to finish.|||||||||||TODO: Allow multiple threads to check jobs at the same time.\n";
		//cout << "Locked.\n";

		pthread_exit(NULL);

		return;
	}*/

	pthread_mutex_lock(&Job_Que.job_mutex); //TODO: Allow multiple threads to check jobs at the same time.

	//Look through the job que until a job is found that this unit can perform.
	//Assign the closest job.

	//cout << "Checking job.\n";

	vector<int> jobs;
	vector<vector<int> > movepaths;

	int i = 0;
	bool done = false;
	vector<job>::iterator iterator2 = Job_Que.jobs.begin();

	//for(vector<job>::iterator iterator2 = Job_Que.jobs.begin(); iterator2 < Job_Que.jobs.end(); iterator2++, i++)
	while(!done)
	{
		if(iterator2 >= Job_Que.jobs.end())
		{
			done = true;
		}
		else
		{
			cout << "Blarg.\n";
			if(Job_Que.jobs[i].type == "construct" && Job_Que.jobs[i].taken == false)
			{

				/*TODO: Let the unit know where they have to go.
				 * Then calculate the path to it.
				 * Then finally let everybody else know that this job has been taken.
				 */

				cancel_current_activity();

				move_destination = Job_Que.jobs[i].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.
				move = true; //Let the game know this unit is going somewhere.
				//move_path.clear(); //Empty the move path so that movement doesn't glitch.
				//mining = false; //Let the game know the unit has moved away and has stopped mining the tile.
				//mine_on_reach_goal = false; //Let the game know the unit isn't moving to that tile anymore.
				//pick_up_on_reach_goal = false; //Let the game know the unit isn't moving to that tile anymore.
				//mine_tile_id = 0; //Reset mine_tile_id.
				//shovelling = false; //Let the game know the unit has moved away and has stopped shovelling the tile.
				//shovel_on_reach_goal = false; //Let the game know the unit isn't moving to that tile anymore.
				move_frame = 0; //Reset this to prevent the "skip first tile in move_path" bug.


				cout << "Calculating path.\n";
				if(!get_free_neighbor_tile(Job_Que.jobs[i].tasked_tile)) //Find a free tile next to the construction.
				{
					cout << "Could not find path.\n";
					cancel_current_activity();
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
						cout << "Saving construction job.\n";

						jobs.push_back(i); //Store the index of this job.
						movepaths.push_back(move_path);

						cancel_current_activity();
					}
					else
					{
						cancel_current_activity();
					}
				}

				done = true;

				cout << "Taken job!\n";
			}
			else if(Job_Que.jobs[i].type == "drill wall" && Job_Que.jobs[i].taken == false && can_mine_wall) //Check if the job is a drill wall job.
			{
				cout << "Found drill wall job.\n";

				cancel_current_activity();

				move_destination = Job_Que.jobs[i].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.

				if(!get_free_neighbor_tile(Job_Que.jobs[i].tasked_tile)) //Make sure the unit can reach the wall.
				{
					cancel_current_activity();
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
						jobs.push_back(i); //Store the index of this job.
						movepaths.push_back(move_path);

						cout << "Saving drill job.\n";

						cancel_current_activity();
					}
					else
					{
						cancel_current_activity();
					}
				}
			}
			else if(Job_Que.jobs[i].type == "shovel rubble" && Job_Que.jobs[i].taken == false && can_shovel_rubble) //Check if the job is a shovel rubble job.
			{
				cout << "Found shovel rubble job.\n"; //Debugging output.

				cancel_current_activity();

				move = true; //Let the game know this unit is gonna move.
				move_destination = Job_Que.jobs[i].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.

				if(!calculate_path()) //Make sure the unit can reach the wall.
				{
					cancel_current_activity();
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
						jobs.push_back(i); //Store the index of this job.
						movepaths.push_back(move_path);

						cout << "Saving shovel rubble job.\n";

						cancel_current_activity();
					}
					else
					{
						cancel_current_activity();
					}
				}
			}
			else if(Job_Que.jobs[i].type == "pick up ore" && Job_Que.jobs[i].taken == false && !carrying_resource) //Check if the job is a pick up ore job.
			{
				cout << "Found pick up ore job.\n"; //Debugging output.

				cancel_current_activity();

				move = true; //Let the game know this unit is gonna move.
				move_destination = Job_Que.jobs[i].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.

				if(!calculate_path()) //Make sure the unit can reach the wall.
				{
					cancel_current_activity();
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
						jobs.push_back(i); //Store the index of this job.
						movepaths.push_back(move_path);

						cout << "Saving pick up ore job.\n";

						cancel_current_activity();
					}
					else
					{
						cancel_current_activity();
					}
				}
			}
			else if(Job_Que.jobs[i].type == "open door" && Job_Que.jobs[i].taken == false) //Check if the job is a pick up ore job.
			{
				cout << "Found open door job.\n"; //Debugging output.

				cancel_current_activity();

				move = true; //Let the game know this unit is gonna move.
				move_destination = Job_Que.jobs[i].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.

				if(!calculate_path()) //Make sure the unit can reach the wall.
				{
					cancel_current_activity();
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
						jobs.push_back(i); //Store the index of this job.
						movepaths.push_back(move_path);

						cout << "Saving open door job.\n";

						cancel_current_activity();
					}
					else
					{
						cancel_current_activity();
					}
				}
			}
			else if(Job_Que.jobs[i].type == "incide_usa" && Job_Que.jobs[i].taken == false) //Check if the job is a pick up ore job.
			{
				cout << "Found close door job.\n"; //Debugging output.

				cancel_current_activity();

				tile* destination_tile = NULL;
				destination_tile = get_free_neighbor_tile(Job_Que.jobs[i].tasked_tile); //Assign the move destination to be a neighbour of the door tile.
				if(!destination_tile) //Error checking.
				{
					cout << "Can't find path to door!\n";
					cancel_current_activity();
				}
				else
				{
					jobs.push_back(i); //Store the index of this job.
					movepaths.push_back(move_path);

					cout << "Saving open door job.\n";

					cancel_current_activity();
				}
			}
			iterator2++;
			i++;

			//cout << "movepaths.size(): " << movepaths.size() << "\n";
		}
	}

	cancel_current_activity();

	int shortest_distance = -1;
	int closest_job = 0;
	bool found = false;
	int closest_job_movepath = 0;
	//job* closest_job;

	for(int i2 = 0; i2 < jobs.size(); i2++)
	{
		if(shortest_distance == -1)
		{
			closest_job = jobs[i2];
			shortest_distance = movepaths[i2].size() - 1;
			closest_job_movepath = i2;
			found = true;

			cout << "First job.\n";
			cout << "shortest_distance = " << shortest_distance << "\n";
			cout << "closest_job = " << closest_job << "\n";
		}
		else if(movepaths[i2].size() < shortest_distance)
		{
			closest_job = jobs[i2];
			shortest_distance = movepaths[i2].size();
			closest_job_movepath = i2;
			found = true;

			cout << "Found closer job.\n";
			cout << "shortest_distance = " << shortest_distance << "\n";
		}
	}

	if(found)
	{
		cout << "closest_job: " << closest_job << "\n";
		cout << "jobs.size(): " << jobs.size() << "\n";
		cout << "Found job. Adding.\n";

		if(Job_Que.jobs[closest_job].type == "construct")
		{
			move = true;
			move_destination = Job_Que.jobs[closest_job].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.
			//move_path = movepaths[closest_job];
			move_path.clear();
			//move_path.assign(movepaths[closest_job], movepaths[closest_job] + (movepaths[closest_job].size() - 1));
			move_path = movepaths[closest_job_movepath];
			//move_path =  vec(movepaths[closest_job], movepaths[closest_job] + sizeof(movepaths[closest_job]))
			cout << "closest_job = " << closest_job << "\n";
			cout << "movepaths.size() = " << movepaths.size() << "\n";
			cout << "movepaths[closest_job][0]" << movepaths[closest_job_movepath][0] << "\n";
			//copy(movepaths[closest_job_movepath].begin(), movepaths[closest_job_movepath].end(), move_path.begin());

			Job_Que.jobs[closest_job].taken = true; //The job has been taken. Let everybody know that.
			job_state = "constructing"; //The unit is constructing something.
			my_job = new job;
			*my_job = Job_Que.jobs[closest_job]; //Let the unit know which job it's doing.
			Job_Que.jobs.erase(Job_Que.jobs.begin() + closest_job); //Remove the job from the job que.

			/*if(my_job->construction_type == "wall")
			{
				f
			}*/
		}
		else if(Job_Que.jobs[closest_job].type == "drill wall")
		{
			move = true;
			move_destination = Job_Que.jobs[closest_job].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.
			//move_path = movepaths[closest_job];
			move_path.clear();
			move_path = movepaths[closest_job_movepath];
			//move_path =  vec(movepaths[closest_job], movepaths[closest_job] + sizeof(movepaths[closest_job]))
			cout << "closest_job = " << closest_job << "\n";
			cout << "movepaths.size() = " << movepaths.size() << "\n";
			cout << "movepaths[closest_job][0]" << movepaths[closest_job_movepath][0] << "\n";
			//copy(movepaths[closest_job_movepath].begin(), movepaths[closest_job_movepath].end(), move_path.begin());

			Job_Que.jobs[closest_job].taken = true; //The job has been taken. Let everybody know that.
			job_state = "drilling"; //The unit is drilling a wall now.
			my_job = new job;
			*my_job = Job_Que.jobs[closest_job]; //Let the unit know which job it's doing.
			Job_Que.jobs.erase(Job_Que.jobs.begin() + closest_job); //Remove the job from the job que.

			mine_on_reach_goal = true; //Let the game know the unit will be mining a wall upon reaching its destination.
			mine_tile_id = my_job->tasked_tile->ID; //Let the game know which tile the unit has been commanded to mine.
		}
		else if(Job_Que.jobs[closest_job].type == "shovel rubble")
		{
			move = true;
			move_destination = Job_Que.jobs[closest_job].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.
			//move_path = movepaths[closest_job];
			move_path.clear();
			move_path = movepaths[closest_job_movepath];
			//move_path =  vec(movepaths[closest_job], movepaths[closest_job] + sizeof(movepaths[closest_job]))
			cout << "closest_job = " << closest_job << "\n";
			cout << "movepaths.size() = " << movepaths.size() << "\n";
			cout << "movepaths[closest_job][0] = " << movepaths[closest_job_movepath][0] << "\n";
			//copy(movepaths[closest_job_movepath].begin(), movepaths[closest_job_movepath].end(), move_path.begin());

			Job_Que.jobs[closest_job].taken = true; //The job has been taken. Let everybody know that.
			job_state = "shoveling"; //The unit is drilling a wall now.
			my_job = new job;
			*my_job = Job_Que.jobs[closest_job]; //Let the unit know which job it's doing.
			Job_Que.jobs.erase(Job_Que.jobs.begin() + closest_job); //Remove the job from the job que.

			shovel_on_reach_goal = true; //Let the game know the unit will be shoveling rubble upon reaching its destination.
		}
		else if(Job_Que.jobs[closest_job].type == "pick up ore")
		{
			move = true;
			move_destination = Job_Que.jobs[closest_job].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.
			move_path.clear();
			move_path = movepaths[closest_job_movepath];

			Job_Que.jobs[closest_job].taken = true; //The job has been taken. Let everybody know that.
			job_state = "picking_up"; //The unit is drilling a wall now.
			my_job = new job;
			*my_job = Job_Que.jobs[closest_job]; //Let the unit know which job it's doing.
			Job_Que.jobs.erase(Job_Que.jobs.begin() + closest_job); //Remove the job from the job que.

			pick_up_on_reach_goal = true; //Let the game know the unit will be picking up stuff upon reaching its destination.
			pick_up_object_type = 0; //Let the game know the unit is picking up ore.
		}
		else if(Job_Que.jobs[closest_job].type == "open door")
		{
			move = true;
			move_destination = Job_Que.jobs[closest_job].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.
			move_path.clear();
			move_path = movepaths[closest_job_movepath];

			Job_Que.jobs[closest_job].taken = true; //The job has been taken. Let everybody know that.
			job_state = "moving"; //The unit is drilling a wall now.
			my_job = new job;
			*my_job = Job_Que.jobs[closest_job]; //Let the unit know which job it's doing.
			Job_Que.jobs.erase(Job_Que.jobs.begin() + closest_job); //Remove the job from the job que.
		}
		else if(Job_Que.jobs[closest_job].type == "incide_usa")
		{
			move = true;
			move_destination = Job_Que.jobs[closest_job].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.
			move_path.clear();
			move_path = movepaths[closest_job_movepath];

			Job_Que.jobs[closest_job].taken = true; //The job has been taken. Let everybody know that.
			job_state = "incide_usa"; //The unit is drilling a wall now.
			my_job = new job;
			*my_job = Job_Que.jobs[closest_job]; //Let the unit know which job it's doing.
			Job_Que.jobs.erase(Job_Que.jobs.begin() + closest_job); //Remove the job from the job que.

			close_door = true; //Let the unit know it gonna be closing a door.
			close_door_tile = my_job->tasked_tile; //Let the game know which tile contains the door the unit hath been commanded to close.
		}
	}

	//cout << "Done with job.\n";

	checking_job = false;
	done_checking_job = true;

	pthread_mutex_unlock(&Job_Que.job_mutex); //Don't forget to unlock this!

	pthread_exit(NULL);
}
