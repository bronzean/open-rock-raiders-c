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
	bool door; //Is it a door?
	int type_id; //Let's the game know what type it is.
	SDL_Surface *sprite; //The construction's sprite.

	void init(std::string NAME, bool WALL, bool FLOOR, bool DOOR, int TYPE_ID, std::string SPRITE); //Initalize a new construction type.

	void copy_from(construction Construction); //Give this tile the properties of the one being copied.

	construction(); //Constructor. Initializes an empty construction.
	~construction() //Deconstructor.
	{
	}
};

extern construction c_wall; //Wall construction.
extern construction c_floor; //Floor construction.
extern construction c_door; //Door construction.
