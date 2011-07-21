/* Copyright the ORR-C Dev Team */
#pragma once
#include "../main.hpp"
#include "../Engine.hpp"

class location2d //Pretty much a wrapper for x and y.
{
public:
	int x;
	int y;

	location2d(); //Constructor.
	~location2d(); //Deconstructor.
};

class location3d //Pretty much a wrapper for x, y, z.
{
	int x;
	int y;
	int z;

	location3d(); //Constructor.
	~location3d(); //Deconstructor.
};

class location4d //Pretty much a wrapper for x, y, z, layer.
{
public:
	int x;
	int y;
	int z;
	int layer;

	location4d(); //Constructor.
	~location4d(); //Deconstructor.
};
