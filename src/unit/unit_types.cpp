/* Copyright the ORR-C Dev Team */
#include "unit.hpp"
#include "../library/cfg/parser.hpp"
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
				unit_list[unit_list.size() - 1].type_id = atoi(command.c_str()); //Assign the unit type's ID.
				cout << "ID of new unit: " << command << ". Confirmation: " << unit_list[unit_list.size() - 1].type_id << "\n";
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

	string filepath = folderpath + "/config";//The path to the config file...

	vector<cfg::variable> variables;

	if(!cfg::parse_config_file(filepath, &variables)) //Parses the cfg.
	{
		cout << "Failed to load object's cfg.\n"; //Tell the user it failed.

		return false; //Abort! Abort!
	}

	for(int i = 0; i < variables.size(); i++) //Loop through the variable list.
	{
		if(variables[i].name == "NAME") //Found the entry that specifies the unit's name.
		{
			new_unit.name = variables[i].values[0]; //Assign the new unit's name.
		}
		else if(variables[i].name == "SELECTABLE") //Found the entry that specifies whether or not this unit can be selected.
		{
			out_string << "Encountered selectable...\n";
			if(variables[i].values[0] == "TRUE" || variables[i].values[0] == "true") //Check if the stuff inside the parantheses is telling the game that this unit can be selected.
			{
				new_unit.selectable = true;
				out_string << "Selectable.\n";
			}
			else
			{
				new_unit.selectable = false; //Can't touch that. Er, can't select this unit.
				out_string << "Not selectable.\n";
			}
		}
		else if(variables[i].name == "MOVE_SPEED") //Found the entry that specifies the unit's move speed.
		{
			new_unit.move_speed = atoi(variables[i].values[0].c_str()); //The base movement speed. And by base, I mean foundation, not your super epic base. The 'fancy' atoi function simply converts the string to an integer.
		}
		else if(variables[i].name == "MAX_HEALTH") //Found the entry that specifies the unit's max health.
		{
			new_unit.m_health = atoi(variables[i].values[0].c_str()); //This will soon get replaced with a realistic health system. For now, set the unit's max health to this. The 'fancy' atoi function simply converts the string to an integer.
		}
		else if(variables[i].name == "TELEPORT_IN_TIME") //Found the entry that specifies the unit's teleport time.
		{
			new_unit.teleport_in_time = atoi(variables[i].values[0].c_str()); //Set the unit's teleport in time. The 'fancy' atoi function simply converts the string to an integer.
		}
		else if(variables[i].name == "PICKUP_TIME") //Found the entry that specifies the unit's pickup time.
		{
			new_unit.pickup_time = atoi(variables[i].values[0].c_str()); //Set the unit's pickup time. The 'fancy' atoi function simply converts the string to an integer.
		}
		else if(variables[i].name == "SHOVEL_TIME") //Found the entry that specifies the unit's shovel time.
		{
			new_unit.shovel_time = atoi(variables[i].values[0].c_str()); //Set the unit's shovel time. The 'fancy' atoi function simply converts the string to an integer.
		}
		else if(variables[i].name == "TAKEOUT_DRILL_TIME") //Found the entry that specifies the unit's take out drill time.
		{
			new_unit.take_out_drill_time = atoi(variables[i].values[0].c_str());
		}
		else if(variables[i].name == "DRILL_TIME") //Found the entry that specifies the unit's drill time.
		{
			new_unit.drill_time = atoi(variables[i].values[0].c_str()); //Set the unit's drill time. The 'fancy' atoi function simply converts the string to an integer.
		}
		else if(variables[i].name == "MOVE_ANIMATION_LEFT") //Found the entry that specifies where the unit's moving left animation's cfg is located.
		{
			animation new_animation; //Placeholder animation.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Lots of debugging output.
			out_string << "Kay, I found the stuff that has to do with the moving left animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.move_left = new animation; //Allocate space for the new animation.
			*new_unit.move_left = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "MOVE_ANIMATION_RIGHT") //Found the entry that specifies where the unit's moving right animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Lots of *hopefully* useful debugging output.
			out_string << "Kay, I found the stuff that has to do with the moving right animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.move_right = new animation; //Allocate space for the new animation.
			*new_unit.move_right = new_animation; //Assign the new animation.

		}
		else if(variables[i].name == "MOVE_ANIMATION_UP") //Found the entry that specifies where the unit's moving up animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Lots of useful debugging output.
			out_string << "Kay, I found the stuff that has to do with the moving up animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.move_up = new animation; //Allocate space for the new animation.
			*new_unit.move_up = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "MOVE_ANIMATION_DOWN") //Found the entry that specifies where the unit's moving down animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Lots of debugging output. Nuff said.
			out_string << "Kay, I found the stuff that has to do with the moving down animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.move_down = new animation; //Allocate space for the new animation.
			*new_unit.move_down = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "CARRYORE_ANIMATION_LEFT") //Found the entry that specifies where the unit's carrying ore left animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output.
			out_string << "Kay, I found the stuff that has to do with the carrying ore left animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.move_left_carryore = new animation; //Allocate space for the new animation.
			*new_unit.move_left_carryore = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "CARRYORE_ANIMATION_RIGHT") //Found the entry that specifies where the unit's carrying ore right animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output.
			out_string << "Kay, I found the stuff that has to do with the carrying ore right animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.move_right_carryore = new animation; //Allocate space for the new animation.
			*new_unit.move_right_carryore = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "CARRYORE_ANIMATION_UP") //Found the entry that specifies where the unit's carrying ore up animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output.
			out_string << "Kay, I found the stuff that has to do with the carrying ore up animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.move_up_carryore = new animation; //Allocate space for the new animation.
			*new_unit.move_up_carryore = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "CARRYORE_ANIMATION_DOWN") //Found the entry that specifies where the unit's carrying ore down animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output.
			out_string << "Kay, I found the stuff that has to do with the carrying ore down animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.move_down_carryore = new animation; //Allocate space for the new animation.
			*new_unit.move_down_carryore = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "TAKEOUT_DRILL_ANIMATION_LEFT") //Found the entry that specifies where the unit's takeout drill left animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output.
			out_string << "Kay, I found the stuff that has to do with the takeout drill left animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.takeout_drill_left = new animation; //Allocate space for the new animation.
			*new_unit.takeout_drill_left = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "TAKEOUT_DRILL_ANIMATION_RIGHT") //Found the entry that specifies where the unit's takeout drill right animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Has it really come to this?
			out_string << "Kay, I found the stuff that has to do with the takeout drill right animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.takeout_drill_right = new animation; //Allocate space for the new animation.
			*new_unit.takeout_drill_right = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "TAKEOUT_DRILL_ANIMATION_UP") //Found the entry that specifies where the unit's takeout drill up animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Why am I the one left doing this?
			out_string << "Kay, I found the stuff that has to do with the takeout drill up animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.takeout_drill_up = new animation; //Allocate space for the new animation.
			*new_unit.takeout_drill_up = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "TAKEOUT_DRILL_ANIMATION_DOWN") //Found the entry that specifies where the unit's takeout drill down animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//CAN'T YOU GUYS SEE IT'S DEBUGGING OUTPUT???
			out_string << "Kay, I found the stuff that has to do with the takeout drill down animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.takeout_drill_down = new animation; //Allocate space for the new animation.
			*new_unit.takeout_drill_down = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "DRILL_ANIMATION_LEFT") //Found the entry that specifies where the unit's drill left animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output.
			out_string << "Kay, I found the stuff that has to do with the drill left animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.drill_left = new animation; //Allocate space for the new animation.
			*new_unit.drill_left = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "DRILL_ANIMATION_RIGHT") //Found the entry that specifies where the unit's drill right animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//More Debugging output.
			out_string << "Kay, I found the stuff that has to do with the drill right animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.drill_right = new animation; //Allocate space for the new animation.
			*new_unit.drill_right = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "DRILL_ANIMATION_UP") //Found the entry that specifies where the unit's drill up animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output's debut.
			out_string << "Kay, I found the stuff that has to do with the drill up animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.drill_up = new animation; //Allocate space for the new animation.
			*new_unit.drill_up = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "DRILL_ANIMATION_DOWN") //Found the entry that specifies where the unit's drill down animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output.
			out_string << "Kay, I found the stuff that has to do with the drill down animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.drill_down = new animation; //Allocate space for the new animation.
			*new_unit.drill_down = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "SHOVEL_ANIMATION") //Found the entry that specifies where the unit's shovel animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output.
			out_string << "Kay, I found the stuff that has to do with the shovel animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.shovel_animation = new animation; //Allocate space for the new animation.
			*new_unit.shovel_animation = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "PICKUP_ANIMATION") //Found the entry that specifies where the unit's pickup animation's cfg is located.
		{
			animation new_animation; //The new animation that's going to be added to the animations vector.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output.
			out_string << "Kay, I found the stuff that has to do with the pickup animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.pick_up = new animation; //Allocate space for the new animation.
			*new_unit.pick_up = new_animation; //Assign the new animation.
		}
		else if(variables[i].name == "TELEPORT_IN_ANIMATION") //Found the entry that specifies where the unit's teleport animation's cfg is located.
		{
			animation new_animation; //The new animation.

			new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

			//Debugging output...
			out_string << "Kay, I found the stuff that has to do with the teleport in animation of the unit.\n";
			out_string << "Folderpath: " << new_animation.folder_path << "\n";
			out_string << "CFG path: " << new_animation.folder_path + variables[i].values[0] << "\n\n";

			new_animation.load_settings(new_animation.folder_path + variables[i].values[0]); //Load the animation's settings.

			new_unit.teleport_in_animation = new animation; //Allocate space for the new animation.
			*new_unit.teleport_in_animation = new_animation; //Assign the new animation.
		}
		else
		{
			out_string << "Unknown variable for this object!!!\n";
			out_string << "Variable: " << variables[i].name << "\n";
		}
	}


	//Time to load the unit's sprite.
	filepath = folderpath + "/sprite.png";//The path to the sprite...
	if(!img_load_safe(filepath, &new_unit.sprite))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		return false;
	}
	filepath = folderpath + "/sprite_left.png"; //The path to the left sprite.
	if(!img_load_safe(filepath, &new_unit.sprite_left))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		new_unit.sprite_left = NULL;
	}
	filepath = folderpath + "/sprite_right.png"; //The path to the right sprite.
	if(!img_load_safe(filepath, &new_unit.sprite_right))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		new_unit.sprite_right = NULL;
	}
	filepath = folderpath + "/sprite_up.png"; //The path to the up sprite.
	if(!img_load_safe(filepath, &new_unit.sprite_up))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		new_unit.sprite_up = NULL;
	}

	filepath = folderpath + "/sprite_select.png"; //The path to the selected sprite.
	//unit_sprite_select = img_load(filepath); //Load the selected sprite.
	if(!img_load_safe(filepath, &new_unit.sprite_select))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		return false;
	}

	filepath = folderpath + "/sprite_ore_left.png"; //The path to the ore left.
	if(!img_load_safe(filepath, &new_unit.sprite_ore_left))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		new_unit.sprite_ore_left = NULL;
	}
	filepath = folderpath + "/sprite_ore_right.png"; //The path to the ore right.
	if(!img_load_safe(filepath, &new_unit.sprite_ore_right))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		new_unit.sprite_ore_right = NULL;
	}
	filepath = folderpath + "/sprite_ore_up.png"; //The path to the ore up.
	if(!img_load_safe(filepath, &new_unit.sprite_ore_up))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		new_unit.sprite_ore_up = NULL;
	}
	filepath = folderpath + "/sprite_ore_down.png"; //The path to the ore down.
	if(!img_load_safe(filepath, &new_unit.sprite_ore_down))
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		new_unit.sprite_ore_down = NULL;
	}

	new_unit.carrying_message_sprite = TTF_RenderText_Solid(font1, new_unit.carrying_message_string.c_str(), c_white); //Render the current layer message onto current_layer_sprite.
	new_unit.select_wall_to_mine_spr = TTF_RenderText_Solid(font1, new_unit.select_wall_to_mine_str.c_str(), c_white); //Render the message displayed when the unit enters mining mode.
	new_unit.mining_message_spr = TTF_RenderText_Solid(font2, new_unit.mining_message_str.c_str(), c_green);
	new_unit.select_object_to_pick_up_spr = TTF_RenderText_Solid(font1, new_unit.select_object_to_pick_up_str.c_str(), c_white);
	new_unit.chopping_message_spr = TTF_RenderText_Solid(font2, new_unit.chopping_message_str.c_str(), c_green);
	new_unit.select_tree_to_chop_spr = TTF_RenderText_Solid(font1, new_unit.select_tree_to_chop_str.c_str(), c_white);
	new_unit.shovelling_message_spr = TTF_RenderText_Solid(font2, new_unit.shovelling_message_str.c_str(), c_green);
	new_unit.select_rubble_to_shovel_spr = TTF_RenderText_Solid(font1, new_unit.select_rubble_to_shovel_str.c_str(), c_white);
	new_unit.constructing_message_spr = TTF_RenderText_Solid(font1, new_unit.constructing_message_str.c_str(), c_green);
	new_unit.construct_walking_message_spr = TTF_RenderText_Solid(font1, new_unit.construct_walking_message_str.c_str(), c_green);

	unit_list.push_back(new_unit);

	return true;
}

bClassUnit unit_type_manager::get_by_id(int ID) //Returns a copy of the unit type that has the specified ID.
{
	vector<bClassUnit>::iterator iterator; //Used for navigating the unit list
	int counter = 0; //Used in the loop below...

	for(iterator = unit_list.begin(); iterator < unit_list.end(); iterator++, counter++) //Loop through the unit list
	{
		if(unit_list[counter].type_id == ID) //If it found the unit it's looking for...
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
