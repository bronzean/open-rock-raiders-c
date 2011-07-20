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

	bool door; //Is it a door?
	bool door_locked; //Is the door locked?
	bool door_open; //Is the door currently open?
	int door_strength; //What is the strength of the door? Used to calculate how easy it is for a monsters to force it open.
	bool door_open_animation; //Does the door have an animation that plays when it's opened?
	bool door_close_animation; //Does the door have an animation that plays when it's closed?
	int door_open_animation_entry; //Stores the index of the door opening animation's entry in the animations vector.
	int door_close_animation_entry; //Stores the index of the door closing animation's entry in the animations vector.
	int door_open_time; //How many frames it takes for the door to open. If using animations, then 

	std::vector<animation> animations; //Stores all of the tile's animations.
	bool active_animation; //Is an animation currently going on?
	int active_animation_entry; //The entry of the active animation in the animations vector.

	void init(std::string NAME, bool WALL, bool FLOOR, bool DOOR, int DOOR_STRENGTH, int TYPE_ID, std::string SPRITE); //Initalize a new construction type.

	void copy_from(construction Construction); //Give this tile the properties of the one being copied.

	construction(); //Constructor. Initializes an empty construction.
	~construction() //Deconstructor.
	{
	}
};

extern construction c_wall; //Wall construction.
extern construction c_floor; //Floor construction.
extern construction c_door; //Door construction.

extern bool construction_location_select;
extern bool construction_wall_location_select; //Is the game waiting for the user to select where to place wall the construction?
extern bool construction_door_location_select; //Is the game waiting for the user to select where to place door the construction?

extern std::string choose_wall_location_str;
extern SDL_Surface* choose_wall_location_spr;

extern std::string choose_door_location_str;
extern SDL_Surface* choose_door_location_spr;
