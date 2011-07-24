/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the game object class stuff header file.
using namespace std;

/* --------------------------------------------------------------
 * Everything related to the checking for jobs it can do is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::check_job() //Give the unit something to do out of the job que.
{
	//Look through the job que until a job is found that this unit can perform.
	//TODO: Assign the closest job.

	vector<int> jobs;
	vector<vector<int> > movepaths;

	if(selected)
	{
		cout << "Checking for job.\n";
	}

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

				if(calculate_path() == false) //If it can't calculate find a path...
				{
					cancel_current_activity();
				}

				else
				{
					/*Job_Que.jobs[i].taken = true; //The job has been taken. Let everybody know that.
					job_state = "constructing"; //The unit is constructing something.
					//my_job = &Job_Que.jobs[i]; //Let the unit know which job it's doing.
					my_job = new job;
					*my_job = Job_Que.jobs[i]; //Let the unit know which job it's doing.
					Job_Que.jobs.erase(Job_Que.jobs.begin() + i); //Remove the job from the job que.
					*/

					jobs.push_back(i); //Store the index of this job.
					movepaths.push_back(move_path);

					cancel_current_activity();
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
					/*Job_Que.jobs[i].taken = true; //The job has been taken. Let everybody know that.
					job_state = "drilling"; //The unit is drilling a wall now.
					my_job = new job;
					*my_job = Job_Que.jobs[i]; //Let the unit know which job it's doing.
					Job_Que.jobs.erase(Job_Que.jobs.begin() + i); //Remove the job from the job que.

					mine_on_reach_goal = true; //Let the game know the unit will be mining a wall upon reaching its destination.
					mine_tile_id = my_job->tasked_tile->ID; //Let the game know which tile the unit has been commanded to mine.*/

					jobs.push_back(i); //Store the index of this job.
					movepaths.push_back(move_path);

					cancel_current_activity();
				}
			}
			else if(Job_Que.jobs[i].type == "shovel rubble" && Job_Que.jobs[i].taken == false && can_shovel_rubble) //Check if the job is a drill wall job.
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
					/*Job_Que.jobs[i].taken = true; //The job has been taken. Let everybody know that.
					job_state = "shoveling"; //The unit is drilling a wall now.
					my_job = new job;
					*my_job = Job_Que.jobs[i]; //Let the unit know which job it's doing.
					Job_Que.jobs.erase(Job_Que.jobs.begin() + i); //Remove the job from the job que.

					shovel_on_reach_goal = true; //Let the game know the unit will be shoveling rubble upon reaching its destination.*/

					jobs.push_back(i); //Store the index of this job.
					movepaths.push_back(move_path);

					cout << "move_path.size(): " << move_path.size() << "\n";

					cancel_current_activity();
				}
			}
			iterator2++;
			i++;
		}
	}

	int shortest_distance = -1;
	int closest_job = 0;
	bool found = false;

	for(int i2 = 0; i2 < jobs.size(); i2++)
	{
		if(shortest_distance == -1)
		{
			closest_job = jobs[i2];
			shortest_distance = movepaths[i2].size();
			found = true;

			cout << "First job.\n";
		}
		else if(movepaths[i2].size() < shortest_distance)
		{
			closest_job = jobs[i2];
			shortest_distance = movepaths[i].size();
			found = true;

			cout << "Found closer job.\n";
		}
	}

	if(found)
	{
		cout << "Found job. Adding.\n";

		if(Job_Que.jobs[closest_job].type == "construct")
		{
			move = true;
			move_destination = Job_Que.jobs[closest_job].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.
			move_path = movepaths[closest_job];

			Job_Que.jobs[closest_job].taken = true; //The job has been taken. Let everybody know that.
			job_state = "constructing"; //The unit is constructing something.
			my_job = new job;
			*my_job = Job_Que.jobs[closest_job]; //Let the unit know which job it's doing.
			Job_Que.jobs.erase(Job_Que.jobs.begin() + closest_job); //Remove the job from the job que.
		}
		else if(Job_Que.jobs[closest_job].type == "drill wall")
		{
			move = true;
			move_destination = Job_Que.jobs[closest_job].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.
			move_path = movepaths[closest_job];

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
			move_path = movepaths[closest_job];

			Job_Que.jobs[closest_job].taken = true; //The job has been taken. Let everybody know that.
			job_state = "shoveling"; //The unit is drilling a wall now.
			my_job = new job;
			*my_job = Job_Que.jobs[closest_job]; //Let the unit know which job it's doing.
			Job_Que.jobs.erase(Job_Que.jobs.begin() + closest_job); //Remove the job from the job que.

			shovel_on_reach_goal = true; //Let the game know the unit will be shoveling rubble upon reaching its destination.
		}
	}
}
