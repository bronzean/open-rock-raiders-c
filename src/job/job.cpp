/* Copyright the ORR-C Dev Team */
#include "job.hpp"
using namespace std;

/* --------------------------------------------------------------
 * Everything related to jobs is defined here
 * ----------------------------------------------------------- */

job::job() //Constructor.
{
	type = "";
	construction_type = "";
	tasked_tile = NULL;
	taken = false;
	construction_health = 100;
	build_time = 0;
	_animation = NULL;
}

bool job::compare(job *JOB)
{
	bool good = true;

	job *_job = new job;
	_job = *&JOB;

	//if(!type.compare(JOB->type)) good = false;
	//else if(!construction_type.compare(JOB->construction_type)) good = false;
	//else if(tasked_tile != JOB->tasked_tile) good = false;
	//else if(taken != JOB->taken) good = false;
	//else if(construction_health != JOB->construction_health) good = false;

	//cout << "In compare.\n";
	//cout << "this->type = " << type << " and JOB->type = " << *&JOB->type << "\n";
	//cout << "this->construction_type = " << construction_type << "and JOB->construction_type = " << JOB->construction_type << "\n";
	//cout << "this->tasked_tile->ID = " << tasked_tile->ID << " and JOB->tasked_tile->ID = " << JOB->tasked_tile->ID << "\n";
	//cout << "this->taken = " << taken << " and JOB->taken = " << JOB->taken << "\n";
	//cout << "this->construction_health = " << construction_health << " and JOB->construction_health = " << JOB->construction_health << "\n";

	cout << "In compare.\n";
	//cout << "this->type = " << type << " and JOB->type = " << (string)_job->type << "\n";
	//cout << "this->construction_type = " << construction_type << " and JOB->construction_type = " << (string)_job->construction_type << "\n";
	//cout << "this->tasked_tile->ID = " << tasked_tile->ID << " and JOB->tasked_tile->ID = " << _job->tasked_tile->ID << "\n";
	//cout << "this->taken = " << taken << " and JOB->taken = " << _job->taken << "\n";
	//cout << "this->construction_health = " << construction_health << " and JOB->construction_health = " << _job->construction_health << "\n";


	cout << "this->type = " << type << " and JOB->type = " << (string)JOB->type << "\n";
	cout << "this->construction_type = " << construction_type << " and JOB->construction_type = " << (string)JOB->construction_type << "\n";
	cout << "this->tasked_tile->ID = " << tasked_tile->ID << " and JOB->tasked_tile->ID = " << JOB->tasked_tile->ID << "\n";
	cout << "this->taken = " << taken << " and JOB->taken = " << _job->taken << "\n";
	cout << "this->construction_health = " << construction_health << " and JOB->construction_health = " << JOB->construction_health << "\n";

	//if(!type.compare((string)_job->type)) return false;
	//if(!construction_type.compare((string)_job->construction_type)) return false;
	if(type != (string)_job->type) { cout << "Types not matching.\n"; return false; }
	if(construction_type != (string)_job->construction_type) { cout << "Construction types not matching.\n"; return false; }
	if(tasked_tile != _job->tasked_tile) { cout << "Tasked tiles not matching.\n"; return false; }
	if(taken != _job->taken) { cout << "Takens not matching.\n"; return false; }
	if(construction_health != _job->construction_health) { cout << "Construction healths not matching.\n"; return false; }

	return true;
}

void job::nullify()
{
	type = "";
	construction_type = "";
	tasked_tile = NULL;
	taken = false;
	construction_health = 0;
	build_time = 0;
	_animation = NULL;
}
