/* Copyright the ORR-C Dev Team */
#include "main.hpp"

//This is called when the program is to exit and close
void clean_up()
{
	std::cout << "\nCleaning up everything\n";
	/*Don't forget to release all images here
	ex.
	SDL_FreeSurface( ImageName );*/

	//SDL_FreeSurface(PToolShed->sprite);

	//Quit SDL
	SDL_Quit();
}
