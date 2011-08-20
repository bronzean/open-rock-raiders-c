/* Copyright the ORR-C Dev Team */
#include "job_que.hpp"
using namespace std;

/* --------------------------------------------------------------
 * Everything related to the job_que is defined here
 * ----------------------------------------------------------- */

job_que::job_que() //Constructor.
{
	pthread_mutex_init(&job_mutex, NULL); //Initialize this.
}

job_que::~job_que() //Deconstructor.
{
	pthread_mutex_destroy(&job_mutex);
}

void job_que::add_job(job JOB)
{
	//jobs.push_back(*&JOB);
	jobs.push_back(JOB);
}

job_que Job_Que;
