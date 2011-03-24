/* Copyright the ORR-C Dev Team */
#include "main.hpp" //Blablabla, include main.hpp
#include "engine/EObject.hpp" //Blablabla, include the game object class stuff header file.
#include "engine/Interface.hpp" //Include the interface header file.
#include "engine/spritelist.hpp" //Blablabla, include spritelist.hpp

/* --------------------------------------------------------------
 * This contains the entry point of the program.
 * ----------------------------------------------------------- */

void *DrawScreen(void *param); //Since the graphics update thread is started in this file, and it will run this function, the game needs to know this function exists! So, it is declared here.

//The entry point for our program.
int main( int argc, char* argv[] )
{
	std::cout << "Enter path to map. INCLUDE THE TRAILING '/'!\n"; //Prompt the player to specify the location to the map.
	std::cin >> map_folder_path; //Kay, save that value.

	Timer fps2; //Used to keep track of how many frames pass each second.

	GameLog = fopen("gamelog.txt", "w+");; //Open/create the log file.

	cout << "ORR Version Number: " << VERSION << "\n"; //Output the version number to the console.
	out_string << "ORR Version Number: " << VERSION << "\n"; //Output it to the log file too.
	fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog); //Write out_string to the log.
	fflush(GameLog); //Force it to write.
	out_string.str(""); //Reset out_string. Otherwise bad things can happen...

	//Add the version number to the window caption.
	screen_caption += " Version: ";
	screen_caption += VERSION;

	//Startup the engine
	if(!startup(false, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screen_caption, false))
	{
		std::cerr << "Failed to initialize\n"; //Let the user know that the game failed to initialize.
		out_string << "Failed to initialize\n"; //Let the user know that the game failed to initialize.
		fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog); //Write out_string to the log.
		fflush(GameLog); //Force it to write.
		fclose(GameLog); //Close the log file.
		return 1; //Since startup failed, exit the program.
	}

	if(load_sprites() == 1) //Loads some sprites.
	{
		std::cerr << "Failed to load sprites.\n"; //Let the user know that some sprites failed to load...
		out_string << "Failed to load sprites.\n"; //Let the user know that some sprites failed to load...
		fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog); //Write out_string to the log.
		fflush(GameLog); //Force it to write.
		fclose(GameLog); //Close the log file.
		return 1; //Since startup failed, exit the program.
	}

	GameState = Title; //Sets the gamestate to title.

	fps2.start(); //Start the fps timers

	title_screen = img_load3("data/resource/title.png"); //TODO: Fix the title screen bug. This is just a quick 'n dirty fix.

	//We draw these next two here so that they don't need to be needlessely redrawn every frame.
	draw((SCREEN_WIDTH / 2) - (title_screen_text1_spr->w / 2), (SCREEN_HEIGHT - 100), title_screen_text1_spr, title_screen); //Let the player know they have to press enter to enter the game.
	draw((SCREEN_WIDTH / 2) - (title_screen_text2_spr->w / 2), 0, title_screen_text2_spr, title_screen); //Nifty little saying...TODO: Make it randomally choose between a list of sayings...

	cout << "\n\n\n\n\n\n\n\n\n"; //'Spam' the console with newlines.

	if(num_worker_threads > 0) //If threads are enabled...
	{
		pthread_create(&threads[0], NULL, DrawScreen, NULL); //Then tell thread 0 to get drawing.
	}

	pthread_mutex_init(&screen_lock, NULL); //Initialize the drawing related stuff mutex.

	//Initialize the music related variables.
	audio_rate = 22050;
	audio_format = AUDIO_S16;
	audio_channels = 2;
	audio_buffers = 4096;

	/* Set the music volume */
	Mix_VolumeMusic(audio_volume);

	/* Set the external music player, if any */
	Mix_SetMusicCMD(getenv("MUSIC_CMD"));

	/* Open the audio device */
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		
	} else {
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		printf("Opened audio at %d Hz %d bit %s (%s), %d bytes audio buffer\n", audio_rate,
			(audio_format&0xFF),
			(audio_channels > 2) ? "surround" : (audio_channels > 1) ? "stereo" : "mono", 
			(audio_format&0x1000) ? "BE" : "LE",
			audio_buffers );
	}
	audio_open = 1;

	/* Load the requested music file */
	if(rwops)
	{
		rwfp = SDL_RWFromFile(music_filepath.c_str(), "rb");
		music = Mix_LoadMUS_RW(rwfp);
	}
	else
	{
		music = Mix_LoadMUS(music_filepath.c_str());
		music = Mix_LoadMUS(music_filepath.c_str());
	}
	if(music == NULL)
	{
		fprintf(stderr, "Couldn't load %s: %s\n", music_filepath.c_str(), SDL_GetError());
		
	}
	else
	{
		/* Play the music */
		printf("Playing %s\n", music_filepath.c_str());
		Mix_FadeInMusic(music,looping,2000);
	}

	if(FPS > 0) //If the FPS cap is not set to 'infinite'...See, a FPS cap of < 0 means to run the game with no cap.
	{
		//Main game loop
		while(!gameover)
		{
			fps.start();

			update(); //Everything is updated here. Drawing stuff, pathfinding, ai, etc.
			fps_counter++; //Increment the frame counter.

			//Frame rate stuff
			if(fps.get_ticks() < 1000 / FPS)
			{
				SDL_Delay((1000 / FPS) - fps.get_ticks());
			}

			if(fps2.get_ticks() > 1000) //If a second passed...
			{

				stringstream new_screen_capt; //Ya, this variable is gonna be the new window caption.
				new_screen_capt << screen_caption.c_str() << " FPS: " << fps_counter; //Update the "FPS: #" portion of the window caption.

				SDL_WM_SetCaption(new_screen_capt.str().c_str(), NULL); //Set the window caption.
				fps_counter = 0; // Reset the FPS counter so that it counts the number of frames per second, not the number of frames the program has done total.

				fps2.start(); //Tick the FPS timer.
			}
		}
	}
	else //This is a slightly edited version of the main game loop. It's edited to run with no FPS cap.
	{
		//Main game loop
		while(!gameover)
		{
			fps.start(); //Start the FPS timer. It simply is used to calculate the new window caption.

			update(); //everything is updated here. Drawing stuff, pathfinding, ai, etc.
			fps_counter++; //Increment the FPS counter.

			if(fps2.get_ticks() > 1000) //If a second has passed...
			{
				stringstream new_screen_capt; //Ya, this variable is gonna be the new window caption.
				new_screen_capt << screen_caption.c_str() << " FPS: " << fps_counter; //Update the "FPS: #" portion of the window caption.

				SDL_WM_SetCaption(new_screen_capt.str().c_str(), NULL); //Set the window caption.
				fps_counter = 0; // Reset the FPS counter so that it counts the number of frames per second, not the number of frames the program has done total.

				fps2.start(); //Tick the FPS timer.
			}
		}
	}

	if(num_worker_threads > 0)
	{
		pthread_join(threads[0], NULL); //Ya, get rid of the worker threads. Alternatively, call kill...
	}


	//Close all the music related stuff.
	if(Mix_PlayingMusic())
	{
		Mix_FadeOutMusic(1500);
		SDL_Delay(1500);
	}
	if(music)
	{
		Mix_FreeMusic(music);
		music = NULL;
		if(rwops)
		{
			SDL_FreeRW(rwfp);
		}
	}
	if(audio_open ) {
		Mix_CloseAudio();
		audio_open = 0;
	}

	fclose(GameLog); //Close the gamelog.

	SDL_Quit(); //Exit SDL.

	pthread_exit(NULL); //End of program. Ya, pthreads stops execution here.

	return 0; //End of program.
}
