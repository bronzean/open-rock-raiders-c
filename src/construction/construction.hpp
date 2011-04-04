/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Everything related to the constructions/buildings/bases is defined here
 * ----------------------------------------------------------- */

#pragma once
#include "../engine/EObject.hpp"

class construction //It's a construction. Most basic piece of a building.
{
public:
	std::string name; //The name of this construction.
	bool wall; //Is it a wall?
	bool floor; //Is it a floor?
	int type_id; //Let's the game know what type it is.
	SDL_Surface *sprite; //The construction's sprite.

	void init(std::string NAME, bool WALL, bool FLOOR, int TYPE_ID, std::string SPRITE); //Initalize a new construction type.

	construction(); //Constructor. Initializes an empty construction.
	~construction() //Deconstructor.
	{
	}
};

static construction c_wall; //Wall construction.
