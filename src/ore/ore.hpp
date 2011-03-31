/* Copright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Everything related to ore is defined here
 * ----------------------------------------------------------- */

#pragma once
#include "../engine/EObject.hpp"

class tile;

class ore //It's Ore. Remember, there's not simply "ore". But there's "Iron Ore", "Copper Ore", etc.
{
public:
	std::string name; //Um...The ore's name...
	int matter_value; //A building requires x matter. This ore provides x matter. Change this later...
	int type_id; //Let's the game know what type of ore this is...
	SDL_Surface *sprite; //The ore's sprite.
	tile *containing_tile; //Points to the tile that this ore is laying on.

	void init(int ID, int MATTER_VALUE, SDL_Surface *SPRITE, std::string NAME); //Initialize a new ore/ore type.

	ore(); //Constructor. Initializes an empty ore.
	~ore() //Deconstructor.
	{
		sprite = NULL;
	}
};

class ore_manager //Manages all the base types of ore.
{
public:
	std::vector<ore> ore_list; //All the ore types are stored in this vector.

	void add_ore_type(int ID, int MATTER_VALUE, SDL_Surface *SPRITE, std::string NAME); //Add a new ore type.
	bool load_types_from_file(std::string filepath); //Loads all the ore types from the files...
	bool load_ore(std::string folderpath); //Adds a new type with the data it got out of the specified folder.
	ore get_by_id(int ID); //Returns a copy of the ore type that has the specified ID.
};
