/* Copyright the ORR-C Dev Team */
//Loads an image
#include "../Engine.hpp"

//Loads the image
SDL_Surface *img_load( std::string filename ) 
{
	std::cout << "\nLoading image...";
    //The image to be loaded
	SDL_Surface* loadedImage = NULL;
    
    SDL_Surface* newImage = NULL;
    
    loadedImage = IMG_Load( filename.c_str() );
    
    //Error checking basicly
    if( loadedImage != NULL )
    {
        newImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old image
        SDL_FreeSurface( loadedImage );
		std::cout << "Succesfully loaded\n";
    }
    else
    {
    	std::cerr << "Error: Couldn't load \"" + filename + "\".";
    	return NULL;
    }
    
    return newImage;
}

//color keyed image loader
SDL_Surface *img_load2( std::string filename ) 
{
	std::cout << "\nLoading image...";
    SDL_Surface *loadedImage = NULL;
    
    SDL_Surface *optimizedImage = NULL;
    
    loadedImage = IMG_Load( filename.c_str() );
    
    //Error checking basically
    if( loadedImage != NULL )
    {
       optimizedImage = SDL_DisplayFormat( loadedImage );
        
        SDL_FreeSurface( loadedImage );
		
        if( optimizedImage != NULL )
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
			//Set the pixels of certain rgb to be transparant
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
		std::cout << "Succesfully loaded\n";
		
		return optimizedImage;
	}
	else
	{
		std::cerr << "Error: Couldn't load \"" + filename + "\".";
		return NULL;
	}
}

//load a wide assortment of images
SDL_Surface *img_load3(std::string filename)
{
	std::cout << "\nLoading image...";
	out_string << "\nLoading image...";
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image using SDL_image
	loadedImage = IMG_Load( filename.c_str() );
	
	//If the image loaded
	if( loadedImage != NULL )
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );

		//Free the old image
		SDL_FreeSurface( loadedImage );
		std::cout << "Succesfully loaded\n";
		out_string << "Succesfully loaded\n";
	}

	else
	{
		std::cerr << "Error: Couldn't load \"" + filename + "\".";
		out_string << "Error: Couldn't load \"" + filename + "\".";
		return NULL;
	}

	return optimizedImage;
}
