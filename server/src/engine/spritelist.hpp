/* Copyright the ORR-C Dev Team */
#include "../Engine.hpp"

//////////////////////////
//The Spritelist Class- REDUNDANT
//////////////////////////

class spritelist
{
public:
	SDL_Surface *sprite_list;
	int sprite_num;

//	void init(int size);
	void init();
	int add_sprite(std::string path); //Add a sprite to the array
};


extern spritelist SpriteList;
