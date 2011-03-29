/* Copyright the ORR-C Dev Team */
#include "ore.hpp"
using namespace std;

//Initialize a new ore/ore type.
void ore::init(int ID, int MATTER_VALUE, SDL_Surface *SPRITE, string NAME)
{
	type_id = ID;
	matter_value = MATTER_VALUE;
	sprite = SPRITE;
	name = NAME;
}

ore::ore() //Constructor. Initializes an empty ore.
{
	name = "";
	matter_value = 0;
	type_id = 0;
	sprite = NULL;
	containing_tile = NULL;
}

//Add a new ore type.
void ore_manager::add_ore_type(int ID, int MATTER_VALUE, SDL_Surface *SPRITE, string NAME)
{
	ore new_ore; //The new ore type.

	new_ore.init(ID, MATTER_VALUE, SPRITE, NAME); //Initialize it...

	//And, finally, add it to the ore type array.
	ore_list.push_back(new_ore);
}

bool ore_manager::load_types_from_file(std::string filepath) //Loads all the ore types from the files...
{
	cout << "Loading ore types!\n";
	out_string << "Loading ore types!\n";
	string command = ""; //When it isn't a comment, it appends everything to this. Then this is checked to see if it matches any commands.
	string num_command = ""; //If the command takes parameters, here they are stored.
	bool comment = true; //Did a comment start?
	bool check_command = false; //Is it time to check a command?
	//std::string new_ore_name; //The name of the ore we're going to create.
	char temp = ' '; //Holds the last char read...

	FILE *file = fopen(filepath.c_str(), "r"); //Open the file.
	if(file == NULL) //If the file doesn't exist.
	{
		cout << "The file \"" << filepath << "\" does not exist!\n"; //Debugging output...
		out_string << "The file \"" << filepath << "\" does not exist!\n"; //Debugging output...
		return false; //Tell the caller that it failed.
	}
	cout << "Filepath is: " << filepath << "\n"; //Debugging output.
	out_string << "Filepath is: " << filepath << "\n"; //Debugging output.
	int c = 0; //It's location in the file

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
			if(command != "") //If command is not an empty string...
			{
				//new_ore_name = command; //Let the game know the name of the tool we're making.
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
						//now load the settings of that ore from it's own function...
						load_ore(num_command);
						num_command = "";
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
		}
	}

	fclose(file);
	return true;
}

bool ore_manager::load_ore(string folderpath)
{
	ore new_ore; //The ore we're going to create

	//--------The new ore's properties.------
	string ore_name = ""; //The new ore's name.
	int ore_id = 0; //The new ore's ID.
	int ore_matter_value = 1; //The new ore's material value.
	SDL_Surface *ore_sprite = NULL; //The new ore's sprite.
	//----------------------------------------

	string command = ""; //When it isn't a comment, it appends everything to this. Then this is checked to see if it matches any commands.
	string num_command = ""; //If the command takes parameters, here they are stored.
	bool comment = true; //Did a comment start?
	bool check_command = false; //Is it time to check a command?
	char temp = ' '; //Holds the last char read...

	string filepath = folderpath + "/config";//The path to the config file...

	FILE *file = fopen(filepath.c_str(), "r"); //Open the file.
	if(file == NULL) //If the file doesn't exist.
	{
		cout << "The file \"" << filepath << "\" does not exist!\n"; //Debugging output...
		out_string << "The file \"" << filepath << "\" does not exist!\n"; //Debugging output...
		return false; //Tell the caller that it failed.
	}
	cout << "Filepath is: " << filepath << "\n"; //Debugging output.
	out_string << "Filepath is: " << filepath << "\n"; //Debugging output.
	int c = 0; //It's location in the file

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
			if(command == "NAME") //Found the entry that specifies the ore's name.
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
						ore_name = num_command; //Assign the new ore's name.
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
			else if(command == "ID") //Found the entry that specifies the ore's ID.
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
						ore_id = atoi(num_command.c_str()); //Assign the ore's ID.
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
			else if(command == "MATTER_VALUE") //Found the entry that specifies the ore's matter value.
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
						ore_matter_value = atoi(num_command.c_str()); //Assign the ore's matter value.
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

	//Time to load the ore's sprite.
	filepath = folderpath + "/sprite.png";//The path to the sprite...
	ore_sprite = img_load3(filepath); //Load the sprite.

	new_ore.init(ore_id, ore_matter_value, ore_sprite, ore_name); //Initialize the new ore.
	ore_list.push_back(new_ore);

	return true;
}

ore ore_manager::get_by_id(int ID) //Returns a copy of the ore type that has the specified ID.
{
	vector<ore>::iterator iterator; //Used for navigating ore_list
	int counter = 0; //Used in the for loop below...

	for(iterator = ore_list.begin(); iterator < ore_list.end(); iterator++, counter++) //Loop through ore_list
	{
		if(ore_list[counter].type_id == ID) //If it found the ore it's looking for...
		{
			cout << "Found the requested ore type!\n"; //Debugging output
			out_string << "Found the requested ore type!\n";

			return ore_list[counter]; //Return with a copy of the ore with the specified ID.
		}
	}

	ore temp; //Couldn't find an ore with that ID. So we create this...
	temp.name = " "; //Give it a name that means NULL.
	cout << "Didn't find the requested ore type.\n"; //Debugging output
	out_string << "Didn't find the requested ore type.\n";
	return temp; //And return that...
}

ore_manager Ore_Type_Manager; //Manages all the ore types.
