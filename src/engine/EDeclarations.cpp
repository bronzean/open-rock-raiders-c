/* Copyright the ORR-C Dev Team */
//Has all the declatations of classes, variables, etc...
#include "SDL/SDL.h"
#include "SDL/SDL_keyboard.h"
#include "EDeclarations.hpp"

TTF_Font *font1 = NULL;
TTF_Font *font2 = NULL;
SDL_Color c_black = C_BLACK;
SDL_Color c_white = C_WHITE;
SDL_Color c_red = C_RED;
SDL_Color c_green = C_GREEN;
SDL_Color c_blue = C_BLUE;

SDL_Surface *pause_text_spr = NULL;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int SCREEN_BPP = 24;
bool FULLSCREEN = false;
int FPS = 50;
int GFPS = 50;
bool allow_draw = true; //Is it a drawing update frame?

bool paused = false;

gameState GameState = Title;

SDL_Surface *screen = NULL;

bool gameover = false;

Timer fps;

SDL_Event event_struct;

Uint8 *keystates = SDL_GetKeyState(NULL); 

camera Camera(1);
camera *PCamera = &Camera;
int camera_move_speed = 10;

SDL_Surface *teleport_button_spr = NULL;
SDL_Surface *no_teleport_button_spr = NULL;
std::string teleport_button_path = "";
std::string no_teleport_button_path = "";

//These 2 have to do with teleporting objects.
vector<string> g_teleport_que;
construction* def_teleporter = NULL; //This tells the game what building in the building list is the default teleporter. -1 means none. Remember to allow the map creator to define the default teleporter, and also remember to make the first teleporter in the list the default if it is unhidden.

int num_tiles;

int num_layers;


//Sprites for the tiles
SDL_Surface *tile_1;
SDL_Surface *tile_2;

//std::string* unit_type_list;
//int unit_type_list_num;

int num_col_objects = 0;
int num_row_objects = 0;

/* Use this function to access the Map array as a 2D array...
Map[GetTile(world_x,world_y)];
*/
//Version 1.
int GetTile(int x, int y)
{
//	return ((num_row_objects*x) + y);
//	return (((x / 32) * num_row_objects) + (y / 32));
//	return (((x / 32) * num_col_objects) + ((y / 32)));

//	return (((x) / 32)) + (((y) / 32) * num_row_objects); //FUNNY!
//	return (((x) / 32)) + (((y) / 32) * num_col_objects); //Semi-funny.
//	return (((x * num_col_objects) + (y)) / 32);
	return ((((((x) / 32) * (num_col_objects)) + ((y) / 32))));
}
//Version 2.
int GetTile2(int x, int y)
{
	return ((((((x) / 32)) + (((y) / 32) * (num_col_objects)))));
}

int rightclick_tile_id = 0; //The index of the tile that a right click just happened on in the map array. A value of -1 indicates it's a nonexistant tile.

int fps_counter = 0; //The FPS counter.

std::string screen_caption = "Open Rock Raiders";

std::FILE *GameLog; //The game log file stream.

std::stringstream out_string;

SDL_Surface* title_screen = NULL; //The title screen's sprite.
std::string title_screen_path = ""; //Path to the title screen's image.

SDL_Surface *current_layer_sprite = NULL; //Contains a message stating the camera's current layer.
std::stringstream current_layer_string; //Contains a message stating the camera's current layer.

int leftclick_tile_id = 0; //The index of the tile that a left click just happened on in the map array. A value of -1 indicates it's a nonexistant tile.

int update_graphics_every_x_frames = 0; //After how many frames should the graphics be updated?

string map_folder_path = "maps/default/"; //The path to the map...

bool move_issued = false; //Used in controlling player movement.

bool recheck_importance = false; //Is it time for the tiles to recheck importance?

int num_worker_threads = 0; //How many threads the game creates to help it do all the work that needs to be done.

std::vector<pthread_t> threads; //The worker threads themselves.

int game_mode = 0; //0 = classic. 1 = arcade.

bool screen_needs_updating = true; //Is it time for stuff to be drawn?

SDL_Surface *title_screen_text1_spr;// = TTF_RenderText_Solid(font1, "Press enter to enter the test level", c_white); //Let the player know they have to press enter to enter the game.

SDL_Surface *title_screen_text2_spr;// = TTF_RenderText_Solid(font1, "Tales of Mining and Great Riches", c_white); //Nifty little saying on the title screen.

bool threed_gfx = false; //Will the game be using 3D graphics?

bool server = false; //Is the game running in server or client mode?

int receivedByteCount = 0; //Variable keeping track of the size of incoming data.

bool active_popup_menu = false; //Is a popup menu active?

bool unit_selected = false; //Is a unit currently selected?
bClassUnit* selected_unit = NULL; //Pointer to the selected unit.

bool tile_selected = false; //Is a tile currently selected?
tile* selected_tile = NULL; //Pointer to the selected tile.

bool allow_unit_selection = true; //Only if no buttons were clicked and whatnot can units be selected/deselected

bool construction_selected = false; //Is a construction currently selected?
construction* selected_construction = NULL; //Pointer to the selected construction.

vector<construction*> constructions_on_map; //Vector of all the constructions on the map.
