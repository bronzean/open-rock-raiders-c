/* Copright the ORR-C Dev Team */
//Contians all of the drawing code
#include "../Engine.hpp"

//draw an image to the screen
void draw( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
	//if(screen_needs_updating == false)
	//{
		SDL_Rect offset;

		offset.x = x;
		offset.y = y;
		//blit function
		SDL_BlitSurface( source, NULL, destination, &offset );
	//}
}

void draw2( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	//blit function
	SDL_BlitSurface( source, NULL, destination, &offset );
}

//void ShrinkPicture (SDL_Surface *screen, SDL_Surface *picture) 
//{
//	SDL_Surface *shrink_picture;
//	SDL_Rect dest;
//	int factorx, factory;
//
//	for (factorx=1; factorx<6; factorx++) {
//	 for (factory=1; factory<6; factory++) {
//
//		ClearScreen(screen);
//		if ((shrink_picture=shrinkSurface (picture, factorx, factory))!=NULL) {
//			dest.x = (screen->w - shrink_picture->w)/2;;
//			dest.y = (screen->h - shrink_picture->h)/2;
//			dest.w = shrink_picture->w;
//			dest.h = shrink_picture->h;
//			if ( SDL_BlitSurface(shrink_picture, NULL, screen, &dest) < 0 ) {
//				fprintf(stderr, "Blit failed: %s\n", SDL_GetError());
//				break;
//			}
//			SDL_FreeSurface(shrink_picture);
//		}
//
//		/* Display by flipping screens */
//		SDL_Flip(screen);
//
//		/* Pause for 0.25 sec */
//		SDL_Delay(250);
//
//	 }
//	}
//	
//}
