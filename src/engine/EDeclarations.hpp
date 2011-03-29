/* Copright the ORR-C Dev Team */
//Has all the declatations of classes, variables, etc...
#pragma once
#include "../Engine.hpp"

//Here some colors are defined.
#define C_BLACK {0, 0, 0}
#define C_WHITE {255, 255, 255}
#define C_RED {255, 0, 0}
#define C_GREEN {0, 255, 0}
#define C_BLUE {0, 0, 255}

extern TTF_Font *font1;
extern TTF_Font *font2;
extern SDL_Color c_black;
extern SDL_Color c_white;
extern SDL_Color c_red;
extern SDL_Color c_green;
extern SDL_Color c_blue;
extern SDL_Surface *pause_text_spr; //The paused message's surface

//Screen width, height, and bit mode
extern int SCREEN_WIDTH; // 800
extern int SCREEN_HEIGHT; // 600
extern int SCREEN_BPP; // 32
//Run in full screen?
extern bool FULLSCREEN;

//The Frame Rate
extern int FPS;
extern int GFPS; //The graphic updates fps.
extern bool allow_draw; //Is it a drawing update frame?

//The gamestate manager
enum gameState
{
	Title,
	Loading,
	LevelSelect,
	Level
};

extern bool paused;

//The game state
extern gameState GameState;

//This is the screen's surface
extern SDL_Surface *screen;

//This is the sprite for the teleport button used throughout the game.
extern SDL_Surface *teleport_button_spr;
extern SDL_Surface *no_teleport_button_spr;
extern std::string teleport_button_path;
extern std::string no_teleport_button_path;

//is the game over or not
extern bool gameover;

//fps regulator
extern Timer fps;

//the event structure
extern SDL_Event event_struct;

//the keystates
extern Uint8 *keystates;

//the camera
extern camera Camera;
extern camera *PCamera;
extern int camera_move_speed;
//camera *PCamera = &Camera();


//These 2 have to do with teleporting objects.
extern int g_teleport_que;
extern std::string g_teleport_que_name[9];
extern int def_teleporter; //This tells the game what building in the building list is the default teleporter. -1 means none. Remember to allow the map creator to define the default teleporter, and also remember to make the first teleporter in the list the default if it is unhidden.

extern int num_tiles; //This tells the game how many tiles there are.

extern int num_layers; //This tells the game how many layers the map has.



//TODO: Make the following unhardcoded
extern SDL_Surface *tile_1;
extern SDL_Surface *tile_2;

//extern std::string* unit_type_list;
//extern int unit_type_list_num;

extern int num_col_objects;
extern int num_row_objects;

int GetTile(int x, int y);

extern int rightclick_tile_id; //The index of the tile that a right click just happened on in the map array. A value of -1 indicates it's a nonexistant tile.

extern int fps_counter;

extern std::string screen_caption;

extern std::FILE *GameLog; //The game log file stream.

extern std::stringstream out_string; //Holds what to write to the file.

extern SDL_Surface* title_screen; //The title screen's sprite.
extern std::string title_screen_path; //Path to the title screen's image.

extern SDL_Surface *current_layer_sprite; //Contains a message stating the camera's current layer.
extern std::stringstream current_layer_string; //Contains a message stating the camera's current layer.

extern int leftclick_tile_id; //The index of the tile that a left click just happened on in the map array. A value of -1 indicates it's a nonexistant tile.

extern int update_graphics_every_x_frames; //After how many frames should the graphics be updated?
extern std::string map_folder_path; //The path to the map...

extern bool move_issued; //Used in controlling player movement.

extern bool recheck_importance; //Is it time for the tiles to recheck importance?

extern int num_worker_threads; //How many threads the game creates to help it do all the work that needs to be done.

extern std::vector<pthread_t> threads; //The worker threads themselves.

extern int game_mode; //0 = classic. 1 = arcade.

static pthread_mutex_t screen_lock;

extern bool screen_needs_updating; //Is it time for stuff to be drawn?

extern SDL_Surface *title_screen_text1_spr; //Let the player know they have to press enter to enter the game.

extern SDL_Surface *title_screen_text2_spr; //Nifty little saying on the title screen.

static bool allow_unit_selection = true; //Only if no buttons were clicked and whatnot can units be selected/deselected.

//-----------MUSIC STUFF--------------
static int audio_open = 0;
static Mix_Music *music = NULL;
static int next_track = 0;


static SDL_RWops *rwfp;
static int audio_rate = 22050;
static Uint16 audio_format = AUDIO_S16;
static int audio_channels = 2;
static int audio_buffers = 4096;
static int audio_volume = MIX_MAX_VOLUME;
static int looping = -1;
static int rwops = 0;

static std::string music_filepath = "music.ogg";
//------------------------------------
