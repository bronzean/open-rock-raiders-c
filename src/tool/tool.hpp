/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Everything related to tools is defined here
 * ----------------------------------------------------------- */

#pragma once
#include "../engine/EObject.hpp"

class tool //It's a tool. What else is there to say?
{
public:
	std::string name; //Name of the tool.
	int type_id; //Let's the game know what type of tool it is...

	bool is_tool; //Is it a tool? Can be a tool AND a weapon.
	bool is_weapon; //Is it a weapon? Can be a tool AND a weapon.

	bool can_drill_ground; //Can it drill through ground?

	int default_damage; //The default damage it causes. 0 = doesn't do any damage...

	bool jetpack; //Is it a jetpack?
	int jetpack_duration; //How many moves does it allow the unit to hover?

	bool can_drill_wall; //Can it drill walls?
	int drill_rate; //How long it takes to drill a tile.
	int drill_ground_time; //How long it takes to drill ground. TODO: Implement this.
	int drill_power; //If this is greater than or equal to a wall's minimumn required mining power, then this tool can drill that wall!

	bool can_chop_tree; //Can it chop trees?

	//Rubble stuff.
	bool can_clear_rubble; //Can it clear rubble?
	int default_rubble_damage; //The default damage it causes to rubble. 0 = doesn't do any damage...
	int shovel_rate; //Affects how long it takes to shovel rubble.
	int shovel_power; //If this is greater than or equal to a rubble's minimumn required shovelling power, then this tool can shovel that rubble!
	int rubble_clear_time; //How long it takes to clear rubble. TODO: Implement this.

	SDL_Surface *sprite; //The object's sprite. Used when it is laying around in the level.
	SDL_Surface *icon_sprite; //The object's icon's sprite. Used in the UI.

	tool(); //Constructor. Initialize an empty tool.
	~tool() //Deconstructor.
	{
	}

	void init(int ID, bool IS_TOOL, bool IS_WEAPON, bool CAN_DRILL_WALL, bool CAN_DRILL_GROUND, bool CAN_CLEAR_RUBBLE, int DEFAULT_DAMAGE, bool JETPACK, int JETPACK_DURATION, SDL_Surface *ICON_SPRITE, int DRILL_RATE, int DRILL_POWER, bool CAN_CHOP_TREE, int DEFAULT_RUBBLE_DAMAGE, int SHOVEL_RATE, int SHOVEL_POWER); //Initialize a new tool/tool type..
};

class tool_manager //All the tool base types...
{
public:
	std::vector<tool> tool_list; //All the ore types are stored in this vector.

	void add_tool_type(int ID, bool IS_TOOL, bool IS_WEAPON, bool CAN_DRILL_WALL, bool CAN_DRILL_GROUND, bool CAN_CLEAR_RUBBLE, int DEFAULT_DAMAGE, bool JETPACK, int JETPACK_DURATION, SDL_Surface *ICON_SPRITE, int DRILL_RATE, int DRILL_POWER, bool CAN_CHOP_TREE, int DEFAULT_RUBBLE_DAMAGE, int SHOVEL_RATE, int SHOVEL_POWER); //Add a new tool type.
	bool load_types_from_file(std::string filepath); //Loads all the ore types from the files...
	bool load_tools(std::string folderpath); //Adds a new type with the data it got out of the specified folder.
	tool get_by_id(int ID); //Returns a copy of the ore type that has the specified ID.

	tool_manager() { }
	~tool_manager()
	{
		std::cout << "Freeing the tool types' sprites\n";
		for(int i = 0; i < tool_list.size(); i++) //Free all the sprites.
		{
			SDL_FreeSurface(tool_list[i].sprite);
			SDL_FreeSurface(tool_list[i].icon_sprite);
		}
	}
};
