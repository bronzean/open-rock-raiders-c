#include "object.hpp"
#include "../library/cfg/parser.hpp"
using namespace std;

object::object() //Constructor. Initialize an empty object.
{
	name = "";
	type_id = 0;

	can_drill_ground = false;

	default_damage = 0;

	jetpack = false;
	jetpack_fuel = 0;
	jetpack_fuel_consumption = 0;

	can_drill_wall = false;
	drill_rate = 0;
	drill_power = 0;

	can_chop_tree = false;
	chop_rate = 0;
	chop_power = 0;

	can_clear_rubble = false;
	default_rubble_damage = 0;
	shovel_power = 0;

	sprite = NULL;
	icon_sprite = NULL;
}

void object_manager::add_object_type(object Object) //Add a new object type.
{
	object_list.push_back(Object);
}

bool object_manager::load_types_from_file(std::string filepath) //Loads all the object types from the files...
{
	cout << "Loading objects!\n";
	out_string << "Loading objects!\n";

	string command = ""; //When it isn't a comment, it appends everything to this. Then this is checked to see if it matches any commands.
	string num_command = ""; //If the command takes parameters, here they are stored.
	bool comment = true; //Did a comment start?
	bool check_command = false; //Is it time to check a command?
	std::string new_object_name; //The name of the object we're going to create.
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
				new_object_name = command; //Let the game know the name of the object we're making.
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
						load_objects(num_command);
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
				object_list[object_list.size() - 1].type_id = atoi(command.c_str()); //Assign the object type's ID.
				out_string << "ID of new object: " << command << ". Confirmation: " << object_list[object_list.size() - 1].type_id << "\n";
			}
			check_command = false;
			command = "";
		}
	}

	fclose(file);
	return true;
}

bool object_manager::load_objects(string folderpath)
{
	object new_object; //The object we're going to create.

	//--------The new tool's properties.------
	string tool_name = ""; //The name.
	int tool_id = 0; //The ID.
	bool tool_is_tool = false; //Is it a tool?
	bool tool_is_weapon = false; //Is it a weapon?
	bool tool_can_drill_wall = false; //Can it drill walls?
	bool tool_can_drill_ground = false; //Can it drill the ground?
	bool tool_can_clear_rubble = false; //Can it clear rubble?
	int tool_default_damage = 0; //It's default damage?
	bool tool_jetpack = false; //Is it a jetpack?
	int tool_jetpack_duration = 0; //How long it keeps the raider 'afloat'.
	int tool_drill_rate = 0; //How much damage the tool inflicts to a tile per frame.
	//int tool_drill_ground_time = 0; //TODO: Implement this.
	int tool_rubble_clear_time = 0; //TODO: Implement this.
	int tool_drill_power = 0; //If this is greater than or equal to a wall's minimumn required mining power, then this tool can drill that wall!
	SDL_Surface *tool_icon_sprite = NULL; //Its icon.
	bool tool_can_chop_tree = false; //Can this tool chop down trees.
	int tool_default_rubble_damage = 0;
	int tool_shovel_rate = 0;
	int tool_shovel_power = 0;
	//----------------------------------------

	/*string command = ""; //When it isn't a comment, it appends everything to this. Then this is checked to see if it matches any commands.
	string num_command = ""; //If the command takes parameters, here they are stored.
	bool comment = true; //Did a comment start?
	bool check_command = false; //Is it time to check a command?
	char temp = ' '; //Holds the last char read...*/

	string filepath = folderpath + "/config";//The path to the config file...

	/*FILE *file = fopen(filepath.c_str(), "r"); //Open the file.
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
//			else if(command == "ID") //Found the entry that specifies the tool's ID.
//			{
//				bool quit = false; //Controlls the loop below.
//				bool start = false; //Start recording the parameter?
//
//				while(c != EOF && quit == false)
//				{
//					c = getc(file);
//					temp = (char) c;
//
//					if(temp == '\n' || temp == ')')
//					{
//						start = false;
//						quit = true;
//						tool_id = atoi(num_command.c_str()); //Assign the tool's ID.
//					}
//					else if(temp == '(')
//					{
//						start = true;
//					}
//					else if(start)
//					{
//						num_command += temp;
//					}
//				}
//			}
	}

	fclose(file);*/

	std::vector<cfg::variable> variables;

	if(!cfg::parse_config_file(filepath, &variables)) //Parses the cfg.
	{
		cout << "Failed to load object's cfg.\n"; //Tell the user it failed.

		return false; //Abort! Abort!
	}

	for(int i = 0; i < variables.size(); i++) //Loop through the variable list.
	{
		if(variables[i].name == "NAME") //Found the entry that specifies the object's name.
		{
			new_object.name = variables[i].values[0]; //Assign the new object's name.
		}
		else if(variables[i].name == "CAN_DRILL_WALL") //Found the entry that specifies whether or not the object can drill walls.
		{
			if(variables[i].values[0] == "TRUE" || variables[i].values[0] == "true")
			{
				new_object.can_drill_wall = true; //The new object can drill walls.
			}
			else
			{
				new_object.can_drill_wall = false; //The new object can't drill walls.
			}
		}
		else if(variables[i].name == "CAN_DRILL_GROUND") //Found the entry that specifies whether or not the object can drill ground.
		{
			if(variables[i].values[0] == "TRUE" || variables[i].values[0] == "true")
			{
				new_object.can_drill_ground = true; //The new object can drill ground.
			}
			else
			{
				new_object.can_drill_ground = false; //The new object can't drill ground..
			}
		}
		else if(variables[i].name == "DRILL_RATE") //Found the entry that specifies how much damage it inflicts on a tile per frame.
		{
			new_object.drill_rate = atoi(variables[i].values[0].c_str()); //Assign the object's drill rate.
		}
		else if(variables[i].name == "DRILL_POWER") //Found the entry that specifies the drill's power.
		{
			new_object.drill_power = atoi(variables[i].values[0].c_str()); //Assign the drill's power.
		}
		else if(variables[i].name == "CAN_CLEAR_RUBBLE") //Found the entry that specifies whether or not the object can clear rubble.
		{
			if(variables[i].values[0] == "TRUE" || variables[i].values[0] == "true")
			{
				new_object.can_clear_rubble = true; //The new object can clear rubble.
			}
			else
			{
				new_object.can_clear_rubble = false; //The new object can't clear rubble.
			}
		}
		else if(variables[i].name == "SHOVEL_POWER") //Found the entry that specifies the shoveling power of this object.
		{
			new_object.shovel_power = atoi(variables[i].values[0].c_str());
		}
		else if(variables[i].name == "DEFAULT_RUBBLE_DAMAGE") //Found the entry that specifies the rate at which the object shovels rubble.
		{
			new_object.default_rubble_damage = atoi(variables[i].values[0].c_str());
		}
		else if(variables[i].name == "DEFAULT_DAMAGE") //Found the entry that specifies the object's default damage.
		{
			new_object.default_damage = atoi(variables[i].values[0].c_str()); //Assign the default damage.
		}
		else if(variables[i].name == "JETPACK") //Found the entry that specifies whether or not the object is a jetpack.
		{
			if(variables[i].values[0] == "TRUE" || variables[i].values[0] == "true")
			{
				new_object.jetpack = true; //The new object is a jetpack.
			}
			else
			{
				new_object.jetpack = false; //The new object isn't a jetpack.
			}
		}
		else if(variables[i].name == "JETPACK_FUEL") //Found the entry that specifies the object's jetpack fuel.
		{
			new_object.jetpack_fuel = atoi(variables[i].values[0].c_str());
		}
		else if(variables[i].name == "JETPACK_FUEL_CONSUMPTION") //Found the entry that specifies the object's jetpack fuel consumption.
		{
			new_object.jetpack_fuel_consumption = atoi(variables[i].values[0].c_str());
		}
		else if(variables[i].name == "CAN_CHOP_TREE") //Found the entry that specifies whether or not the object can chop down trees.
		{
			if(variables[i].values[0] == "TRUE" || variables[i].values[0] == "true")
			{
				new_object.can_chop_tree = true;
			}
			else
			{
				new_object.can_chop_tree = false;
			}
		}
		else if(variables[i].name == "CHOP_POWER") //Found the entry that specifies the object's chop power.
		{
			new_object.chop_power = atoi(variables[i].values[0].c_str());
		}
		else if(variables[i].name == "CHOP_RATE") //Found the entry that specifies the rate at which the object chops trees.
		{
			new_object.chop_rate = atoi(variables[i].values[0].c_str());
		}
	}

	//Time to load the object's sprites.
	filepath = folderpath + "/icon.png";//The path to the icon...
	if(!img_load_safe(filepath, &new_object.icon_sprite)) //Load the sprite.
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		return false;
	}
	object_list.push_back(new_object);

	return true;
}

object object_manager::get_by_id(int ID) //Returns a copy of the object type that has the specified ID.
{
	vector<object>::iterator iterator; //Used for navigating object_type_list
	int counter = 0; //Used in the for loop below...

	for(iterator = object_list.begin(); iterator < object_list.end(); iterator++, counter++) //Loop through object_type_list
	{
		if(object_list[counter].type_id == ID) //If it found the object_type it's looking for..
		{
			cout << "Found the requested object type!\n"; //Debugging output
			out_string << "Found the requested object type!\n";

			return object_list[counter]; //Return with a copy of the object_type with the specified ID.
		}
	}

	object temp; //Couldn't find an object_type with that ID. So we create this...
	temp.name = " "; //Give it a name that means NULL.
	cout << "Didn't find the requested tool type.\n"; //Debugging output
	out_string << "Didn't find the requested tool type.\n";
	return temp; //And return that...
}

object_manager Object_Type_Manager; //Manages all the object types.
