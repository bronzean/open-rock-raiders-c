/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Everything related to tiles is defined here
 * ----------------------------------------------------------- */

#pragma once
#include "../engine/EObject.hpp"

class bClassUnit;
class ore;
class energy_crystal;
class animation;
class construction;

class tile
{
public:
	int wx, wy, layer; //The position of the tile.
	int plane;

	SDL_Surface *sprite; //The tile's sprite

	int width, height;//The width and the height of the object. It is obtained from the width and and the height of the image.

	int type_id; //The type of tile this is.
	int ID; //The location of this tile in the map array.

	std::vector<bClassUnit> unitlist; //The units on this tile

	std::string temp; //Um...Used for stuff

	int new_tile; //The location in the map array of the tile the unit will be moving to.

	bool ramp; //Let's the game know whether or not this tile is a ramp that connects two caverns.
	bool up_ramp; //Let's the game know where it leads.
	bool down_ramp; //Let's the game know where it leads.

	bool wall; //Is it a wall?
	bool self_supporting; //Does the wall support itself? As in, doesn't collapse if it's not connected to enough walls/not connected in the right way. False = The way it is in RR. True = Doesn't have ot be connected to any other walls.
	bool generate_ore_on_mine; //Does this tile generate ore when it is mined?
	int ore_type; //What type of ore does this tile generale when mined, if it can be mined?
	bool can_mine; //Can this wall be mined?
	int minimumn_mining_power; //The minimumn power a drill need to be able to mine this wall.

	bool air; //Is this an air tile?

	std::string name; //The tile's name.

	bool turn_to_ground; //Does it turn into a ground tile when it is mined?
	int ground_type; //The ID of the ground tile it turns into when mined.

	std::vector<ore> orelist; //Contains a list of all the ore on this tile.
	std::vector<ore>::iterator iterator; //Used for navigating the ore list
	std::vector<energy_crystal> energy_crystal_list; //Contains a list of all the energy crystals on this tile.
	int num_ore_to_generate; //The number of ore to generate when this tile is mined.
	std::vector<int> health; //How much health the tile's got. When it reaches <= 0, it "collapses". If it's a wall. So, it's used for landslides and drilling. - Yay, this has been expanded to mining.

	bool tree; //Is this tile tile a tree?
	bool generate_wood_on_chop; //Does this tile generate wood when it is chopped.

	bool important; //Is this tile important? Importance is used in updating tiles, and other stuff.
	int Active_Map_Entry; //This tile's location in Active_Map. A value of -1 means it has no entry in Active_Map.

	bool rubble; //Is this tile a rubble tile?
	std::vector<int> ore_gen_ids; //A vector containing a list of the IDs of the types of ores it can generate. For weights, simply add multiple copies of that ID. TODO: Change this to be used with walls too! Much better than a wall creating only one ore type!
	/*int health_per_shovel; //How much health has to be reduced to be considered "one shovel". OBSOLETE */
	int num_shovels; //How many shovels are left before the rubble is cleared and it turns into a ground tile. This number is determined by the ammount of calues passed to health in the config files...This also doubles over for mining.
	int total_shovels; //The total number of shovels and drills.


	std::vector<animation> animations; //Stores all of the tile's animations.
	bool drilling_animation; //Does the tile have an animation that plays while it is getting drilled?
	int drilling_animation_entry; //Stores the index of the drilling animation's entry in the animations vector.
	bool active_animation; //Is an animation currently going on?
	int active_animation_entry; //The entry of the active animation in the animations vector.

	construction *local_construction; //The construction that's on this tile
	bool has_construction; //Does this tile have a construction present on it?

	bool obstruction; //Is this tile an obstruction? Wall tiles, for example, are obstructions.

	tile(); //Constructor. Initialize an empty tile.
	~tile() //Deconstructor.
	{
	}

	void init(int ID, SDL_Surface *SPRITE, std::string NAME, bool WALL, bool RAMP, bool UP_RAMP, bool DOWN_RAMP, bool SELF_SUPPORTING, int ORE_TYPE, bool CAN_MINE, int MINIMUMN_MINING_POWER, bool AIR, bool TURN_TO_GROUND, int GROUND_TYPE, bool GENERATE_ORE_ON_MINE, int NUM_ORE_TO_GENERATE/*, std::vector<int> HEALTH*/, bool TREE, bool RUBBLE/*, int HEALTH_PER_SHOVEL*/); //Initialize the tile...
	void update();
	void move_unit(int i); //Called by the update function...
	void set_sprite(std::string sprite_path);
	void draw_sprite();
	int get_wx();
	int get_wy();
	void set_wx(int WX);
	void set_wy(int WY);
	int get_width();
	int get_height();

	void mine_to_ground(int i); //Change the tile to a ground tile.
	void chop_to_ground(int i); //Changes a tree to a ground tile.
	void rubble_to_ground(int i); //Changes a rubble tile to a ground tile.

	void construct_construction(construction c_type); //Creates a construction here.
};

class tile_manager //Manages all the base types of tiles.
{
public:
	std::vector<tile> tile_list; //All the tile types are stored in this vector.

	void add_tile_type(int ID, SDL_Surface *SPRITE, std::string NAME, bool WALL, bool RAMP, bool UP_RAMP, bool DOWN_RAMP, bool SELF_SUPPORTING, int ORE_TYPE, bool CAN_MINE, int MINIMUMN_MINING_POWER, bool AIR, bool TURN_TO_GROUND, int GROUND_TYPE, bool GENERATE_ORE_ON_MINE, int NUM_ORE_TO_GENERATE/*, std::vector<int> HEALTH*/, bool TREE, bool RUBBLE/*, int HEALTH_PER_SHOVEL*/); //Add a new tile type.
	bool load_types_from_file(std::string filepath); //Loads all the tile types from the files...
	bool load_tile(std::string folderpath); //Adds a new type with the data it got out of the specified folder.
	tile get_by_id(int ID); //Returns a copy of the tile type that has the specified ID.

	tile_manager() { }
	~tile_manager();
};
