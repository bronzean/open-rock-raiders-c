/* Copyright the ORR-C Dev Team */
#include "tile.hpp"
using namespace std;

//Add a new tile type.
void tile_manager::add_tile_type(int ID, SDL_Surface *SPRITE, std::string NAME, bool WALL, bool RAMP, bool UP_RAMP, bool DOWN_RAMP, bool SELF_SUPPORTING, int ORE_TYPE, bool CAN_MINE, int MINIMUMN_MINING_POWER, bool AIR, bool TURN_TO_GROUND, int GROUND_TYPE, bool GENERATE_ORE_ON_MINE, int NUM_ORE_TO_GENERATE/*, std::vector<int> HEALTH*/, bool TREE, bool RUBBLE/*, int HEALTH_PER_SHOVEL*/)
{
	tile new_tile; //The new tile type.

	new_tile.init(ID, SPRITE, NAME, WALL, RAMP, UP_RAMP, DOWN_RAMP, SELF_SUPPORTING, ORE_TYPE, CAN_MINE, MINIMUMN_MINING_POWER, AIR, TURN_TO_GROUND, GROUND_TYPE, GENERATE_ORE_ON_MINE, NUM_ORE_TO_GENERATE, TREE, RUBBLE/*, HEALTH_PER_SHOVEL*/); //Initialize it...

	//And, finally, add it to tile type list.
	tile_list.push_back(new_tile);
}

bool tile_manager::load_types_from_file(std::string filepath) //Loads all the tile types from the files...
{
	cout << "Loading tile types!\n"; //Debugging output.
	out_string << "Loading tile types!\n"; //Debugging output.

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
						//now load the settings of that tilel from it's own function...
						load_tile(num_command);
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
				tile_list[tile_list.size() - 1].type_id = atoi(command.c_str()); //Assign the tile type's ID.
				cout << "ID of new tile: " << command << ". Confirmation: " << tile_list[tile_list.size() - 1].type_id << "\n";
			}
			check_command = false;
			command = "";
		}
	}

	fclose(file);
	return true;
}

bool tile_manager::load_tile(string folderpath)
{
	tile new_tile; //The tile we're going to create

	//--------The new tile's properties.------
	string tile_name = ""; //The new tile's name.
	int tile_type = 0; //The new tile's type/ID.
	SDL_Surface *tile_sprite = NULL; //The new tile's sprite.
	bool tile_ramp = false; //Let's the game know whether or not this tile is a ramp that connects two caverns.
	bool tile_up_ramp = false; //Let's the game know where it leads.
	bool tile_down_ramp = false; //Let's the game know where it leads.
	bool tile_wall = false; //Is it a wall?
	bool tile_self_supporting = true; //Does the wall support itself? As in, doesn't collapse if it's not connected to enough walls/not connected in the right way. False = The way it is in RR. True = Doesn't have ot be connected to any other walls.
	bool tile_can_mine = false; //Can this wall be mined?
	int tile_minimumn_mining_power = 0; //The minimumn power a drill need to be able to mine this wall.
	bool tile_air = false; //Is the tile an air tile?
	bool tile_turn_to_ground = false; //Turn into a ground tile when it is mined?
	int tile_ground_type = 0; //The ID of the ground tile it turns into when mined.
	bool tile_generate_ore_on_mine = false; //Does this tile generate ore when it is mined?
	int tile_num_ore_to_gen = 0; //How much ore does this tile generate when it is mined? This also doubles for the ore per shovel in rubble.
	int tile_ore_type = 0; //What type of ore does this tile generate when mined, if it can be mined?
	/*int tile_health = 0; //The health of the tile. 0 or lower means collapse or something like that. OBSOLETE */
	bool tile_tree = false; //Is this tile a tree?
	bool tile_rubble = false; //Is this tile a rubble tile?
	int tile_ore_per_shovel = 0; //How much ore is produced per shovel.
	int tile_health_per_shovel = 0; //How much health has to be reduced to be considered "one shovel".
	int tile_minimumn_shovelling_power = 0; //The minimumn power of the shovel required to shovel this rubble.
	new_tile.num_shovels = 0; //How many shovels to go until this rubble is shovelled?
	new_tile.total_shovels = 0;
	new_tile.drilling_animation = false;
	new_tile.drilling_animation_entry = 0;
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
			if(command == "NAME") //Found the entry that specifies the tile's name.
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
						tile_name = num_command; //Assign the new tile's name.
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
//			else if(command == "ID") //Found the entry that specifies the tile's ID.
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
//						tile_type = atoi(num_command.c_str()); //Assign the tile's type/ID.
//						std::cout << "Tile type's ID: " << tile_type << "\n";
//						out_string << "Tile type's ID: " << num_command << "\n";
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
			else if(command == "WALL") //Found the entry that specifies whether or not the tile is a wall.
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
							tile_wall = true;
							new_tile.obstruction = true; //This tile is an obstruction.
						}
						else
						{
							tile_wall = false;
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
			else if(command == "DOWN_RAMP") //Found the entry that specifies whether or not the tile is a down ramp
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
							tile_down_ramp = true;
							tile_ramp = true;
						}
						else
						{
							tile_down_ramp = false;
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
			else if(command == "UP_RAMP") //Found the entry that specifies whether or not the tile is an up ramp
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
							tile_up_ramp = true;
							tile_ramp = true;
						}
						else
						{
							tile_up_ramp = false;
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
			else if(command == "SELF_SUPPORTING") //Found the entry that specifies whether or not the tile is self supporting.
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
							tile_self_supporting = true;
						}
						else
						{
							tile_self_supporting = false;
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
			else if(command == "MIN_MINING_POWER") //Found the entry that specifies the tile's minimumn required mining power..
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
						tile_minimumn_mining_power = atoi(num_command.c_str());
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
			else if(command == "CAN_MINE") //Found the entry that specifies whether or not the tile can be mined.
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
							tile_can_mine = true;
						}
						else
						{
							tile_can_mine = false;
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
			else if(command == "AIR") //Found the entry that specifies whether or not the tile is an air tile.
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
							tile_air = true;
						}
						else
						{
							tile_air = false;
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
			else if(command == "TURN_TO_GROUND") //Found the entry that specifies whether or not the tile turns into ground when mined.
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
							tile_turn_to_ground = true;
						}
						else
						{
							tile_turn_to_ground = false;
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
			else if(command == "TO_GROUND_TYPE") //Found the entry that specifies the ID of the ground tile this tile turns into when mined.
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
						tile_ground_type = atoi(num_command.c_str());
						cout << "Ground type: " << num_command << "\n";
						out_string << "Ground type: " << num_command << "\n";
						cout << "Ground type2: " << tile_ground_type << "\n";
						out_string << "Ground type2: " << tile_ground_type << "\n";
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
			else if(command == "GENERATE_ORE_ON_MINE")
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
							tile_generate_ore_on_mine = true;
						}
						else
						{
							tile_generate_ore_on_mine = false;
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
			else if(command == "NUM_ORE") //Found the entry that specifies the number of ore generated when this tile is mine.
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
						tile_num_ore_to_gen = atoi(num_command.c_str());
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
			else if(command == "ORE_TYPE") //Found the entry that specifies the tile's ore type.
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
						tile_ore_type = atoi(num_command.c_str());
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
			else if(command == "HEALTH") //Found the entry that specifies the tile's health.
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n')
					{
						if(start)
						{
							new_tile.health.push_back(atoi(num_command.c_str())); //Add the new health to the health list.
							new_tile.num_shovels++; //Increase the number of shovels the tile has left till it's cleared completely.
							new_tile.total_shovels++;
							out_string << "\nAdding health...\nHealth: "; //Debugging output.
							out_string << num_command << "\n\n"; //Debugging output.
						}
						start = false;
						quit = true;
						out_string << "Num_shovels: " << new_tile.num_shovels << "\n";
						out_string << "Total shovels: "<< new_tile.total_shovels << "\n";
					}
					else if(temp == ')')
					{
						start = false;
						new_tile.health.push_back(atoi(num_command.c_str())); //Add the new health to the health list.
						new_tile.num_shovels++; //Increase the number of shovels the tile has left till it's cleared completely.
						new_tile.total_shovels++;
						out_string << "\nAdding health...\nHealth: "; //Debugging output.
						out_string << num_command << "\n\n"; //Debugging output.
						//out_string << new_tile.health[0] << "\n\n"; //Debugging output.
						num_command = ""; //Reset num_command so that all the values passed don't add up into one string.

						cout << "Health total: \n";
						for(int i2 = 0; i2 < new_tile.num_shovels; i2++)
						{
							cout << new_tile.health[i2] << "\n";
							out_string << "Health: " << new_tile.health[i2] << "\n";
						}
						cout << "\n";
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
			else if(command == "TREE") //Found the entry that specifies whether or not the tile is a tree tile.
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
							tile_tree = true;
						}
						else
						{
							tile_tree = false;
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
			else if(command == "RUBBLE") //Found the entry that specifies whether or not the tile is a tree tile.
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
							tile_rubble = true;
						}
						else
						{
							tile_rubble = false;
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
			else if(command == "TYPES_OF_ORE_GENERATED") //Found the entry that specifies what types of ore this tile can generate...
			{
				bool quit = false; //Controlls the loop below.
				bool start = false; //Start recording the parameter?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n')
					{
						start = false;
						quit = true;
						//TODO: Add the new ore ID.
						new_tile.ore_gen_ids.push_back(atoi(num_command.c_str())); //Add the new ore id to the ore id list
					}
					else if(temp == ')')
					{
						start = false;
						//TODO: Add the new ore id.
						new_tile.ore_gen_ids.push_back(atoi(num_command.c_str())); //Add the new ore id to the ore id list
						out_string << "\nAdding ore ID to whitelist...\nID:"; //Debugging output.
						out_string << num_command << "\n\n"; //Debugging output.
						num_command = ""; //Reset num_command so that all the values passed don't add up into one string.
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
			else if(command == "ORE_PER_SHOVEL")
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
						tile_num_ore_to_gen = atoi(num_command.c_str());
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
			/* -----------------------THIS IS OBSOLETE-------------------
			else if(command == "HEALTH_PER_SHOVEL")
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
						tile_health_per_shovel = atoi(num_command.c_str());
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
			}*/
			else if(command == "MIN_SHOVELLING_POWER") //Found the entry that specifies the tile's minimumn required shovelling power..
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
						tile_minimumn_shovelling_power = atoi(num_command.c_str());
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
			else if(command == "DRILLING_ANIMATION") //Found the entry that specifies where the tile's drilling animation's cfg is located.
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
						//new_animation.init(); //Initialize an empty animation. //Redundant.

						new_animation.folder_path = folderpath + "/"; //Assign the object's folder path.

						out_string << "Kay, I found the stuff that has to do with the drilling animation.\n";
						out_string << "Folderpath: " << new_animation.folder_path << "\n";
						out_string << "CFG path: " << new_animation.folder_path + num_command << "\n\n";

						new_animation.load_settings(new_animation.folder_path + num_command); //Load the animation's settings.

						new_tile.animations.push_back(new_animation); //Add the drill animation to the tile's animation vector.
						new_tile.drilling_animation_entry = new_tile.animations.size() - 1; //Let the game know what the drill animation's location in the animations vector is.
						new_tile.drilling_animation = true; //Let's the game know that the tile has a drilling animation.
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

	//Time to load the tile's sprite.
	filepath = folderpath + "/sprite.png";//The path to the sprite...
	//tile_sprite = img_load3(filepath); //Load the sprite.
	if(!img_load_safe(filepath, &tile_sprite)) //Load the sprite.
	{
		cout << "Sprite filepath " << filepath << " does not exist!\n";
		out_string << "Sprite filepath " << filepath << " does not exist!\n";
		return false;
	}

	new_tile.init(tile_type, tile_sprite, tile_name, tile_wall, tile_ramp, tile_up_ramp, tile_down_ramp, tile_self_supporting, tile_ore_type, tile_can_mine, tile_minimumn_mining_power, tile_air, tile_turn_to_ground, tile_ground_type, tile_generate_ore_on_mine, tile_num_ore_to_gen/*, tile_health*/, tile_tree, tile_rubble/*, tile_health_per_shovel*/); //Initialize the new tile.
	tile_list.push_back(new_tile);

	return true;
}

tile tile_manager::get_by_id(int ID) //Returns a copy of the tile type that has the specified ID.
{
	vector<tile>::iterator iterator; //Used for navigating the tile list
	int counter = 0; //Used in the for loop below...

	for(iterator = tile_list.begin(); iterator < tile_list.end(); iterator++, counter++) //Loop through the tile list
	{
		if(tile_list[counter].type_id == ID) //If it found the tile it's looking for...
		{
			//cout << "Found the requested tile type!\n"; //Debugging output
			//out_string << "Found the requested tile type!\n";

			return tile_list[counter]; //Return with a copy of the tile with the specified ID.
		}
	}

	tile temp; //Couldn't find a tile with that ID. So we create this...
	temp.name = " "; //Give it a name that means NULL.
	cout << "Didn't find the requested tile type.\n"; //Debugging output
	out_string << "Didn't find the requested tile type.\n";
	return temp; //And return that...
}


tile_manager::~tile_manager()
{
	cout << "Freeing the tile types' sprites\n";
	for(int i = 0; i < tile_list.size(); i++) //Free all the sprites.
	{
		SDL_FreeSurface(tile_list[i].sprite);
		for(int j = 0; j < tile_list[i].animations.size(); j++) //Free the animations' sprites.
		{
			for(int h = 0; h < tile_list[i].animations[j].frames_spr.size(); h++)
			{
				SDL_FreeSurface(tile_list[i].animations[j].frames_spr[h]);
			}
		}
	}
}

tile_manager Tile_Type_Manager; //Manages all the tile types.
