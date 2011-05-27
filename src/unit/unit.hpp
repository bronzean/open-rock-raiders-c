/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Everything related to the constructions/buildings/bases is defined here
 * ----------------------------------------------------------- */

#pragma once
#include "../engine/EObject.hpp"

class tool;
class ore;
class energy_crystal;
class animation;
class job;
class tile;

//This is the blase class of all the units that the game will be using
class bClassUnit
{
public:
	//The world x and the world y.
	int wx, wy;
	//It's z-level
	int wz;
	//The layer it's on
	int layer;
	//The speed the unit moves at
	int move_speed;
	//The max health
	int m_health;
	//The current health
	int c_health;
	//The object's sprite
	SDL_Surface *sprite;
	SDL_Surface *sprite_select; //This is the sprite that is used when the object is selected.
	//The width and the height of the object. It is obtained from the width and and the height of the image.
	int width, height;
	//Is the unit selectable?
	bool selectable;
	//Is the unit sellected?
	bool selected;
	//The name of the unit.
	std::string name;
	//The file extension of the sprite's image
	std::string spr_extend;
	//Draw with a color key?
	bool color_key;
	//This is the object's position in the list of all objects.
	int que_num; //NOTE: UNUSED.
	//The tile to move to
	int move_destination;
	//The tile to move to. This means it first has to move to a ramp tile.
	int move_destination_ramp;
	//Move up or down a layer when you reach the ramp?
	int move_layer_ramp; //0 = move down, 1 = move up.
	//If true, the unit is moving somewhere. If false, the unit isn't going anywhere.
	bool move;
	//If true, check if there is need for a ramp, then find the ramp. If false, that was already done.
	bool calculate_need_ramp;
	//If false, the unit can not move along x anymore.
	bool xmove;
	//If false, the unit can not move along y anymore.
	bool ymove;
	//The frame it last moved in
	int move_frame;
	//The frame it last was drawn in
	int draw_frame;
	//Contains a list of the indexes of all the tiles the raider needs to move to to reach it's goal.
	std::vector<int> move_path;
	//Does the unit's path need to be calculated?
	bool need_path;
	//Contains all the tools that the raider is carrying
	std::vector<tool> tool_list;
	//Is the unit hovering?
	bool hovering;
	//For how many more frames is the unit going to hover?
	int hover_duration;
	//Contains the message: "Carrying: "
	std::string carrying_message_string;
	SDL_Surface *carrying_message_sprite;
	//All the ore the unit is carrying
	std::vector<ore> ore_list;
	//All the energy crystals the unit is carrying.
	std::vector<energy_crystal> energy_crystal_list;
	//If it's carrying an ore or energy crystal, set this to true, so that it doesn't pick up any others...
	bool carrying_resource;
	std::vector<tool>::iterator iterator; //Used for navigating the tool list
	std::vector<ore>::iterator iterator2; //Used for navigating the ore list
	std::vector<energy_crystal>::iterator iterator3; //Used for navigating the energy crystal
	bool mining_mode; //Used in the mining code.
	int mine_tile_id; //The ID of the tile the unit needs to mine.
	bool mine_on_reach_goal; //Is the unit moving somewhere to mine a tile.
	std::string select_wall_to_mine_str; //A message that is displayed when the player wants to select a wall to mine.
	SDL_Surface *select_wall_to_mine_spr; //A message that is displayed when the player wants to select a wall to mine.
	bool mining; //Is the unit currently mining a tile? Used in drill times.
	bool allow_move; //Is the unit allowed to move?
	int frames_since_last_move; //The number of frames that have passed since the last move.
	std::string mining_message_str; //A message that is displayed while the unit is mining.
	SDL_Surface *mining_message_spr; //A message that is displayed while the unit is mining.
	int type_id; //The unit's type.
	bool allow_deselect; //Allow the unit to be deselected?
	bool pick_up_on_reach_goal; //Is the unit moving somewhere to pick up something?
	bool pick_up_mode; //Is the unit waiting for the player to specify what it's going to be picking up?
	int pick_up_object_type; //The type of object the unit is picking up. -1 = not picking up anything. 0 = ore. 1 = Energy Crystal. 2 = tool.
	int pick_up_stage; //Used in the check_pick_up_command function.
	std::string status; //What's it doing? IDLE = not doing anything. Check the ai related files for the rest of the status stuff.
	bool ai_pick_up_ore; //Is the unit allowed to automatically pick up ore?
	std::string select_object_to_pick_up_str; //Used in the "Select object to pick up" stuff.
	SDL_Surface *select_object_to_pick_up_spr; //Used in the "Select object to pick up" stuff.
	bool player; //Is this the player?
	std::string update_return; //Used in update functio...Tells the caller stuff.
	std::string chopping_message_str; //A message that is displayed while the unit is chopping.
	SDL_Surface *chopping_message_spr; //A message that is displayed while the unit is chopping.
	bool chop_on_reach_goal; //Is the unit going to chop down a tree?
	bool chopping; //Is the unit currently chopping a tree?
	bool chop_mode; //Is the game waiting for the player to select a tree to kill?
	std::string select_tree_to_chop_str; //Displayed when the player is selecting a tree to kill.
	SDL_Surface *select_tree_to_chop_spr; //Displayed when the player is selecting a tree to kill.
	bool shovel_on_reach_goal; //Will the unit be shovelling stuff when it reaches its goal?svn add --depth=infinity * --force
	bool shovelling; //Is the unit currently shovelling something?
	bool shovel_mode; //Is the game waiting for the player to select some rubble to shovel?
	std::string select_rubble_to_shovel_str; //Displayed when the player is selecting rubble to shovel.
	SDL_Surface *select_rubble_to_shovel_spr; //Displayed when the player is selecting rubble to shovel.
	std::string shovelling_message_str; //A message that is displayed while the unit is shovelling.
	SDL_Surface *shovelling_message_spr; //A message that is displayed while the unit is shovelling.
	bool animation_playing; //Is the unit currently playing an animation?
	std::string constructing_message_str; //A messaged that is displayed while the unit is constructing something.
	SDL_Surface *constructing_message_spr; //A messaged that is displayed while the unit is constructing something.
	std::string construct_walking_message_str;
	SDL_Surface *construct_walking_message_spr;

	job *my_job; //The current job this guy is doing.
	std::string job_state; //What is the unit currently doing?
	/* Acceptable values:
	 * idling
	 * - Means the unit is doing nothing.
	 * mining
	 * - Means the unit is doing mining stuff.
	 * moving
	 * - Means the unit is moving.
	 * shoveling
	 * - Means the unit is shoveling rubble!
	 * picking_up
	 * - Means the unit is picking up something. Probably ore.
	 * constructing
	 * - Means the unit is constructing something.
	 * chopping
	 * - Means the unit is choppin' trees.
	 */

	int construct_rate; //The rate at which it constructs buildings. TODO: Unhardcode.
	
	bClassUnit(); //Constructor. Initializes an empty unit.
	//bClassUnit(const bClassUnit &source); //Copy constructor.svn add --depth=infinity * --force
	~bClassUnit() //Deconstructor.
	{
		/*if(sprite != NULL)
		{
			SDL_FreeSurface(sprite);
		}svn add --depth=infinity * --force
		if(sprite_select != NULL)
		{
			SDL_FreeSurface(sprite_select);
		}*/
		sprite = NULL;
		sprite_select = NULL;
		carrying_message_sprite = NULL;
		mining_message_spr = NULL;
		select_object_to_pick_up_spr = NULL;
		chopping_message_spr = NULL;
		select_tree_to_chop_spr = NULL;
		select_rubble_to_shovel_spr = NULL;
		shovelling_message_spr = NULL;
		select_wall_to_mine_spr = NULL;
	}

	void init(int ID, SDL_Surface *SPRITE, std::string NAME, SDL_Surface *SPRITE_SELECT, bool SELECTABLE, int MOVE_SPEED, int MAX_HEALTH); //Initialize a new unit type.
	bool load_settings(); //Load the settings from the unit's cfg
	std::string update(); //Update the object. It returns a string to let the calling tile know stuff.
	//void set_sprite(std::string sprite_name); //Set the object's sprite. //Obsolete.
	void draw_sprite(); //Draw the sprite.
	void draw_inventory(); //Lets the player know what tools this guy is carrying.

	//Get and set the wx, and wy of the object.
	int get_wx();
	int get_wy();
	int get_wz();

	//Set the position, wx, and wy of the object.
	void set_pos(int WORLD_X, int WORLD_Y, int WORLD_Z);
	void set_wx(int WX);
	void set_wy(int WY);

	//Get the width and the height of the object
	int get_width();
	int get_height();

	void select(); //Select the object.

	bool calculate_path(); //Calculate a path to move_destination.

	bool check_mine_command(); //Checks if a mine command was issued.
	bool check_pick_up_command(); //Checks if a pick up object command was issued.
	bool check_shovel_command(); //Checks if a shovel command was issued.

	void check_job(); //Give the unit something to do out of the job que.
};

class unit_type_manager //Manages all the base types of units.
{
public:
	std::vector<bClassUnit> unit_list; //All the unit types are stored in this vector.

	void add_unit_type(int ID, SDL_Surface *SPRITE, std::string NAME, SDL_Surface *SPRITE_SELECT, bool SELECTABLE, int MOVE_SPEED, int MAX_HEALTH); //Add a new unit type.
	bool load_types_from_file(std::string filepath); //Loads all the unit types from the files...
	bool load_unit(std::string folderpath); //Adds a new type with the data it got out of the specified folder.
	bClassUnit get_by_id(int ID); //Returns a copy of the unit type that has the specified ID.

	unit_type_manager() { } //Constructor.
	~unit_type_manager()
	{
		std::cout << "Freeing unit types' sprites.\n";
		for(int i = 0; i < unit_list.size(); i++) //Free all the sprites.
		{
			SDL_FreeSurface(unit_list[i].sprite);
			SDL_FreeSurface(unit_list[i].sprite_select);
			SDL_FreeSurface(unit_list[i].carrying_message_sprite);
			SDL_FreeSurface(unit_list[i].select_wall_to_mine_spr);
			SDL_FreeSurface(unit_list[i].mining_message_spr);
			SDL_FreeSurface(unit_list[i].select_object_to_pick_up_spr);
			SDL_FreeSurface(unit_list[i].chopping_message_spr);
			SDL_FreeSurface(unit_list[i].select_tree_to_chop_spr);
			SDL_FreeSurface(unit_list[i].select_rubble_to_shovel_spr);
			SDL_FreeSurface(unit_list[i].shovelling_message_spr);
			SDL_FreeSurface(unit_list[i].constructing_message_spr);
			SDL_FreeSurface(unit_list[i].construct_walking_message_spr);
		}
	}
	
};
