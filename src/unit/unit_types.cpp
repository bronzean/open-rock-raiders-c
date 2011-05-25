/* Copyright the ORR-C Dev Team */
#include "unit.hpp"
using namespace std;

//Add a new unit type.
void unit_type_manager::add_unit_type(int ID, SDL_Surface *SPRITE, std::string NAME, SDL_Surface *SPRITE_SELECT, bool SELECTABLE, int MOVE_SPEED, int MAX_HEALTH)
{
	bClassUnit new_unit; //The new unit type.

	new_unit.init(ID, SPRITE, NAME, SPRITE_SELECT, SELECTABLE, MOVE_SPEED, MAX_HEALTH); //Initialize it...

	//And, finally, add it to unit type list.
	unit_list.push_back(new_unit);
}

bool unit_type_manager::load_types_from_file(std::string filepath) //Loads all the unit types from the files...
{
	cout << "Loading unit types!\n";
	out_string << "Loading unit types!\n";
	string command = ""; //When it isn't a comment, it appends everything to this. Then this is checked to see if it matches any commands.
	string num_command = ""; //If the command takes parameters, here they are stored.
	bool comment = true; //Did a comment start?
	bool check_command = false; //Is it time to check a command?
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
						//now load the settings of that unit from it's own function...
						load_unit(num_command);
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

bool unit_type_manager::load_unit(string folderpath)
{
	bClassUnit new_unit; //The unit we're going to create

	//--------The new unit's properties.------
	string unit_name = ""; //The new unit's name.
	int unit_type = 0; //The new unit's type/ID.
	SDL_Surface *unit_sprite = NULL; //The new unit's sprite.
	SDL_Surface *unit_sprite_select = NULL; //The new unit's selected sprite.
	bool unit_selectable = false; //Can this new unit be selected?
	int unit_move_speed = 0; //The speed the unit moves at.
	int unit_max_health = 100; //The maximumn health of the unit.
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
			if(command == "NAME") //Found the entry that specifies the unit's name.
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
						unit_name = num_command; //Assign the new unit's name.
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
			else if(command == "ID") //Found the entry that specifies the unit's ID.
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
						unit_type = atoi(num_command.c_str()); //Assign the unit's type/ID.
						std::cout << "Unit type's ID: " << unit_type << "\n";
						out_string << "Unit type's ID: " << num_command << "\n";
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
			else if(command == "SELECTABLE") //Found the entry that specifies whether or not the unit is selectable.
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
						if(num_command == "TRUE" || num_command == "true")
						{
							unit_selectable = true;
						}
						else
						{
							unit_selectable = false;
						}
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
			else if(command == "MOVE_SPEED") //Found the entry that specifies the unit's move speed.
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
						unit_move_speed = atoi(num_command.c_str());
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
			else if(command == "MAX_HEALTH") //Found the entry that specifies the unit's max health.
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
						unit_max_health = atoi(num_command.c_str());
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

	//Time to load the unit's sprite.
	filepath = folderpath + "/sprite.png";//The path to the sprite...
	//unit_sprite = img_load3(filepath); //Load the sprite.
	if(!img_load_safe(filepath, &unit_sprite))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
	}
	filepath = folderpath + "/sprite_select.png"; //The path to the selected sprite.
	//unit_sprite_select = img_load(filepath); //Load the selected sprite.
	if(!img_load_safe(filepath, &unit_sprite_select))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
	}

	new_unit.init(unit_type, unit_sprite, unit_name, unit_sprite_select, unit_selectable, unit_move_speed, unit_max_health); //Initialize the new unit.
	unit_list.push_back(new_unit);

	return true;
}

bClassUnit unit_type_manager::get_by_id(int ID) //Returns a copy of the unit type that has the specified ID.
{
	vector<bClassUnit>::iterator iterator; //Used for navigating the unit list
	int counter = 0; //Used in the loop below...

	for(iterator = unit_list.begin(); iterator < unit_list.end(); iterator++, counter++) //Loop through the unit list
	{
		if(unit_list[counter].type == ID) //If it found the unit it's looking for...
		{
			cout << "Found the requested unit type!\n"; //Debugging output
			out_string << "Found the requested unit type!\n";

			return unit_list[counter]; //Return with a copy of the unit with the specified ID.
		}
	}

	bClassUnit temp; //Couldn't find an unit with that ID. So we create this...
	temp.name = " "; //Give it a name that means NULL.
	cout << "Didn't find the requested unit type.\n"; //Debugging output
	out_string << "Didn't find the requested unit type.\n";
	return temp; //And return that...
}

unit_type_manager Unit_Type_Manager; //Manages all the unit types.
