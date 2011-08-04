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
//			else if(command == "ID") //Found the entry that specifies the unit's ID.
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
///						quit = true;
//						unit_type = atoi(num_command.c_str()); //Assign the unit's type/ID.
//						std::cout << "Unit type's ID: " << unit_type << "\n";
//						out_string << "Unit type's ID: " << num_command << "\n";
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
			else if(command == "MOVE_ANIMATION_LEFT") //Found the entry that specifies where the unit's moving left animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the moving left animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.move_left = new animation; //Create the new animation.
						*new_unit.move_left = new_animation; //Assign the new animation.
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
			else if(command == "MOVE_ANIMATION_RIGHT") //Found the entry that specifies where the unit's moving right animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the moving right animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.move_right = new animation; //Create the new animation.
						*new_unit.move_right = new_animation; //Assign the new animation.
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
			else if(command == "MOVE_ANIMATION_UP") //Found the entry that specifies where the unit's moving up animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the moving up animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.move_up = new animation; //Create the new animation.
						*new_unit.move_up = new_animation; //Assign the new animation.
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
			else if(command == "MOVE_ANIMATION_DOWN") //Found the entry that specifies where the unit's moving down animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the moving down animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.move_down = new animation; //Create the new animation.
						*new_unit.move_down = new_animation; //Assign the new animation.
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
			else if(command == "CARRYORE_ANIMATION_LEFT") //Found the entry that specifies where the unit's carrying ore left animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the carrying ore left animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.move_left_carryore = new animation; //Create the new animation.
						*new_unit.move_left_carryore = new_animation; //Assign the new animation.
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
			else if(command == "CARRYORE_ANIMATION_RIGHT") //Found the entry that specifies where the unit's carrying ore right animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the carrying ore right animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.move_right_carryore = new animation; //Create the new animation.
						*new_unit.move_right_carryore = new_animation; //Assign the new animation.
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
			else if(command == "CARRYORE_ANIMATION_UP") //Found the entry that specifies where the unit's carrying ore up animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the carrying ore up animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.move_up_carryore = new animation; //Create the new animation.
						*new_unit.move_up_carryore = new_animation; //Assign the new animation.
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
			else if(command == "CARRYORE_ANIMATION_DOWN") //Found the entry that specifies where the unit's carrying ore down animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the carrying ore down animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.move_down_carryore = new animation; //Create the new animation.
						*new_unit.move_down_carryore = new_animation; //Assign the new animation.
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
			else if(command == "TAKEOUT_DRILL_ANIMATION_LEFT") //Found the entry that specifies where the unit's takeout drill left animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the takeout drill left animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.takeout_drill_left = new animation; //Create the new animation.
						*new_unit.takeout_drill_left = new_animation; //Assign the new animation.
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
			else if(command == "TAKEOUT_DRILL_ANIMATION_RIGHT") //Found the entry that specifies where the unit's takeout drill right animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the takeout drill right animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.takeout_drill_right = new animation; //Create the new animation.
						*new_unit.takeout_drill_right = new_animation; //Assign the new animation.
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
			else if(command == "TAKEOUT_DRILL_ANIMATION_UP") //Found the entry that specifies where the unit's takeout drill up animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the takeout drill up animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.takeout_drill_up = new animation; //Create the new animation.
						*new_unit.takeout_drill_up = new_animation; //Assign the new animation.
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
			else if(command == "TAKEOUT_DRILL_ANIMATION_DOWN") //Found the entry that specifies where the unit's takeout drill down animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the takeout drill down animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.takeout_drill_down = new animation; //Create the new animation.
						*new_unit.takeout_drill_down = new_animation; //Assign the new animation.
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
			else if(command == "TAKEOUT_DRILL_TIME") //Found the entry that specifies the unit's move speed.
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
						new_unit.take_out_drill_time = atoi(num_command.c_str());
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
			else if(command == "DRILL_ANIMATION_LEFT") //Found the entry that specifies where the unit's drill left animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the drill left animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.drill_left = new animation; //Create the new animation.
						*new_unit.drill_left = new_animation; //Assign the new animation.
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
			else if(command == "DRILL_ANIMATION_RIGHT") //Found the entry that specifies where the unit's drill right animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the drill right animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.drill_right = new animation; //Create the new animation.
						*new_unit.drill_right = new_animation; //Assign the new animation.
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
			else if(command == "DRILL_ANIMATION_UP") //Found the entry that specifies where the unit's drill up animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the drill up animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.drill_up = new animation; //Create the new animation.
						*new_unit.drill_up = new_animation; //Assign the new animation.
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
			else if(command == "DRILL_ANIMATION_DOWN") //Found the entry that specifies where the unit's drill down animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the drill down animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.drill_down = new animation; //Create the new animation.
						*new_unit.drill_down = new_animation; //Assign the new animation.
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
			else if(command == "DRILL_TIME") //Found the entry that specifies the unit's drill time.
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
						new_unit.drill_time = atoi(num_command.c_str());
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
			else if(command == "SHOVEL_ANIMATION") //Found the entry that specifies where the unit's shovel animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the shovel animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.shovel_animation = new animation; //Create the new animation.
						*new_unit.shovel_animation = new_animation; //Assign the new animation.
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
			else if(command == "SHOVEL_TIME") //Found the entry that specifies the unit's shovel time.
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
						new_unit.shovel_time = atoi(num_command.c_str());
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
			else if(command == "PICKUP_ANIMATION") //Found the entry that specifies where the unit's pickup animation's cfg is located.
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

						out_string << "Kay, I found the stuff that has to do with the pickup animation of the unit.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_unit.pick_up = new animation; //Create the new animation.
						*new_unit.pick_up = new_animation; //Assign the new animation.
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
			else if(command == "PICKUP_TIME") //Found the entry that specifies the unit's pickup time.
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
						new_unit.pickup_time = atoi(num_command.c_str());
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
	if(!img_load_safe(filepath, &unit_sprite_select))
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

	//new_unit.init(unit_type, unit_sprite, unit_name, unit_sprite_select, unit_selectable, unit_move_speed, unit_max_health); //Initialize the new unit.
	new_unit.init(0, unit_sprite, unit_name, unit_sprite_select, unit_selectable, unit_move_speed, unit_max_health); //Initialize the new unit.

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
