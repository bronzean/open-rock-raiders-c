/* Copyright the ORR-C Dev Team */
#include "tile.hpp"

void tile::set_sprite(std::string sprite_path)
{
	sprite = img_load3(sprite_path);
	if(&sprite == NULL)
	{
		std::cout << "\ntile_object.sprite == NULL\n";
	}
	width = sprite->w;
	height = sprite->h;
}

int tile::get_wx()
{
	return wx;
}

int tile::get_wy()
{
	return wy;
}

int tile::get_width()
{
	return width;
}

int tile::get_height()
{
	return height;
}

vector<tile> Map; //This is the vector that stores the entire map...
vector<int> Active_Map; //This is the vector that stores all of the indexes of the active tiles...
vector<int> Draw_Map; //This is the vector that stores all of the indexes of the tiles that are in the camera's view.
std::vector<ore*> ore_on_map; //Points to all the ore that is currently laying around the place.
