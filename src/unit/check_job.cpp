/* Copyright the ORR-C Dev Team */
#include "unit.hpp" //Blablabla, include the game object class stuff header file.
using namespace std;

/* --------------------------------------------------------------
 * Everything related to the checking for jobs it can do is defined here.
 * ----------------------------------------------------------- */

void bClassUnit::check_job() //Give the unit something to do out of the job que.
{
	//TODO: Look through the job que until a job is found that this unit can perform.

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
					move = false; //Tell the unit it doesn't have anywhere to go.
					move_destination = 0; //Reset the unit's move destination.
					move_frame = 0; //Reset this to prevent the "skip first tile in move_path" bug.
				}

				else
				{
					Job_Que.jobs[i].taken = true; //The job has been taken. Let everybody know that.
					job_state = "constructing"; //The unit is constructing something.
					//my_job = &Job_Que.jobs[i]; //Let the unit know which job it's doing.
					my_job = new job;
					*my_job = Job_Que.jobs[i]; //Let the unit know which job it's doing.
					Job_Que.jobs.erase(Job_Que.jobs.begin() + i); //Remove the job from the job que.
				}

				done = true;

				cout << "Taken job!\n";
			}
			else if(Job_Que.jobs[i].type == "drill wall" &&Job_Que.jobs[i].taken == false && can_mine_wall) //Check if the job is a drill wall job.
			{
				cout << "Found drill job.\n";

				cancel_current_activity();

				move_destination = Job_Que.jobs[i].tasked_tile->ID; //move_destination is the index in the map array of the tile that the unit has to move to.

				if(!get_free_neighbor_tile(Job_Que.jobs[i].tasked_tile)) //Make sure the unit can reach the wall.
				{
				}
				else
				{
					Job_Que.jobs[i].taken = true; //The job has been taken. Let everybody know that.
					job_state = "drilling"; //The unit is drilling a wall now.
					my_job = new job;
					*my_job = Job_Que.jobs[i]; //Let the unit know which job it's doing.
					Job_Que.jobs.erase(Job_Que.jobs.begin() + i); //Remove the job from the job que.

					mine_on_reach_goal = true; //Let the game know the unit will be mining a wall upon reaching its destination.
					mine_tile_id = my_job->tasked_tile->ID; //Let the game know which tile the unit has been commanded to mine.
				}
			}
			iterator2++;
			i++;
		}
	}
}
