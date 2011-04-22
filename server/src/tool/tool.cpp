#include "tool.hpp"
using namespace std;

//Constructor. Initialize an empty tool.
tool::tool()
{
	is_tool = false;
	is_weapon = false;
	can_drill_wall = false;
	can_drill_ground = false;
	can_clear_rubble = false;
	default_damage = 0;
	jetpack = false;
	jetpack_duration = 0;
	type_id = 0;
	drill_rate = 0;
	drill_power = 0;
	can_chop_tree = false;
	default_rubble_damage = 0;
	shovel_rate = 0;
	shovel_power = 0;
	sprite = NULL;
	icon_sprite = NULL;
}

//Initialize a new tool type
void tool::init(int ID, bool IS_TOOL, bool IS_WEAPON, bool CAN_DRILL_WALL, bool CAN_DRILL_GROUND, bool CAN_CLEAR_RUBBLE, int DEFAULT_DAMAGE, bool JETPACK, int JETPACK_DURATION, SDL_Surface *ICON_SPRITE, int DRILL_RATE, int DRILL_POWER, bool CAN_CHOP_TREE, int DEFAULT_RUBBLE_DAMAGE, int SHOVEL_RATE, int SHOVEL_POWER)
{
	is_tool = IS_TOOL;
	is_weapon = IS_WEAPON;
	can_drill_wall = CAN_DRILL_WALL;
	can_drill_ground = CAN_DRILL_GROUND;
	can_clear_rubble = CAN_CLEAR_RUBBLE;
	default_damage = DEFAULT_DAMAGE;
	jetpack = JETPACK;
	jetpack_duration = JETPACK_DURATION;
	type_id = ID;
	drill_rate = DRILL_RATE;
	drill_power = DRILL_POWER;
	can_chop_tree = CAN_CHOP_TREE;
	default_rubble_damage = DEFAULT_RUBBLE_DAMAGE;
	shovel_rate = SHOVEL_RATE;
	shovel_power = SHOVEL_POWER;
	icon_sprite = ICON_SPRITE;
}

//Add a new tool type.
void tool_manager::add_tool_type(int ID, bool IS_TOOL, bool IS_WEAPON, bool CAN_DRILL_WALL, bool CAN_DRILL_GROUND, bool CAN_CLEAR_RUBBLE, int DEFAULT_DAMAGE, bool JETPACK, int JETPACK_DURATION, SDL_Surface *ICON_SPRITE, int DRILL_RATE, int DRILL_POWER, bool CAN_CHOP_TREE, int DEFAULT_RUBBLE_DAMAGE, int SHOVEL_RATE, int SHOVEL_POWER)
{
	tool new_tool; //The new tool type.

	new_tool.init(ID, IS_TOOL, IS_WEAPON, CAN_DRILL_WALL, CAN_DRILL_GROUND, CAN_CLEAR_RUBBLE, DEFAULT_DAMAGE, JETPACK, JETPACK_DURATION, ICON_SPRITE, DRILL_RATE, DRILL_POWER, CAN_CHOP_TREE, DEFAULT_RUBBLE_DAMAGE, SHOVEL_RATE, SHOVEL_POWER); //Initialize it...

	//And, finally, add it to the tool type array.
	tool_list.push_back(new_tool);
}

bool tool_manager::load_types_from_file(std::string filepath) //Loads all the tool types from the files...
{
	cout << "Loading tools!\n";
	out_string << "Loading tools!\n";
	string command = ""; //When it isn't a comment, it appends everything to this. Then this is checked to see fi ti matches any commands.
	string num_command = ""; //If the command takes parameters, here they are stored.
	bool comment = true; //Did a comment start?
	bool check_command = false; //Is it time to check a command?
	std::string new_tool_name; //The name of the tool we're going to create.
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
				new_tool_name = command; //Let the game know the name of the tool we're making.
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
						//now load the settings of that tool from it's own function...
						//Tool_Type_Manager.load_tools(num_command);
						load_tools(num_command);
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

bool tool_manager::load_tools(string folderpath)
{
	tool new_tool; //The tool we're going to create

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
			if(command == "NAME") //Found the entry that specifies the tool's name.
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
						tool_name = num_command; //Assign the new tool's name.
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
			else if(command == "ID") //Found the entry that specifies the tool's ID.
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
						tool_id = atoi(num_command.c_str()); //Assign the tool's ID.
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
			else if(command == "IS_TOOL") //Found the entry that specifies whether or not the tool is a tool.
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
						if(num_command == "TRUE" || "true")
						{
							tool_is_tool = true; //The new tool is a tool.
						}
						else
						{
							tool_is_tool = false; //The new tool is not a tool.
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
			else if(command == "IS_WEAPON") //Found the entry that specifies whether or not the tool is a weapon.
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
						if(num_command == "TRUE" || "true")
						{
							tool_is_weapon = true; //The new tool is a weapon.
						}
						else
						{
							tool_is_weapon = false; //The new tool is not a weapon.
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
			else if(command == "CAN_DRILL_WALL") //Found the entry that specifies whether or not the tool can drill walls.
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
						if(num_command == "TRUE" || "true")
						{
							tool_can_drill_wall = true; //The new tool can drill walls.
						}
						else
						{
							tool_can_drill_wall = false; //The new tool can't drill walls..
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
			else if(command == "CAN_DRILL_GROUND") //Found the entry that specifies whether or not the tool can drill ground.
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
						if(num_command == "TRUE" || "true")
						{
							tool_can_drill_ground = true; //The new tool can drill ground.
						}
						else
						{
							tool_can_drill_ground = false; //The new tool can't drill ground..
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
			else if(command == "CAN_CLEAR_RUBBLE") //Found the entry that specifies whether or not the tool can clear rubble.
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
						if(num_command == "TRUE" || "true")
						{
							tool_can_clear_rubble = true; //The new tool can clear rubble.
						}
						else
						{
							tool_can_clear_rubble = false; //The new tool can't clear rubble.
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
			else if(command == "DEFAULT_DAMAGE") //Found the entry that specifies the tool's default damage.
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
						tool_default_damage = atoi(num_command.c_str()); //Assign the default damage
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
			else if(command == "JETPACK") //Found the entry that specifies whether or not the tool is a jetpack.
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
						if(num_command == "TRUE" || "true")
						{
							tool_jetpack = true; //The new tool is a jetpack.
						}
						else
						{
							tool_jetpack = false; //The new tool isn't a jetpack.
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
			else if(command == "JETPACK_DURATION") //Found the entry that specifies the tool's jetpack duration.
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
						tool_jetpack_duration = atoi(num_command.c_str());
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
			else if(command == "DRILL_RATE") //Found the entry that specifies how much damage it inflicts on a tile per frame.
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
						tool_drill_rate = atoi(num_command.c_str()); //Assign the tool's drill rate.
						out_string << "Drill rate 2: " << tool_drill_rate << "\n";
						out_string << "Drill rate 3: " << num_command << "\n";
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
			else if(command == "RUBBLE_CLEAR_TIME") //Found the entry that specifies how long it takes the tool to clear rubble.
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
						tool_rubble_clear_time = atoi(num_command.c_str()); //Assign how long it takes the tool to clear rubble.
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
			else if(command == "DRILL_POWER") //Found the entry that specifies the drill's power.
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
						tool_drill_power = atoi(num_command.c_str()); //Assign the drill's power
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
			else if(command == "CAN_CHOP_TREE")
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
						cout << "This tool is a chopper? " << num_command << "\n";
						out_string << "This tool is a chopper? " << num_command << "\n";
						if(num_command == "TRUE" || num_command == "true")
						{
							tool_can_chop_tree = true;
						}
						else
						{
							tool_can_chop_tree = false;
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
			else if(command == "CHOP_POWER")
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
						tool_drill_power = atoi(num_command.c_str());
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
			else if(command == "CHOP_RATE")
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
						tool_drill_rate = atoi(num_command.c_str());
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
			else if(command == "DEFAULT_RUBBLE_DAMAGE")
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
						tool_default_rubble_damage = atoi(num_command.c_str());
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
			else if(command == "SHOVEL_RATE") //NOTE: THIS IS NOW OBSOLETE!!!
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
						tool_shovel_rate = atoi(num_command.c_str());
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
			else if(command == "SHOVEL_POWER")
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
						tool_shovel_power = atoi(num_command.c_str());
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

	//Time to load the tool's sprite.
	filepath = folderpath + "/icon.png";//The path to the icon...
	tool_icon_sprite = img_load3(filepath); //Load the icon.

	new_tool.init(tool_id, tool_is_tool, tool_is_weapon, tool_can_drill_wall, tool_can_drill_ground, tool_can_clear_rubble, tool_default_damage, tool_jetpack, tool_jetpack_duration, tool_icon_sprite, tool_drill_rate, tool_drill_power, tool_can_chop_tree, tool_default_rubble_damage, tool_shovel_rate, tool_shovel_power); //Initialize the new tool.
	tool_list.push_back(new_tool);

	return true;
}

tool tool_manager::get_by_id(int ID) //Returns a copy of the tool type that has the specified ID.
{
	vector<tool>::iterator iterator; //Used for navigating tool_type_list
	int counter = 0; //Used in the for loop below...

	for(iterator = tool_list.begin(); iterator < tool_list.end(); iterator++, counter++) //Loop through tool_type_list
	{
		if(tool_list[counter].type_id == ID) //If it found the tool_type it's looking for..
		{
			cout << "Found the requested tool type!\n"; //Debugging output
			out_string << "Found the requested tool type!\n";

			return tool_list[counter]; //Return with a copy of the tool_type with the specified ID.
		}
	}

	tool temp; //Couldn't find a tool_type with that ID. So we create this...
	temp.name = " "; //Give it a name that means NULL.
	cout << "Didn't find the requested tool type.\n"; //Debugging output
	out_string << "Didn't find the requested tool type.\n";
	return temp; //And return that...
}

tool_manager Tool_Type_Manager; //Manages all the tool types.
