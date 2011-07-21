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
	SDL_Surface *sprite_open; //The construction's open sprite.

	bool door; //Is it a door?
	bool locked; //Is it locked? (Used by doors and the like)
	bool construction_open; //Is it currently open? (Used by doors and the like)
	bool opening; //Is it in the process of opening. Used only on powered engine door things and the like. Ones the unit doesn't have to open for themselves.
	int door_strength; //What is the strength of the door? Used to calculate how easy it is for a monsters to force it open.
	int open_ammount; //Pretty much open progress. (Used by doors and the like)
	bool can_automatic_open; //Does the construction have the ability to open by itself? That is, doesn't require something to actively be opening it. (Used by doors and the like)

	/*bool door_open_animation; //Does the door have an animation that plays when it's opened?
	bool door_close_animation; //Does the door have an animation that plays when it's closed?
	int door_open_animation_entry; //Stores the index of the door opening animation's entry in the animations vector.
	int door_close_animation_entry; //Stores the index of the door closing animation's entry in the animations vector.*/

	int open_time; //How many frames it takes for the door to open. If using animations, then how much time is spent on each frame of the animation.

	std::vector<animation> animations; //Stores all of the tile's animations.
	bool active_animation; //Is an animation currently going on?
	int active_animation_entry; //The entry of the active animation in the animations vector.

	bool open_animation; //Does the construction have an opening animation?
	int open_animation_entry; //Stores the index of the open animation's entry in the animations vector.
	bool close_animation; //Does the construction have a closing animation?
	int close_animation_entry; //Stores the index of the close animation's entry in the animations vector.

	void init(std::string NAME, bool WALL, bool FLOOR, bool DOOR, int DOOR_STRENGTH, int TYPE_ID, std::string SPRITE); //Initalize a new construction type.

	void copy_from(construction Construction); //Give this tile the properties of the one being copied.

	void draw_sprite(int wx, int wy, int layer); //Draw the construction's sprite.

	bool load_config(std::string folderpath); //Load the properties of the construction. (Used only for animations at the moment.)

	void open_thyself(bool automatic);

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
