/* Copyright the ORR-C Dev Team */
#pragma once
#include "../Engine.hpp"
#include "../engine/EObject.hpp"
#include "job.hpp"
using std::string;

/* --------------------------------------------------------------
 * Everything related to job que is defined here
 * ----------------------------------------------------------- */

class job;

class job_que //Job class. A job is a task for your minions to carry out.
{
public:
	std::vector<job> jobs; //Vector containing all the jobs.

	job_que(); //Constructor.
	~job_que() { } //Deconstructor.

	void add_job(job JOB); //Add a job to the job que...hehe
};
