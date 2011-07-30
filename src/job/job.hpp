/* Copyright the ORR-C Dev Team */
#pragma once
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
	bool taken; //Is the job being done by another unit?
	int construction_health; //Ya, same old health system. Once this reaches 0, the construction is done and BOB the builder can go home. TODO: Unhardcode, of course.
	int build_time; //Used in constructing constructions.
	animation *_animation; //Pointer to the animation associated with this job.

	job(); //Constructor.
	~job() { } //Deconstructor.
	bool compare(job *JOB); //Returns true if the two jobs are one and same.
	void nullify(); //Similar to "job JOB = NULL;"
};
