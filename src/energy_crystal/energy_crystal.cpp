/* Copright the ORR-C Dev Team */
#include "energy_crystal.hpp"
using namespace std;

//Initialize a new energy crystal/energy crystal type.
void energy_crystal::init(int ID, int ENERGY_PRODUCTION_RATE, SDL_Surface *SPRITE, std::string NAME)
{
	type_id = ID;
	energy_production_rate = ENERGY_PRODUCTION_RATE;
	sprite = SPRITE;
	name = NAME;
}

energy_crystal::energy_crystal() //Constructor. Initializes an empty energy crystal.
{
	name = "";
	energy_production_rate = 0;
	type_id = 0;
	sprite = NULL;
}

//Add a new energy crystal type.
void energy_crystal_manager::add_energy_crystal_type(int ID, int ENERGY_PRODUCTION_RATE, SDL_Surface *SPRITE, std::string NAME)
{
	energy_crystal new_energy_crystal; //The new energy crystal type.

	new_energy_crystal.init(ID, ENERGY_PRODUCTION_RATE, SPRITE, NAME); //Initialize it...

	//And, finally, add it to the energy crystal type list.
	energy_crystal_list.push_back(new_energy_crystal);
}

bool energy_crystal_manager::load_types_from_file(std::string filepath) //Loads all the energy crystal types from the files...
{
	cout << "Loading energy crystal types!\n";
	out_string << "Loading energy crystal types!\n";
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
						//now load the settings of that energy crystal from it's own function...
						load_energy_crystal(num_command);
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

bool energy_crystal_manager::load_energy_crystal(string folderpath)
{
	energy_crystal new_energy_crystal; //The energy crystal we're going to create

	//--------The new energy crystal's properties.------
	string energy_crystal_name = ""; //The new energy crystal's name.
	int energy_crystal_id = 0; //The new energy crystal's ID.
	int energy_crystal_energy_production_rate = 1; //The new energy crystal's energy production rate.
	SDL_Surface *energy_crystal_sprite = NULL; //The new energy crystal's sprite.
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
			if(command == "NAME") //Found the entry that specifies the energy crystal's name.
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
						energy_crystal_name = num_command; //Assign the new energy crystal's name.
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
			else if(command == "ID") //Found the entry that specifies the energy crystal's ID.
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
						energy_crystal_id = atoi(num_command.c_str()); //Assign the energy crystal's ID.
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
			else if(command == "ENERGY_PRODUCTION_RATE") //Found the entry that specifies the energy crystal's matter value.
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
						energy_crystal_energy_production_rate = atoi(num_command.c_str()); //Assign the energy crystal's matter value.
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

	//Time to load the energy crystal's sprite.
	filepath = folderpath + "/sprite.png";//The path to the sprite...
	energy_crystal_sprite = img_load3(filepath); //Load the sprite.

	new_energy_crystal.init(energy_crystal_id, energy_crystal_energy_production_rate, energy_crystal_sprite, energy_crystal_name); //Initialize the new energy crystal.
	energy_crystal_list.push_back(new_energy_crystal);

	return true;
}

energy_crystal energy_crystal_manager::get_by_id(int ID) //Returns a copy of the energy crystal type that has the specified ID.
{
	vector<energy_crystal>::iterator iterator; //Used for navigating the energy crystal list
	int counter = 0; //Used in the for loop below...

	for(iterator = energy_crystal_list.begin(); iterator < energy_crystal_list.end(); iterator++, counter++) //Loop through the energy crystal list
	{
		if(energy_crystal_list[counter].type_id == ID) //If it found the energy crystal it's looking for...
		{
			cout << "Found the requested energy crystal type!\n"; //Debugging output
			out_string << "Found the requested energy crystal type!\n";

			return energy_crystal_list[counter]; //Return with a copy of the energy crystal with the specified ID.
		}
	}

	energy_crystal temp; //Couldn't find an energy crystal with that ID. So we create this...
	//temp.name = " "; //Give it a name that means NULL.
	cout << "Didn't find the requested energy crystal type.\n"; //Debugging output
	out_string << "Didn't find the requested energy crystal type.\n";
	return temp; //And return that...
}

energy_crystal_manager Energy_Crystal_Type_Manager; //Manages all the energy crystal types.
