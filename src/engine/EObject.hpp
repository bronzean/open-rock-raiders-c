/* Copyright the ORR-C Dev Team */
//This file contains all the base classes for all the objects that exist in the game
#pragma once
#include "../Engine.hpp"
#include "../unit/unit.hpp"
#include "../tool/tool.hpp"
#include "../map/tile.hpp"
#include "../ore/ore.hpp"
#include "../energy_crystal/energy_crystal.hpp"
#include "../construction/construction.hpp"
#include "../job/job_que.hpp"
#include <vector>

class tool;
class tool_manager;

class ore;
class ore_manager;

class energy_crystal;
class energy_crystal_manager;

class animation;

class bClassUnit;
class unit_type_manager;

class tile;
class tile_manager;

class draw_message_handler;

class construction;

class job_que;

class message;
class draw_message_handler //Handles all the messages to be drawn.
{
public:
	//std::vector<int> world_x_list; //Contains a list of all the messages' world x.
	//std::vector<int> world_y_list; //Contains a list of all the messages' world y.
	//std::vector<int> layer_list; //Contains a list of all the messages' layer.
	//std::vector<SDL_Surface*> draw_what_sprite_list; //Contains a list of all the messages themselves.
	//std::vector<int> message_duration_frames_list; //Contains a list specifying how many frames each message lasts.
	//std::vector<int>::iterator list_iterator; //Used for looping through all the messages to be drawn.
	std::vector<message> messages; //Contains all the messages.
	std::vector<message>::iterator _iterator; //Used for looping through all the messages to be drawn.

	void add_message(int wx, int wy, int layer, SDL_Surface *to_draw_spr, int message_duration, bool global); //Adds a message to be drawn.
	void add_message2(int wx, int wy, int layer, SDL_Surface **to_draw_spr, int message_duration, bool global); //Adds a message to be drawn.
	void add_message3(int wx, int wy, int layer, SDL_Surface to_draw_spr, int message_duration, bool global); //Adds a message to be drawn.
	void draw_all(); //Draw everything it's supposed to draw. This is called at the end of the update function, so that the message is drawn on top of everything else.
};

class message //A message used by the draw_message_handler.
{
public:
	int world_x, world_y, layer; //The x, y, and layer of the message.
	SDL_Surface* sprite; //The sprite of the message.
	int message_duration; //The duration of the message.
	bool global; //Is the message always displayed?

	message() { world_x = 0; world_y = 0; layer = 0; message_duration = 0; sprite = NULL; global = false;} //Constructor.
	~message() { }
};


class animation //It's an animation...
{
public:
	int num_frames; //The number of frames the animation lasts...
	int current_frame; //The current frame that's playing in the animation.
	std::string folder_path; //The path to the folder containing all the animation's files.
	std::vector<SDL_Surface *> frames_spr; //Contains the sprites of all the frames.

	void init(); //Initialize everything.


	//static job_que Job_Que; //The job que!
	bool load_settings(std::string cfg_path); //Load all the animation's properties/settings.

	void proceed_animation(); //Proceeds the animation by one frame.
	void draw_sprite(int wx, int wy, int layer); //Draw the current frame's sprite.
	void auto_proceed1(); //Just a little function that automatically proceeds the animation...Based on a timer.

	animation(); //Constructor. Initializes an empty animation.
	~animation() //Deconstructor.
	{
		//for(int i = 0;  i < num_frames; i++)
			//if(frames_spr[i] != NULL)
				////SDL_FreeSurface(frames_spr[i]);
				//frames_spr[i] = NULL;
	}
};



extern unit_type_manager Unit_Type_Manager; //The unit manager.

extern tool_manager Tool_Type_Manager; //Manages all the tool types.

extern tile_manager Tile_Type_Manager; //Manages all the tile types.

extern std::vector<tile> Map; //This is the vector that stores the entire map...
extern std::vector<int> Active_Map; //This is the vector that stores all of the indexes of the active tiles...
extern std::vector<int> Draw_Map; //This is the vector that stores all of the indexes of the tiles that are in the camera's view.

extern ore_manager Ore_Type_Manager; //Manages all the ore types.

extern energy_crystal_manager Energy_Crystal_Type_Manager; //Manages all the Energy Crystal Types.

extern draw_message_handler Draw_Message_Handler; //Handles all the messages to be drawn.

extern std::vector<ore*> ore_on_map; //Points to all the ore that is currently laying around the place.

extern job_que Job_Que; //The job que!
