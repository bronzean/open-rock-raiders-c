/* Copyright the ORR-C Dev Team */
#include "parser.hpp"
#include "EObject.hpp"

bool parser::parse_map_cfg2(const char filepath[200])
{
	string command; //When it isn't a comment, it appends everything to this. Then this is checked to see fi ti matches any commands.
	string num_command; //If the command takes parameters, here they are stored.
	comment = true; //Did a comment start?
	bool check_command = false; //Is it time to check a command?

	file = fopen(filepath, "r");
	if(file == NULL)
	{
		cout << "The file \"" << filepath << "\" does not exist!\n";
		return false;
	}
	cout << "Filepath is: " << filepath << "\n";
	c = 0;

	while (c != EOF)
	{
        	c = getc(file);
		temp = (char) c;
		temp2 = temp;

		if(temp2 == ']' || temp == '\n')
		{
			comment = true;
			check_command = true;
		}
		if(!comment)
		{
			command += temp2;
		}

		if(temp2 == '[')
		{
			comment = false;
		}

		if(check_command)
		{
			if(command == "NUM_COL")
			{
				std::cout << "\nEncountered the option that specifies the number of columns.\n";

				bool quit = false;
				bool start = false; //Start recording parameter?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						num_col_objects = atoi(num_command.c_str());
						std::cout << "\ncol objects = " << num_col_objects << "\n";
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
			else if(command == "NUM_ROW")
			{
				std::cout << "\nEncountered the option that specifies the number of rows.\n";

				bool quit = false;
				bool start = false;

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						num_row_objects = atoi(num_command.c_str());
						std::cout << "\nrow objects = " << num_row_objects << "\n";
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
			else if(command == "LAYERS")
			{
				std::cout << "\nEncountered the option that specifies the number of layers.\n";

				bool quit = false;
				bool start = false;

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						num_layers = atoi(num_command.c_str());
						std::cout << "\nNumber of layers = " << num_layers << "\n";
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
			else if(command == "CAMERA")
			{
				std::cout << "\nEncountered the option that specifies the location of the game camera.\n";

				bool quit = false;
				bool start = false;

				int paramater = 0; //What paramater is it at?

				while(c != EOF && quit == false)
				{
					c = getc(file);
					temp = (char) c;

					if(temp == ')')
					{
						start = false;
						if(paramater == 0)
						{
							PCamera->wx = atoi(num_command.c_str());
							cout << "WX: " << PCamera->wx << "\n";
							paramater++;
						}
						else if(paramater == 1)
						{
							PCamera->wy = atoi(num_command.c_str());
							cout << "WY: " << PCamera->wy << "\n";
							paramater++;
						}
						else if(paramater == 2)
						{
							PCamera->layer = atoi(num_command.c_str()) - 1;
							cout << "LAYER: " << PCamera->layer << "\n";
						}
						num_command = "";
					}
					else if(temp == '\n')
					{
						start = false;
						quit = true;
                                                current_layer_string.str(""); //Reset current_layer_string so that it doesn't keep expanding it with new messages.
                                                current_layer_string << "Current layer: " << PCamera->layer; //The text that informs the player what layer they're on.
                                                current_layer_sprite = TTF_RenderText_Solid(font1, current_layer_string.str().c_str(), c_white); //Render the current layer message onto current_layer_sprite.
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

	num_tiles = ((num_col_objects) * (num_row_objects) * (num_layers));

	fclose(file);
	return true;
}

bool parser::parse_map_layer(const char folderpath[200]) //TODO: Finish this
{
	string stage[3]; //The contents of that stage are placed into this.
	int read_stage = 0; //What stage of the line has been read? Look at the comment before this function to see what I mean.
	string stage_object[4]; //The contents of the stages in the object parser thinbg are placed here.
	int current_tile = 0; //At what tile is it?
	bool parse_tile = false; //Once it finishes reading a tile, it creates the tile.

	string cur_layer;
	cur_layer = "0";
	int cur_layer_int = 0;

	for(cur_layer_int = 0; cur_layer_int < num_layers; cur_layer_int++)
	{
		for(int i = 0; i < 3; i++)
		{
			stage[i] = "";
		}

		//cout << "\nParsing layers...\n";

		stringstream out;
		out << cur_layer_int;
		cur_layer = out.str();

		string filepath;
		filepath = folderpath;
		//cout << "\nFolder path is: " << folderpath << "\n";
		filepath += "l";
		filepath += cur_layer;

		file = fopen(filepath.c_str(), "r");
		if(file == NULL)
		{
			cout << "The file \"" << filepath << "\" does not exist!\n";
			out_string << "The file \"" << filepath << "\" does not exist!\n";
			return false;
		}
		//cout << "Filepath is: " << filepath << "\n";
		//out_string << "Filepath is: " << filepath << "\n";
		c = 0;

		int w = 0;
		int h = 0;
		if(cur_layer_int > 0)
		{
			c = 1; //If the current layer is greater than 1, set c to start at 1. Why? If I don't, it reads extra junk and the tile in the top left corner of the map becomes ground.
		}

		int tiles_per_loop = 0; //How many tiles were made in that loops

		while (c != EOF)
		{
			c = getc(file);
				
        				
			temp = (char) c;

			cout.flush();
			if(temp == '.' || temp == ',')
			{
				read_stage ++;
			}
			else if(temp == '\n')
			{
				read_stage = 0;
				parse_tile = true;
			}
			else if(temp == ' ')
			{
				read_stage = 0;
				parse_tile = true;
			}
			else
			{
				stage[read_stage] += temp;
			}

			cout.flush();

			if(parse_tile)
			{
				tile new_tile; //The tile we are are going to add to the map.

				new_tile.type_id = atoi(stage[0].c_str()); //This gives the tile its type.

				tile new_tile_temp = Tile_Type_Manager.get_by_id(new_tile.type_id); //Grab the tile's properties.

				if(new_tile_temp.name == " ") //If it failed to grab the ID...
				{
					cout << "Unkown tile type: " << new_tile.type_id << "\n"; //Debugging output
					out_string << "Unkown tile type: " << new_tile.type_id << "\n";
					return false; //Let the caller now it failed.
				}
				else
				{
					new_tile = new_tile_temp; //Assign this tile's properties...
				}

				
				new_tile.layer = cur_layer_int; //Assigns the tile its layer.
				new_tile.ID = current_tile; //Assign its ID.
				new_tile.wx = w * 32; //This gives the tile its world x.
				new_tile.wy = h * 32; //This gives the tile its world y.
				new_tile.width = new_tile.sprite->w;
				new_tile.height = new_tile.sprite->h;
				new_tile.sprite = new_tile_temp.sprite;
						

				for(int i = 0; i < 3; i++)
				{
					stage[i] = "";
				}
				current_tile ++;
				parse_tile = false;
				if(w >= num_row_objects - 1)
				{
					w = 0;
					h++;
				}
				else
				{
					w++;
				}

				
				tiles_per_loop++;

				Map.push_back(new_tile); //Add the new tile to the map.
			}

			cout.flush();
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string
		}


		fclose(file);

		//cout << "\nParsing object layers...\n";

		stringstream out2;
		out2 << cur_layer_int;
		cur_layer = out2.str();

		string filepath2;
		filepath2 = folderpath;
		//cout << "\nFolder path is: " << folderpath << "\n";
		filepath2 += "ol";
		filepath2 += cur_layer;

		bool load_objects = true;

		file = fopen(filepath2.c_str(), "r");
		if(file == NULL)
		{
			cout << "The file \"" << filepath2 << "\" does not exist!\n";
			out_string << "The file \"" << filepath2 << "\" does not exist!\n";
			//return false;
			load_objects = false;
		}
		//cout << "Filepath is: " << filepath2 << "\n";
		c = 0;

		if(load_objects == true)
		{
		while (c != EOF)
		{
        		c = getc(file);
			temp = (char) c;

			cout.flush();

			if(temp == '.')
			{
				read_stage ++;
			}
			else if(temp == '\n')
			{
				read_stage = 0;
				parse_tile = true;
			}
			else if(temp == ' ')
			{
				read_stage = 0;
				parse_tile = true;
			}
			else
			{
				stage_object[read_stage] += temp;
			}

			cout.flush();
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string

			/*object maps:

			unit_id.tile_number.starts_with_tool.tool_id
			if starts_with_tool == 0, it doesn't start with a tool
			if starts_with tool == anything else, then it does start with the tool specified in tool_id
			example:
			0.100.1.0
			Unit with ID: 0 starting on tile with ID: 100 and is carrying a tool with ID: 0

			*/

			
			if(parse_tile)
			{
				bClassUnit temp_unit = Unit_Type_Manager.get_by_id(atoi(stage_object[0].c_str())); //Grab the unit that has the same ID as this guy.

				//First check if stage_object[0] == something_in_unittypelist
				if(stage_object[0] != "" && temp_unit.name != " ")
				{
					bClassUnit newUnit = temp_unit;
					newUnit.wx = Map[atoi(stage_object[1].c_str())].wx; //Assign the new unit's world x.
					newUnit.wy = Map[atoi(stage_object[1].c_str())].wy; //Assign the new unit's world y.
					newUnit.layer = Map[atoi(stage_object[1].c_str())].layer; //Assign the new unit's layer.
					newUnit.c_health = 100; //Assign the new unit's current health.					
					//std::cout << "Created new unit.\n";

					if(stage_object[2] != "0")
					{
						tool new_tool = Tool_Type_Manager.get_by_id(atoi(stage_object[3].c_str())); //Find the tool with the specified ID.
						newUnit.tool_list.push_back(new_tool); //Add the tool it found to the new unit's tool list.

						if(newUnit.tool_list[newUnit.tool_list.size() - 1].can_drill_wall == true) //Check if the raider is carying a drill.
						{
							newUnit.wall_popup_menu = new popup_menu;
							newUnit.wall_popup_menu->fields.push_back(field_drill_wall); //Add this to the unit's popup menu.
							newUnit.wall_popup_menu->fields[newUnit.wall_popup_menu->fields.size() - 1].set_parent_menu(newUnit.wall_popup_menu); //Let the new field know what popup_menu contains it.
						}

						newUnit.rubble_popup_menu = new popup_menu;
						newUnit.rubble_popup_menu->fields.push_back(field_moveto); //Add this to the unit's popup menu.
						newUnit.rubble_popup_menu->fields[newUnit.rubble_popup_menu->fields.size() - 1].set_parent_menu(newUnit.rubble_popup_menu); //Let the new field know what popup_menu contains it.

						if(newUnit.tool_list[newUnit.tool_list.size() - 1].can_clear_rubble == true) //Check if the raider is carying a shovel.
						{
							newUnit.rubble_popup_menu->fields.push_back(field_shovel_rubble); //Add this to the unit's popup menu.
							newUnit.rubble_popup_menu->fields[newUnit.rubble_popup_menu->fields.size() - 1].set_parent_menu(newUnit.rubble_popup_menu); //Let the new field know what popup_menu contains it.
						}
					}

					Map[atoi(stage_object[1].c_str())].unitlist.push_back(newUnit);

					//Map[atoi(stage_object[1].c_str())].unitlist[Map[atoi(stage_object[1].c_str())].unitlist.size()].init(); //Initialise the unit.

					Active_Map.push_back(Map[atoi(stage_object[1].c_str())].ID); //Add this tile's index to Active_Map to know that this tile requires updating.
					Map[atoi(stage_object[1].c_str())].Active_Map_Entry = Active_Map.size() - 1; //Let the tile know where its entry in Actve_Map is.
					
				}

				parse_tile = false;
				for(int i = 0; i <= 3; i++)
				{
					stage_object[i] = "";
				}
			}
			cout.flush();
			fwrite(out_string.str().c_str(), 1, strlen(out_string.str().c_str()), GameLog);
			fflush(GameLog);
			out_string.str(""); //Reset out_string
		}

		fclose(file);
		}
	}
	return true;
}

parser Parser;
