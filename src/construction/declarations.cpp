/* Copyright the ORR-C Dev Team */
#include "construction.hpp"

std::string choose_wall_location_str = "Choose the location of the wall construction, kind sir.";
SDL_Surface* choose_wall_location_spr = NULL;

std::string choose_door_location_str = "Choose the location of the door construction, kind sir.";
SDL_Surface* choose_door_location_spr = NULL;

std::string choose_teleporter1_location_str = "Ye must choose tha location of thy teleporter.";
SDL_Surface* choose_teleporter1_location_spr = NULL;

bool construction_location_select = false;
bool construction_wall_location_select = false; //Is the game waiting for the user to select where to place the wall construction?
bool construction_door_location_select = false; //Is the game waiting for the user to select where to place the door construction?
bool construction_teleporter1_location_select = false; //Is the game waiting for the user to select where to place the teleporter construction?
