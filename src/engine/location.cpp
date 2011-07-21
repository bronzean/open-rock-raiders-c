/* Copyright the ORR-C Dev Team */
#pragma once
#include "location.hpp"
using namespace std;


location2d::location2d() //Constructor.
{
	x = 0;
	y = 0;
}

location2d::~location2d() //Deconstructor.
{
}

location3d::location3d() //Constructor.
{
	x = 0;
	y = 0;
	z = 0;
}

location3d::~location3d() //Deconstructor.
{
}

location4d::location4d() //Constructor.
{
	x = 0;
	y = 0;
	z = 0;
	layer = 0;
}

location4d::~location4d() //Deconstructor.
{
}
