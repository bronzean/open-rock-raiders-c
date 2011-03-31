/* Copyright the ORR-C Dev Team */
#include "../Engine.hpp"
#include "../engine/EObject.hpp"
using std::string;

/* --------------------------------------------------------------
 * Everything related to jobs is defined here
 * ----------------------------------------------------------- */

class job //Job class. A job is a task for your minions to carry out.
{
public:
	string type; //The type of job.
	string construction_type; //If it is a construction job, what type of construction is being made?
	tile *tasked_tile; //Pointer to the tile that involves this task.

	job(); //Constructor.
	~job() { } //Deconstructor.
};
