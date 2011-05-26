/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Everything related to energy crystals are defined here
 * ----------------------------------------------------------- */

#pragma once
#include "../engine/EObject.hpp"

class energy_crystal //It's Energy Crystals. Remember, there's not simply "Energy Crystal". But there's "Green Energy Crystal", "Red Energy Crystal", etc.
{
public:
	std::string name; //The name of the energy crystal.
	int energy_production_rate; //The energy production rate of the energy crystal.
	int type_id; //Let's the game know what type of energy crystal this is.
	SDL_Surface *sprite; //The energy crystal's sprite.

	void init(int ID, int ENERGY_PRODUCTION_RATE, SDL_Surface *SPRITE, std::string NAME); //Initalize a new energy crystal/energy crystal type.

	energy_crystal(); //Constructor. Initializes an empty energy crystal.
	~energy_crystal() //Deconstructor.
	{
	}
};

class energy_crystal_manager //Manages all the energy crystal types.
{
public:
	std::vector<energy_crystal> energy_crystal_list; //All the energy crystal types are stored in this vector.

	void add_energy_crystal_type(int ID, int ENERGY_PRODUCTION_RATE, SDL_Surface *SPRITE, std::string NAME); //Add a new energy crystal type.
	bool load_types_from_file(std::string filepath); //Loads all the energy crystal types from the files...
	bool load_energy_crystal(std::string folderpath); //Adds a new type with the data it got out of the specified folder.
	energy_crystal get_by_id(int ID); //Returns a copy of the energy crystal type that has the specified ID.

	energy_crystal_manager() { } //The constructor.
	~energy_crystal_manager() //The deconstructor.
	{
		std::cout << "Freeing the energy crystal types' sprites\n";
		for(int i = 0; i < energy_crystal_list.size(); i++) //Free all the sprites.
		{
			SDL_FreeSurface(energy_crystal_list[i].sprite);
		}
	}
};
