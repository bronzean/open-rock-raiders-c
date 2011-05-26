/* Copyright the ORR-C Dev Team */
#include "EObject.hpp"

/* --------------------------------------------------------------
 * Everything related to the animation class is defined here.
 * ----------------------------------------------------------- */

void animation::init() //Initialize everything.
{
}

animation::animation() //Constructor. Initializes an empty animation.
{
	num_frames = 0; //Set to 0.
	current_frame = 0; //Set to 0.
	folder_path = ""; //Makes sure it's an emptry string.
}

bool animation::load_settings(std::string cfg_path) //Load all the animation's properties/settings.
{
	out_string << "Loading animation!\n"; //Let's the user know an animation is being loaded.
	string command = ""; //When it isn't a comment, it appends everything to this. Then this is checked to see if it matches any commands.
	string num_command = ""; //If the command takes parameters, here they are stored.
	bool comment = true; //Did a comment start?
	bool check_command = false; //Is it time to check a command?
	char temp = ' '; //Holds the last character read...

	FILE *file = fopen(cfg_path.c_str(), "r"); //Open the file.
	if(file == NULL) //If the file doesn't exist.
	{
		cout << "The file \"" << cfg_path << "\" does not exist!\n"; //Debugging output...
		out_string << "The file \"" << cfg_path << "\" does not exist!\n"; //Debugging output...
		return false; //Tell the calling function that it failed.
	}
	cout << "Filepath is: " << cfg_path << "\n"; //Debugging output.
	out_string << "Filepath is: " << cfg_path << "\n"; //Debugging output.
	int c = 0; //The parser's location in the file.

	while (c != EOF) //While the end of the file hasn't been reached.
	{
        	c = getc(file); //Read the current char.
		temp = (char) c; //Convert it into something we can use.

		if(temp == ']' || temp == '\n') //If it's found the end of the line or the closing ']'...
		{
			comment = true; //Tell it everything after this is a comment.
			check_command = true; //Tell it to check the data it read in.
		}
		if(!comment) //If it's not a comment...
		{
			command += temp; //Add the character we just read to command.
		}

		if(temp == '[') //If it found an opening '['
		{
			comment = false; //Let it know commenting is off.
		}

		if(check_command) //If it's time to check the data we read...
		{
			if(command == "NUM_FRAMES") //Found the entry that specifies the animation's number of frames.
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false) //While it hasn't reached the end of the file and quit equals false...
				{
					c = getc(file); //Read the next character from the file.
					temp = (char) c; //Convert to a char and store that in temp.

					if(temp == '\n' || temp == ')') //If the character that was just read is either equal to '\n' or ')'...
					{
						start = false; //Do not save any more characters.
						quit = true; //Quit this loop.
						num_frames = atoi(num_command.c_str()); //Convert the value to an int and store it in num_frames.
						out_string << "Number of frames: " << num_frames << "\n"; //Debugging output.
					}
					else if(temp == '(') //Ok, is temp equal to '('?
					{
						start = true; //Start saving the characters that are read in from the file.
					}
					else if(start) //Finally, if all the other checks failed...
					{
						num_command += temp; //Save the character just read by adding it to num_command.
					}
				}
			}
			else if(command == "IMG_SRC_FOLDER") //Found the entry that specifies the locations of the images the animation uses.
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false) //While it hasn't reached the end of the file and quit equals false...
				{
					c = getc(file); //Read the next character from the file.
					temp = (char) c; //Convert to a char and store that in temp.

					if(temp == '\n' || temp == ')') //If the character that was just read is either equal to '\n' or ')'...
					{
						start = false; //Do not save any more characters.
						quit = true; //Quit this loop.
						folder_path += num_command; //Add what has been read so far onto folder_path.
						out_string << "Location of the animation's files: " << folder_path << "\n"; //Debugging output.
					}
					else if(temp == '(') //Ok, is temp equal to '('?
					{
						start = true; //Start saving the characters that are read in from the file.
					}
					else if(start) //Finally, if all the other checks failed...
					{
						num_command += temp; //Save the character just read by adding it to num_command.
					}
				}
			}
			check_command = false; //Done checking the command.
			num_command = ""; //Reset this. VERY IMPORANT!
			command = ""; //Reset this too. VERY IMPORTANT!
		}
	}

	fclose(file); //Close the file.

	string image_path = ""; //The path to the next frame's sprite to load.

	for(int i = 0; i < num_frames; i++) //This makes sure all the sprites have been loaded.
	{
		image_path = folder_path; //Reset this...Crucial.

		//Find the path of the next image.
		stringstream covert_to_int; //Blablabla, a whole bunch of conversion junk...
		covert_to_int << i; //Blablabla, a whole bunch of conversion junk...
		image_path += covert_to_int.str(); //Blablabla, a whole bunch of conversion junk...
		image_path += ".png"; //Blablabla, a whole bunch of conversion junk...

		SDL_Surface *new_image = NULL; //The image that's being loaded is first stored here.
		frames_spr.push_back(new_image); //Add this new image that was just loaded to the animation's sprite list.

		//frames_spr[frames_spr.size() - 1] = img_load3(image_path); //Load the new image.
		img_load_safe(image_path, &frames_spr[frames_spr.size() - 1]); //Load the new image.
		if(frames_spr[frames_spr.size() - 1] == NULL) //Check if it failed to load the image...
		{
			//It failed to load the image. Let the game and player know that.
			cout << "Failed loading sprite for animation!\n";
			cout << "Filepath: " << image_path << "\n";
			out_string << "\nFailed loading sprite for animation!\n";

			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog); //Force write the contents of out_string to the gamelog file.
			out_string.str(""); //Reset out_string.

			return false; //Exit the function.
		}

		SDL_FreeSurface(new_image); //Very important to free the surfaces when they're not needed anymore!
	}

	return true; //Sucesfully loaded everything.
}

void animation::auto_proceed1() //Autoproceeds the animation based on time...
{
	//First off, this function is run in its own thread.
	//Here's how it works:
	/*
	proceed_animation(); //Proceed the animation.
	SDL_Delay(ANIMATION_FPS); //Delay the animation for the ammount of ms it's supposed to delay.
	*/
	//Meanwhile, the owner of this animation is calling draw_sprite().
}

void animation::proceed_animation() //Proceeds the animation by one frame.
{
	current_frame++; //Increments the current frame by one.
	if(current_frame >= num_frames) //If it has looped through all the frames...
	{
		current_frame = 0; //Then head back to the beginning.
	}
}

void animation::draw_sprite(int wx, int wy, int layer) //Draw the current frame's sprite.
{
	if(screen_needs_updating == false)
	{
		if(layer == PCamera->layer && wx + frames_spr[current_frame]->w >= PCamera->wx && wx <= (PCamera->wx + SCREEN_WIDTH) && wy + frames_spr[current_frame]->h >= PCamera->wy && wy <= (PCamera->wy + SCREEN_HEIGHT)) //If the sprite is on screen...
		{
			draw(wx - (PCamera->wx), wy - (PCamera->wy), frames_spr[current_frame], screen); //Draw the sprite.
		}
	}
}
