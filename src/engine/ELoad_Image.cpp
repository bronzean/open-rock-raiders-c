/* Copyright the ORR-C Dev Team */
//Loads an image
#include "../Engine.hpp"

//Loads the image
SDL_Surface *img_load(std::string filename) 
{
	std::cout << "\nLoading image...";
	//The image to be loaded
	SDL_Surface* loadedImage = NULL;
	//auto_ptr<SDL_Surface> loadedImage;

	SDL_Surface* newImage = NULL;
	//auto_ptr<SDL_Surface> newImage;
    
	loadedImage = IMG_Load(filename.c_str());
	//loadedImage = (auto_ptr<SDL_Surface>) IMG_Load(filename.c_str());
    
	//Error checking basicly
	if(loadedImage != NULL)
	//if(*loadedImage != NULL)
	{
		newImage = SDL_DisplayFormat(loadedImage);
		//newImage = (auto_ptr<SDL_Surface>) SDL_DisplayFormat(*loadedImage);
        
		//Free the old image
		SDL_FreeSurface(loadedImage);
		//SDL_FreeSurface(*loadedImage);
		std::cout << "Succesfully loaded\n";
	}
	else
	{
		std::cerr << "Error: Couldn't load \"" + filename + "\".";
		return NULL;
	}
    
	return newImage;
	//return *newImage;
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

//Loads the image
bool img_load_safe(std::string filename, SDL_Surface **Original) //Doesn't memleak. Copy of img_load3.
{
	std::cout << "\nLoading image...";
	out_string << "\nLoading image...";

	SDL_Surface* loadedImage = NULL; //The image that's loaded
	SDL_Surface* optimizedImage = NULL; //The image that's loaded

	loadedImage = IMG_Load(filename.c_str()); //Load the image using SDL_image
	
	if(loadedImage != NULL) //If the image loaded
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		*Original = optimizedImage; //TODO: This isn't actually modifying Original...

		SDL_FreeSurface(loadedImage); //Free the old image
		std::cout << "Succesfully loaded\n";
		out_string << "Succesfully loaded\n";
	}
	else
	{
		std::cerr << "Error: Couldn't load \"" + filename + "\".";
		out_string << "Error: Couldn't load \"" + filename + "\".";
		SDL_Surface *null_spr = NULL;
		//Original = null_spr;
		*Original = NULL;
		return false;
	}
	return true; //Success!
}
