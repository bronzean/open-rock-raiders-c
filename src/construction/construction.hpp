/* Copyright the ORR-C Dev Team */

/* --------------------------------------------------------------
 * Everything related to the constructions/buildings/bases is defined here
 * ----------------------------------------------------------- */

#pragma once
#include "../engine/EObject.hpp"

typedef bClassUnit unit;

class construction //It's a construction. Most basic piece of a building.
{
public:
	std::string name; //The name of this construction.
	int type_id; //Let's the game know what type it is.

	bool wall; //Is it a wall?

	bool floor; //Is it a floor?

	tile *containing_tile; //What tile is this construction built on?

	bool selectable; //Can this construction be selected?
	bool selected; //Can this construction be selected?
	bool allow_deselect; //Is the construction allowed to be deselected/selected?

	bool teleporter; //Is it a teleporter?
	int teleport_signal_strength; //The teleport signal strength.
	unit* teleport_unit_type; //What type of unit does it deleport? NOTE: OBSOLETE.
	//int unit_to_teleport_id; //The type id of the unit to teleport.

	SDL_Surface *sprite; //The construction's sprite.
	SDL_Surface *sprite_select; //The construction's selected sprite.
	SDL_Surface *sprite_open; //The construction's open sprite.
	SDL_Surface *construction_qued_sprite; //The sprite displayed when the construction is qued.

	bool door; //Is it a door?
	bool locked; //Is it locked? (Used by doors and the like)
	bool construction_open; //Is it currently open? (Used by doors and the like)
	bool opening; //Is it in the process of opening? Used only on powered engine door things and the like. Ones the unit doesn't have to open for themselves.
	bool closing; //Is it in the process of closing? Used only on powered engine door things and the like. Ones the unit doesn't have to stand there closing.
	int door_strength; //What is the strength of the door? Used to calculate how easy it is for a monsters to force it open.
	int open_ammount; //Pretty much open progress. (Used by doors and the like)
	int close_ammount; //Pretty much close progress. (Used by doors and the like)
	bool can_automatic_open; //Does the construction have the ability to open/close by itself? That is, doesn't require something to actively be opening it. (Used by doors and the like)

	/*bool door_open_animation; //Does the door have an animation that plays when it's opened?
	bool door_close_animation; //Does the door have an animation that plays when it's closed?
	int door_open_animation_entry; //Stores the index of the door opening animation's entry in the animations vector.
	int door_close_animation_entry; //Stores the index of the door closing animation's entry in the animations vector.*/

	int open_time; //How many frames it takes for the construction to open. If using animations, then how much time is spent on each frame of the animation.
	int close_time; //How many framed it takes for the construction to open. If using animations, then how much time is spent on each frame of the animation.
	int build_time; //How many frames it takes for the construction to open. If using animations, specifies how much time is spent on each frame of the animation.

	std::vector<animation> animations; //Stores all of the tile's animations.
	bool active_animation; //Is an animation currently going on?
	int active_animation_entry; //The entry of the active animation in the animations vector.

	bool open_animation; //Does the construction have an opening animation?
	int open_animation_entry; //Stores the index of the open animation's entry in the animations vector.
	bool close_animation; //Does the construction have a closing animation?
	int close_animation_entry; //Stores the index of the close animation's entry in the animations vector.
	bool build_animation; ///Does the construction have a build animation?
	int build_animation_entry; //Stores the index of the build animation's entry in the animations vector.

	//Here are all the possible connections. Used for walls and the like.
	SDL_Surface *four_way_spr, *corner_left_down_spr, *corner_left_up_spr, *corner_right_down_spr, *corner_right_up_spr, *horz_downcon_spr, *horz_endsopen_spr, *horz_leftend_spr, *horz_rightend_spr, *horz_upcon_spr, *vert_downend_spr, *vert_endsopen_spr, *vert_leftcon_spr, *vert_rightcon_spr, *vert_upend_spr; //All the connection sprites.
	SDL_Surface* connection; //A pointer to the current connection. NULL for none.

	construction *neighbour_left, *neighbour_right, *neighbour_up, *neighbour_down; //The construction's neighbouring constructions.

	void init(std::string NAME, bool WALL, bool FLOOR, bool DOOR, bool TELEPORTER, int DOOR_STRENGTH, int TYPE_ID, std::string SPRITE); //Initalize a new construction type.

	void copy_from(construction Construction); //Give this tile the properties of the one being copied.

	void draw_sprite(int wx, int wy, int layer); //Draw the construction's sprite.

	bool load_config(std::string folderpath); //Load the properties of the construction. (Used only for animations at the moment.)

	void open_thyself(bool automatic); //Open the construction! (Door, for example.)
	void close_thyself(bool automatic); //Close the construction! (Door, for example.)

	void select(); //Checks if the player selected/deselected the construction.

	void update(); //Update whatever needs updating.

	void update_connections(); //Updates this tile's connection sprite.

	void load_connection_sprites(std::string folderpath); //Load the tile's connection sprites.


	construction(); //Constructor. Initializes an empty construction.
	~construction() //Deconstructor.
	{
	}
};

extern construction c_wall; //Wall construction.
extern construction c_floor; //Floor construction.
extern construction c_door; //Door construction.
extern construction c_teleporter1; //Teleportation device.

extern bool construction_location_select;
extern bool construction_wall_location_select; //Is the game waiting for the user to select where to place wall the construction?
extern bool construction_door_location_select; //Is the game waiting for the user to select where to place door the construction?

extern std::string choose_wall_location_str;
extern SDL_Surface* choose_wall_location_spr;

extern std::string choose_door_location_str;
extern SDL_Surface* choose_door_location_spr;
