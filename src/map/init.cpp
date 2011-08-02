/* Copyright the ORR-C Dev Team */
#include "tile.hpp"

void tile::init(int ID, SDL_Surface *SPRITE, std::string NAME, bool WALL, bool RAMP, bool UP_RAMP, bool DOWN_RAMP, bool SELF_SUPPORTING, int ORE_TYPE, bool CAN_MINE, int MINIMUMN_MINING_POWER, bool AIR, bool TURN_TO_GROUND, int GROUND_TYPE, bool GENERATE_ORE_ON_MINE, int NUM_ORE_TO_GENERATE, bool TREE, bool RUBBLE)
{
	type_id = ID;
	sprite = SPRITE;
	name = NAME;
	width = SPRITE->w;
	height = SPRITE->h;
	ramp = RAMP;
	up_ramp = UP_RAMP;
	down_ramp = DOWN_RAMP;
	wall = WALL;
	self_supporting = SELF_SUPPORTING;
	ore_type = ORE_TYPE;
	can_mine = CAN_MINE;
	minimumn_mining_power = MINIMUMN_MINING_POWER;
	air = AIR;
	turn_to_ground = TURN_TO_GROUND;
	ground_type = GROUND_TYPE;
	generate_ore_on_mine = GENERATE_ORE_ON_MINE;
	num_ore_to_generate = NUM_ORE_TO_GENERATE;
	tree = TREE;
	rubble = RUBBLE;
}
