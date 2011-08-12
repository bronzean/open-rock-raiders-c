/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Everything related to the constructions/buildings/bases is defined here
 * ----------------------------------------------------------- */

#pragma once
#include "../engine/EObject.hpp"
#include "../engine/interface/popup_menu.hpp"

class tool;
class ore;
class energy_crystal;
class animation;
class job;
class tile;
class popup_menu;

class pickup_sprite;

//This is the blase class of all the units that the game will be using
class bClassUnit
{
public:
	int wx, wy, wz; //The world x, world y, and world z.
	int layer; //The layer it's on.

	int m_health; //The max health.
	int c_health; //The current health.

	SDL_Surface *sprite, *sprite_left, *sprite_right, *sprite_up; //The unit's sprite. Sprite is facing down, all the rest face their specified direction.
	SDL_Surface *sprite_select; //This is the sprite that is used when the object is selected.
	SDL_Surface *sprite_ore_left, *sprite_ore_right, *sprite_ore_up, *sprite_ore_down; //These sprites are used when the unit is facing the specified direction and carrying ore at the same time.
	std::string spr_extend; //The file extension of the sprite's image
	bool color_key; //Draw with a color key?

	int width, height; //The width and the height of the object. It is obtained from the width and and the height of the image.

	bool selectable; //Is the unit selectable?
	bool selected; //Is the unit sellected?

	std::string name; //The name of the unit.
	int type_id; //The unit's type.

	//This is the object's position in the list of all objects.
	int que_num; //NOTE: UNUSED.

	int move_destination; //The tile to move to.
	int move_speed; //The speed the unit moves at. If there is a moving animation, then this is the ammount of frames spent on each frame of the animation. If there is no moving animation, then this is how many frames transpire until the unit moves to the next tile.
	int move_destination_ramp; //The tile to move to. This means it first has to move to a ramp tile.
	//Move up or down a layer when you reach the ramp?
	int move_layer_ramp; //0 = move down, 1 = move up.
	bool move; //If true, the unit is moving somewhere. If false, the unit is staying put.
	bool calculate_need_ramp; //If true, check if there is need for a ramp, then find the ramp. If false, that was already done.
	bool xmove; //If false, the unit can not move along x anymore. NOTE: UNUSED.
	bool ymove; //If false, the unit can not move along y anymore. NOTE: UNUSED.
	int move_frame; //The frame it last moved in.
	std::vector<int> move_path; //Contains a list of the indexes of all the tiles the raider needs to move to to reach it's goal.
	bool need_path; //Does the unit's path need to be calculated?
	bool allow_move; //Is the unit allowed to move?
	int frames_since_last_move; //The number of frames that have passed since the last move.
	int heading; //The direction the unit is facing. = 0 North. 90 = east. 180 = south. 270 = west.

	animation *move_left, *move_right, *move_up, *move_down; //The move left, right, up, and down animations.
	animation *move_left_carryore, *move_right_carryore, *move_up_carryore, *move_down_carryore; //The move left while carrying something, move right while carrying something, up and down too, animations.

	animation *active_animation; //Pointer to the currently active animation.

	int draw_frame; //The frame it last was drawn in.

	std::vector<tool> tool_list; //Contains all the tools that the raider is carrying.
	std::vector<tool>::iterator iterator; //Used for navigating the tool list.

	bool hovering; //Is the unit hovering?
	int hover_duration; //For how many more frames is the unit going to hover?

	//Contains the message: "Carrying: "
	std::string carrying_message_string;
	SDL_Surface *carrying_message_sprite;

	std::vector<ore> ore_list; //Contains all of the ore the unit is carrying.
	std::vector<ore>::iterator iterator2; //Used for navigating the ore list.
	std::vector<energy_crystal> energy_crystal_list; //Contains all of the energy crystals the unit is carrying.
	std::vector<energy_crystal>::iterator iterator3; //Used for navigating the energy crystal.

	bool carrying_resource; //If it's carrying an ore or energy crystal, set this to true, so that it doesn't pick up any others...
	bool carrying; //If it's carrying something...
	bool drop_carried; //Is the unit supposed to drop what it's carrying?

	bool mining_mode; //Used in the mining code.
	bool can_mine_wall; //Can the unit even mine stuff?
	int mine_tile_id; //The ID of the tile the unit needs to mine.
	bool mine_on_reach_goal; //Is the unit moving somewhere to mine a tile.
	std::string select_wall_to_mine_str; //A message that is displayed when the player wants to select a wall to mine.
	SDL_Surface *select_wall_to_mine_spr; //A message that is displayed when the player wants to select a wall to mine.
	bool mining; //Is the unit currently mining a tile? Used in drill times.
	std::string mining_message_str; //A message that is displayed while the unit is mining.
	SDL_Surface *mining_message_spr; //A message that is displayed while the unit is mining.

	bool taking_out_drill; //Is the unit currently taking out its drill? (used in the drilling animation)
	bool drill_out; //Did it take its drill out?
	bool putting_drill_away; //Is the unit currently putting its drill away?
	animation *takeout_drill_left, *takeout_drill_right, *takeout_drill_up, *takeout_drill_down; //The take out drill animations.
	animation *drill_left, *drill_right, *drill_up, *drill_down; //The drill left/right/up/down animations.
	animation *putaway_drill; //The put away the drill animation.
	int take_out_drill_time; //The number of frames the unit spends taking out its drill. If it has an animation for it, then it's the number of frames spent on each frame of the animation.
	int drill_time; //The number of frames the unit spends on each frame of the drilling animation.
	int drill_animation_frame_progress; //How far into the time allocated on each frame of the drilling animation has the unit gone?
	int putaway_drill_time; //The number of frames the unit spends putting away its drill. If it has an animation for it, then it's the number of frames spent on each frame of the animation.
	int take_out_drill_progress; //How far into taking out the drill has the unit gone?
	int put_away_drill_progress; //How far into putting the drill away has the unit gone?

	bool allow_deselect; //Allow the unit to be deselected?

	bool pick_up_on_reach_goal; //Is the unit moving somewhere to pick up something?
	bool pick_up_mode; //Is the unit waiting for the player to specify what it's going to be picking up?
	int pick_up_object_type; //The type of object the unit is picking up. -1 = not picking up anything. 0 = ore. 1 = Energy Crystal. 2 = tool.
	int pick_up_stage; //Used in the check_pick_up_command function.
	//bool holding_object; //Is the unit currently holding an object in its arms?
	std::string select_object_to_pick_up_str; //Used in the "Select object to pick up" stuff.
	SDL_Surface *select_object_to_pick_up_spr; //Used in the "Select object to pick up" stuff.

	animation *pick_up; //The pick up animation.
	pickup_sprite *pick_up_objects_sprite; //The pick up animation is a general pick up animation. Every object that can be picked up has a pick up version of the sprite. This sprite is overlayed over the pick up animation at the specified position.
	int pickup_time; //The number of frames the unit spends picking up an object. If it has an animation for it, then it's the number of frames spent on each frame of the animation.
	int pickup_progress; //How far into pickup up the object has the unit gone?
	bool picked_up; //This is set to true once the pickup time has expired.

	std::string status; //What's it doing? IDLE = not doing anything. Check the ai related files for the rest of the status stuff. NOTE: OBSOLETE.
	bool ai_pick_up_ore; //Is the unit allowed to automatically pick up ore?

	bool player; //Is this the player? (Used in the mode where the user is controlling only one unit in an RPG sort of thing.

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
	bool can_shovel_rubble; //Does the unit even possess the ability to shovel rubble?
	std::string select_rubble_to_shovel_str; //Displayed when the player is selecting rubble to shovel.
	SDL_Surface *select_rubble_to_shovel_spr; //Displayed when the player is selecting rubble to shovel.
	std::string shovelling_message_str; //A message that is displayed while the unit is shovelling.
	SDL_Surface *shovelling_message_spr; //A message that is displayed while the unit is shovelling.

	animation *shovel_animation; //The shovelling animation.
	int shovel_time; //The number of frames the unit spends on each frame of the shoveling animation.
	int shovel_animation_frame_progress; //How far into the time allocated on each frame of the shoveling animation has the unit gone?


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
	 * incide_usa
	 * - Means the unit is closing a door.
	 */

	int construction_repositioning; //A unit has to move off the construction it is building when it nears completion. This variable is used in that. 0 = false. 1 = true. 2 = Already done.
	int construct_rate; //The rate at which it constructs buildings. TODO: Unhardcode.
	std::string constructing_message_str; //A messaged that is displayed while the unit is constructing something.
	SDL_Surface *constructing_message_spr; //A messaged that is displayed while the unit is constructing something.
	std::string construct_walking_message_str;
	SDL_Surface *construct_walking_message_spr;

	//static popup_menu unit_popup_menu; //The unit's popup menu. NOTE: Unused
	popup_menu *wall_popup_menu; //When the user clicks on a wall (with this unit selected)...This is the popup menu that's used.
	popup_menu *rubble_popup_menu; //When the user clicks on rubble (with this unit selected)...This is the popup menu that's used.
	popup_menu *ground_popup_menu; //When the user clicks on ground (with this unit selected)...This is the popup menu that's used.

	bool close_door; //Unit has to close a door?
	bool closing_door; //Currently closing a door?
	tile* close_door_tile; //Pointer to the tile containing this door.
	bool needs_to_close_door; //Does the unit need to close the door behind itself?
	tile* needs_to_close_door_tile; //Pointer to the tile containing the door the unit needs to close.
	int moves_till_close_door_time; //In what number of moves does the unit need to close the door behind itself? (Used in conjuction with needs_to_close_door)

	int teleport_in_time; //The number of frames the teleporter spends on each frame of the teleport in animation. If no teleport in animation, then the amount of time that passes until the bingy bingy is teleported in.
	int teleport_in_progress; //How far into the time allocated on each frame of the teleport in animation has the unit gone? If no animation, how far into the teleport in time.
	animation* teleport_in_animation; //The teleport in animation.
	bool teleport_in_animation_done; //Is the teleport in animation done?




	bClassUnit(); //Constructor. Initializes an empty unit.
	//bClassUnit(const bClassUnit &source); //Copy constructor.
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
		wall_popup_menu = NULL;
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

	void construct_construction(); //Does the stuff related to constructions.

	void wall_popup_menu_update(); //Update the wall_popup_menu.
	void rubble_popup_menu_update(); //Update the rubble_popup_menu.
	void ground_popup_menu_update(); //Update the ground_popup_menu.

	void cancel_current_activity(); //Instead of always writing "mining = false; shovelling = false; etc", simply call this function and it'll do it ALL.

	void take_out_drill(); //Take out its drill.

	void drilling_animation(); //Handles animating the drilling animation.

	void shoveling_animation(); //Handles animating the shoveling animation.

	void _pick_up(); //Picks up objects. Well. Does the timing stuff, and the animating, if the unit has an animation.

	/* --------------------------------------------------------------
	 * The get_free_neighbor_tile function finds a free tile adjacent to the tile passed to it, and returns a pointer to it. Returns null on fail.
	 * ----------------------------------------------------------- */
	tile* get_free_neighbor_tile(tile* src_tile); 
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
