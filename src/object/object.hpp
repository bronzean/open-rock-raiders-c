/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Everything related to objects is defined here
 * ----------------------------------------------------------- */

#pragma once
#include "../engine/EObject.hpp"

class object //It's an object. What else is there to say?
{
public:
	std::string name; //Name of the tool.
	int type_id; //Let's the game know what type of object it is...

	bool can_drill_ground; //Can it drill down through the ground? Only reason it wouldn't be able to drill ground, if it can drill walls, is if it couldn't be put into such a position by the unit.

	int default_damage; //The default damage it causes. 0 = doesn't do any damage...
	//int final_damage; //The final damage the object causes.

	bool jetpack; //Can it be used as a jetpack?
	int jetpack_fuel; //How much fuel does the jetpack have? More fuel = can be used longer.
	int jetpack_fuel_consumption; //How much fuel does it use per frame? More consumption = less flying.

	bool can_drill_wall; //Can it drill walls? Only reason it wouldn't be able to drill walls, if it can drill ground, is if it can't be hoisted vertically or something by the unit.
	int drill_rate; //Influences how long it takes to drill a tile.
	int drill_power; //If this is greater than or equal to a wall/ground's minimumn required mining power, then this tool can drill that wall/ground!

	bool can_chop_tree; //Can it chop down trees?
	int chop_rate; //Influences how long it takes to chop down a tree.
	int chop_power; //If this is greater than or equal to a tree's minimumn required chopping power, then this tool can chop that tree!

	//Rubble stuff.
	bool can_clear_rubble; //Can it clear rubble?
	int default_rubble_damage; //The default damage it causes to rubble. 0 = doesn't do any damage...Which means it can't actually clear rubble.
	//int shovel_rate; //Affects how long it takes to shovel rubble.
	int shovel_power; //If this is greater than or equal to a rubble's minimumn required shovelling power, then this tool can shovel that rubble!

	SDL_Surface *sprite; //The object's sprite. Used when it is laying around in the level.
	SDL_Surface *icon_sprite; //The object's icon's sprite. Used in the UI and such.

	object(); //Constructor. Initialize an empty tool.
	~object() //Deconstructor.
	{
	}

	//void init(int ID, bool IS_TOOL, bool IS_WEAPON, bool CAN_DRILL_WALL, bool CAN_DRILL_GROUND, bool CAN_CLEAR_RUBBLE, int DEFAULT_DAMAGE, bool JETPACK, int JETPACK_DURATION, SDL_Surface *ICON_SPRITE, int DRILL_RATE, int DRILL_POWER, bool CAN_CHOP_TREE, int DEFAULT_RUBBLE_DAMAGE, int SHOVEL_RATE, int SHOVEL_POWER); //Initialize a new object/object type..
};

class object_manager //All the object base types...
{
public:
	std::vector<object> object_list; //All the object types are stored in this vector.

	//void add_object_type(int ID, bool IS_TOOL, bool IS_WEAPON, bool CAN_DRILL_WALL, bool CAN_DRILL_GROUND, bool CAN_CLEAR_RUBBLE, int DEFAULT_DAMAGE, bool JETPACK, int JETPACK_DURATION, SDL_Surface *ICON_SPRITE, int DRILL_RATE, int DRILL_POWER, bool CAN_CHOP_TREE, int DEFAULT_RUBBLE_DAMAGE, int SHOVEL_RATE, int SHOVEL_POWER); //Add a new object type.
	void add_object_type(object Object); //Add a new object type.
	bool load_types_from_file(std::string filepath); //Loads all the object types from the files...
	bool load_objects(std::string folderpath); //Adds a new type with the data it got out of the specified folder.
	object get_by_id(int ID); //Returns a copy of the object type that has the specified ID.

	object_manager() { }
	~object_manager()
	{
		std::cout << "Freeing the object types' sprites\n";
		for(int i = 0; i < object_list.size(); i++) //Free all the sprites.
		{
			SDL_FreeSurface(object_list[i].sprite);
			SDL_FreeSurface(object_list[i].icon_sprite);
		}
	}
};
