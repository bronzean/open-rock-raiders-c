/* Copyright the ORR-C Dev Team */
#include "construction.hpp"

bool construction::load_config(std::string folderpath)
{
	cout << "Loading construction animations!\n"; //Debugging output.
	out_string << "Loading construction animations!\n"; //Debugging output.

	string command = ""; //When it isn't a comment, it appends everything to this. Then this is checked to see if it matches any commands.
	string num_command = ""; //If the command takes parameters, here they are stored.
	bool comment = true; //Did a comment start?
	bool check_command = false; //Is it time to check a command?
	char temp = ' '; //Holds the last char read...

	string filepath = folderpath; //The location of the cfg of this construction.
	filepath += "/config";

	FILE *file = fopen(filepath.c_str(), "r"); //Open the file.
	if(file == NULL) //If the file doesn't exist.
	{
		cout << "The file \"" << filepath << "\" does not exist!\n"; //Debugging output...
		out_string << "The file \"" << filepath << "\" does not exist!\n"; //Debugging output...
		return false; //Tell the caller that it failed.
	}
	cout << "Filepath is: " << filepath << "\n"; //Debugging output.
	out_string << "Filepath is: " << filepath << "\n"; //Debugging output.

	int c = 0; //Its location in the file

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
			if(command == "OPEN_ANIMATION") //Found the entry that specifies where the construction's open animation's cfg is located.
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;

						animation new_animation; //The new animation that's going to be added to the animations vector.

						new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

						//Debugging output.
						out_string << "Kay, I found the stuff that has to do with the opening animation.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						animations.push_back(new_animation); //Add the open animation to the construction's animation vector.
						open_animation_entry = animations.size() - 1; //Let the game know what the open animation's location in the animations vector is.

						open_animation = true; //Let's the game know that the construction has an open animation.
					}
					else if(temp == '(')
					{
						start = true;
					}
					else if(start)
					{
						num_command += temp;
					}
				}
			}
			else if(command == "CLOSE_ANIMATION") //Found the entry that specifies where the construction's close animation's cfg is located.
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;

						animation new_animation; //The new animation that's going to be added to the animations vector.

						new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

						//Debugging output.
						out_string << "Kay, I found the stuff that has to do with the closing animation.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						animations.push_back(new_animation); //Add the close animation to the construction's animation vector.
						close_animation_entry = animations.size() - 1; //Let the game know what the close animation's location in the animations vector is.

						close_animation = true; //Let's the game know that the construction has a close animation.
					}
					else if(temp == '(')
					{
						start = true;
					}
					else if(start)
					{
						num_command += temp;
					}
				}
			}
			else if(command == "BUILD_ANIMATION") //Found the entry that specifies where the construction's build animation's cfg is located.
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;

						animation new_animation; //The new animation that's going to be added to the animations vector.

						new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

						//Debugging output.
						out_string << "Kay, I found the stuff that has to do with the building animation.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						animations.push_back(new_animation); //Add the build animation to the construction's animation vector.
						build_animation_entry = animations.size() - 1; //Let the game know what the build animation's location in the animations vector is.

						build_animation = true; //Let's the game know that the construction has a build animation.
					}
					else if(temp == '(')
					{
						start = true;
					}
					else if(start)
					{
						num_command += temp;
					}
				}
			}
			else if(command == "OPEN_TIME") //Found the entry that specifies the open time.
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;

						open_time = atoi(num_command.c_str()); //Save the value, of course.
					}
					else if(temp == '(')
					{
						start = true;
					}
					else if(start)
					{
						num_command += temp;
					}
				}
			}
			else if(command == "CLOSE_TIME") //Found the entry that specifies the close time.
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;

						close_time = atoi(num_command.c_str()); //Save the value, of course.
					}
					else if(temp == '(')
					{
						start = true;
					}
					else if(start)
					{
						num_command += temp;
					}
				}
			}
			else if(command == "BUILD_TIME") //Found the entry that specifies the build time.
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;

						build_time = atoi(num_command.c_str()); //Save the value, of course.
					}
					else if(temp == '(')
					{
						start = true;
					}
					else if(start)
					{
						num_command += temp;
					}
				}
			}
			check_command = false;
			command = "";
			num_command = "";
		}
	}

	fclose(file);

	return true;
}
