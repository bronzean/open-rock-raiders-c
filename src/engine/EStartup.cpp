/* Copright the ORR-C Dev Team */
//Contains all of the startup code
#include "../Engine.hpp"
#include "Interface.hpp"

using namespace std;

bool startup(bool fullscreen, int screen_w, int screen_h, int screen_bpp, std::string screen_capt, bool load_from_cfg)
{
	std::cout << "\nInitializing\n";

	//Initialize everything
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		std::cerr << "\nError initializing SDL\n";
		return false;
	}

	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		std::cerr << "\nError initializing SDL_ttf\n";
		return false;    
	}

	if(load_settings() == false)
	{
		//TODO: Make the error loading more specific and print out the problems to the console window
		//Probably would have to be done in the load_settings() function
		std::cerr << "\nError loading settings from cfg\n";
	}

	//If the game is set to run fullscreen, do it.
	if(FULLSCREEN == true)
	{
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, screen_bpp, SDL_FULLSCREEN);//Set video mode as fullscreen
		std::cout << "\nRunning fullscreen\n";
	}
	else
	{
		if(true) //TODO: Change this to if(system_memory) { ... }
		{
    			screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, screen_bpp, SDL_SWSURFACE); // Set video mode... A crucial part
		}
		std::cout << "\nRunning windowed\n";
	}

	//Error checking
	if(screen == NULL)
	{
		std::cerr << "\nError setting video mode\n";
		return false;
	}

	SDL_WM_SetCaption(screen_capt.c_str(), NULL);
	std::cout << "\nSet caption to: " << screen_capt << std::endl;

	std::cout << "\nSetting varius variables.\n";

	title_screen_text1_spr = TTF_RenderText_Solid(font1, "Press enter to enter the test level", c_white); //Let the player know they have to press enter to enter the game.
	title_screen_text2_spr = TTF_RenderText_Solid(font1, "Tales of Mining and Great Riches", c_white); //Nifty little saying on the title screen.

	std::cout << "\nSucesfully Initialized\n";

	//If everything initialized fine
	return true;
}

/*bool load_settings()
{
	//A temporary veriable
	std::string temp = "";
	std::string temp3;
	//Same as above
	int temp2 = NULL;
	//Now load the configuration file
	settings.load("data/game.cfg");

	std::cout << "\nSetting screen width...";
	//Ok, fetch the screen width, and height
	temp = settings.get("SCREEN_WIDTH");
	//Convert the value to an int so that we can assign the screen width correctly
	temp2 = atoi(temp.c_str());
	//Now set it
	SCREEN_WIDTH = temp2;
	//error checking
	if(!SCREEN_WIDTH)
		return false;
	std::cout << "Screen width set succesfully!\n";
	//reset the temps as to not cuase conflicts
	temp = "";
	temp2 = NULL;
	//Repeat for screen height
	std::cout << "Setting screen height...";
	temp = settings.get("SCREEN_HEIGHT");
	temp2 = atoi(temp.c_str());
	SCREEN_HEIGHT = temp2;
	if(!SCREEN_HEIGHT)
		return false;
	std::cout << "Screen height set succesfully!\n";
	temp = "";
	temp2 = NULL;

	//Run in fullscreen?
	std::cout << "\nChecking to see if I should run fullscreen...";
	temp = settings.get("FULLSCREEN");
	if(temp == "TRUE")
	{
		FULLSCREEN = true;
		std::cout << "Running fullscreen.\n";
	}
	else
	{
		FULLSCREEN = false;
		std::cout << "Running windowed.\n";
	}
	temp = "";

	//Set the fps to cap off the game at
	std::cout << "\nSetting frame rate...";
	temp = settings.get("FPS");
	temp2 = atoi(temp.c_str());
	FPS = temp2;
	if(!FPS)
		return false;
	std::cout << "Frame rate set succesfully to " << FPS <<"!\n";
	temp = "";
	temp2 = NULL;

	temp = settings.get("CAM_MOVE_SPEED");
	temp2 = atoi(temp.c_str());
	camera_move_speed = temp2;
	if(camera_move_speed == 0)
	{
		std::cout << "Cannot find CAM_MOVE_SPEED or cannot set it to 0\n";
		return false;
	}
	std::cout << "Set camera move speed to: " << camera_move_speed << std::endl;
	temp = "";
	temp2 = NULL;

	temp = settings.get("INTERFACE_CFG");
	//Interface stuff.
	settings.load(temp);
	temp = "";

	//First we'll get the paths of the teleport button sprites.
	std::cout << "\nLoading teleport button sprite.\n";
	temp = settings.get("TELEPORT_BUTTON_PATH");
	teleport_button_path = temp;
	std::cout << temp << std::endl;
	temp = "";

	std::cout << "\nLoading disabled teleport button sprite.\n";
	temp = settings.get("DISABLED_TELEPORT_BUTTON_PATH");
	no_teleport_button_path = temp;
	std::cout << temp << std::endl;
	temp = "";

	std::cout << "\nX and Y of teleport button:";
	temp = settings.get("TELEPORT_BUTTON_X");
	g_teleport_button.x1 = atoi(temp.c_str());
	std::cout << " (" << g_teleport_button.x1 << "," << std::endl;
	temp = "";
	temp = settings.get("TELEPORT_BUTTON_Y");
	g_teleport_button.y1 = atoi(temp.c_str());
	std::cout << g_teleport_button.y1 <<  ")\n" << std::endl;
	temp = "";

	temp = settings.get("FONT_1");
	temp3 = settings.get("FONT_1_SIZE");
	font1 = TTF_OpenFont(temp.c_str(), atoi(temp3.c_str()));
	temp = "";
	temp2 = NULL;
	temp3 = "";

	return true;
}*/

bool load_settings()
{
	//This is all the junk needed by the parser
	FILE* file;
	int c = 0;
	char temp;
	bool comment = true;
	string command;
	string num_command;
	bool check_command;

	//Here lay all the variables the parser needs for setting variables and such for the game.
	const char filepath[200] = "data/game.cfg";
	const char interface_filepath[200] = "";
	const char* interface_filepath2 = "";
	std::string temp2;
	std::string f1_temp1 = ""; //This is a temp variable for font1 loading stuff
	int f1_temp2 = 0; //This is a temp variable for font1 loading stuff.
	std::string f2_temp1 = ""; //This is a temp variable for font2 loading stuff
	int f2_temp2 = 0; //This is a temp variable for font2 loading stuff.

	//Load the cfg
	file = fopen(filepath, "r");
	if(file == NULL)
	{
		cout << "The file \"" << filepath << "\" does not exist!\n";
		return false;
	}

	//The parsing loop
	while (c != EOF)
	{
		//cout << "\nTest\n";
        	c = getc(file);
		temp = (char) c;

		if(temp == ']' || temp == '\n')
		{
			comment = true;
			check_command = true;
		}

		if(!comment)
		{
			command += temp;
			//std::cout << "\nAppending to command string. Current contents:\n" << command << "\n";
			
			cout.flush();
		}

		//I do this check here so that it doesn't append the '[' to the command string.
		if(temp == '[')
		{
			comment = false;
		}

		//This is where we check the things it reads and see if it's a valid command. If so, then get the required values for that command
		if(check_command)
		{
			if(command == "SCREEN_WIDTH")
			{
				std::cout << "\nEncountered the variable that specifies the screen width.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						SCREEN_WIDTH = atoi(num_command.c_str());
						std::cout << "\nScreen width = " << SCREEN_WIDTH << "\n";
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

					cout.flush();
				}
			}

			else if(command == "SCREEN_HEIGHT")
			{
				std::cout << "\nEncountered the variable that specifies the screen height.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						SCREEN_HEIGHT = atoi(num_command.c_str());
						std::cout << "\nScreen height = " << SCREEN_HEIGHT << "\n";
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

					cout.flush();
				}
			}

			else if(command == "FULLSCREEN")
			{
				std::cout << "\nEncountered the variable that specifies whether to run fullscreen or not.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						if(num_command == "TRUE")
						{
							FULLSCREEN = true;
							//std::cout << "\nRunning fullscreen\n";
						}
						else
						{
							FULLSCREEN = false;
							//std::cout << "\nRunning windowed\n";
						}
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

					cout.flush();
				}
			}

			else if(command == "FPS")
			{
				std::cout << "\nEncountered the variable that specifies the FPS cap.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						FPS = atoi(num_command.c_str());
						std::cout << "\nFPS cap = " << FPS << "\n";
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

					cout.flush();
				}
			} //GFPS

			else if(command == "GFPS")
			{
				std::cout << "\nEncountered the variable that specifies the Graphics update stuff.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						GFPS = atoi(num_command.c_str());
						std::cout << "\nGFPS cap = " << GFPS << "\n";
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

					cout.flush();
				}
			} //GFPS

			else if(command == "HELPER_THREADS")
			{
				std::cout << "\nEncountered the variable that specifies the number of helper threads.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						num_worker_threads = atoi(num_command.c_str());
						std::cout << "\nNumber of helper threads = " << num_worker_threads << "\n";
						num_command = "";

						for(int i = 0; i < num_worker_threads; i++)
						{
							pthread_t new_thread;
							threads.push_back(new_thread); //Create our worker/helper threads.
							cout << "Created new thread!\n";
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

					cout.flush();
				}
			}

			else if(command == "CAM_MOVE_SPEED")
			{
				std::cout << "\nEncountered the variable that specifies the camera move speed.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						if(num_command != "0")
						{
							camera_move_speed = atoi(num_command.c_str());
							std::cout << "\nCamera move speed = " << camera_move_speed << "\n";
						}
						else
						{
							std::cout << "\nCannot set camera move speed to 0, fool!\n";
							return false;
						}
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

					cout.flush();
				}
			}

			else if(command == "INTERFACE_CFG")
			{
				std::cout << "\nEncountered the variable that specifies the location of the interface cfg.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						//interface_filepath = num_command.c_str();
						temp2 = num_command; //I don't assign num_Command directly to interface_filepath2 becuase if I did, when num_command was cleared or changed, interface filepath would equal the new value of num_command.
						interface_filepath2 = const_cast<char *>(temp2.c_str());
						//strncpy(num_command.c_str(), interface_filepath);
						//for(int i=0; num_command.c_str[i]; i++) interface_filepath[i] = num_command[i];		//TODO: Get it to assign interface_filepath the value of num_command
						std::cout << "\nInterface cfg filepath = " << interface_filepath2 << "\n";
						//std::cout << "\nInterface cfg filepath = " << num_command << "\n";

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

					cout.flush();
				}
			}

			check_command = false;
			command = "";
		}

		cout.flush();
	}

	fclose(file);
	c = 0;

	file = fopen(interface_filepath2, "r");
	if(file == NULL)
	{
		cout << "The file \"" << interface_filepath2 << "\" does not exist!\n";
		return false;
	}

	//The parsing loop
	while (c != EOF)
	{
		//cout << "\nTest\n";
        	c = getc(file);
		temp = (char) c;

		if(temp == ']' || temp == '\n')
		{
			comment = true;
			check_command = true;
		}

		if(!comment)
		{
			command += temp;
			//std::cout << "\nAppending to command string. Current contents:\n" << command << "\n";
			//cout <<temp;
			
			cout.flush();
		}

		//I do this check here so that it doesn't append the '[' to the command string.
		if(temp == '[')
		{
			comment = false;
		}

		//This is where we check the things it reads and see if it's a valid command. If so, then get the required values for that command
		if(check_command)
		{
			if(command == "TELEPORT_BUTTON_PATH")
			{
				std::cout << "\nEncountered the variable that specifies the teleport button path.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						teleport_button_path = num_command;
						std::cout << "\nTeleport button path = " << teleport_button_path << "\n";
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

					cout.flush();
				}
			}

			else if(command == "TELEPORT_BUTTON_X")
			{
				std::cout << "\nEncountered the variable that specifies the teleport button x.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						Interface.g_teleport_button.x1 = atoi(num_command.c_str());
						std::cout << "\nTeleport button x = " << Interface.g_teleport_button.x1 << "\n";
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

					cout.flush();
				}
			}

			else if(command == "TELEPORT_BUTTON_Y")
			{
				std::cout << "\nEncountered the variable that specifies the teleport button y.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						Interface.g_teleport_button.y1 = atoi(num_command.c_str());
						std::cout << "\nTeleport button y = " << Interface.g_teleport_button.y1 << "\n";
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

					cout.flush();
				}
			}

			else if(command == "DISABLED_TELEPORT_BUTTON_PATH")
			{
				std::cout << "\nEncountered the variable that specifies the disabled teleport button path.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						no_teleport_button_path = num_command;
						std::cout << "\nTeleport button path = " << no_teleport_button_path << "\n";
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

					cout.flush();
				}
			}

			else if(command == "FONT_1")
			{
				std::cout << "\nEncountered the variable that specifies font 1's path.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						f1_temp1 = num_command;
						std::cout << "\nFont 1's path = " << f1_temp1 << "\n";
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

					cout.flush();
				}
			}

			else if(command == "FONT_1_SIZE")
			{
				std::cout << "\nEncountered the variable that specifies font 1's size.\n";

				bool quit = false;

				//Now we read its values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						f1_temp2 = atoi(num_command.c_str());
						std::cout << "\nFont 1's size = " << f1_temp2 << "\n";
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

					cout.flush();
				}
			}

			else if(command == "FONT_2")
			{
				std::cout << "\nEncountered the variable that specifies font 2's path.\n";

				bool quit = false;

				//Now we read it's values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						f2_temp1 = num_command;
						std::cout << "\nFont 1's path = " << f2_temp1 << "\n";
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

					cout.flush();
				}
			}

			else if(command == "FONT_2_SIZE")
			{
				std::cout << "\nEncountered the variable that specifies font 2's size.\n";

				bool quit = false;

				//Now we read its values
				while(c != EOF && quit == false)
				{
					bool start;
					c = getc(file);
					temp = (char) c;

					if(temp == '\n' || temp == ')')
					{
						start = false;
						quit = true;
						f2_temp2 = atoi(num_command.c_str());
						std::cout << "\nFont 2's size = " << f2_temp2 << "\n";
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

					cout.flush();
				}
			}

			//Found the variable that specifies the path to the title screen's image.
			else if(command == "TITLE")
			{
				std::cout << "\nEncountered the variable that specifies the location of the title screen's image.\n"; //Debugging output.

				bool quit = false; //Controls the loop below.

				//Now we its values
				while(c != EOF && quit == false)
				{
					bool start; //The parser can begin to record the values in the parantheses.
					c = getc(file); //Read the character.
					temp = (char) c; //Convert c into a char.

					//If it found the end of the line or the closing parantheses...
					if(temp == '\n' || temp == ')')
					{
						start = false; //Stop reading from file.
						quit = true; //Exit this loop.
						std::cout << "\nLocation of the title screen's image = " << num_command << "\n"; //Debugging output
						//title_screen = img_load(num_command); //Load the title screen image.
						title_screen_path = num_command; //Let the game know where the title screen's image is located.
						num_command = ""; //Reset num_command
					}
					//If it found the opening paranthesis...
					else if (temp == '(')
					{
						start = true; //Start reading from file.
					}

					else if(start)	
					{
						num_command += temp; //Read from file.
					}

					cout.flush(); //Fource the console to update.
				}
			}

			check_command = false;
			command = "";
		}

		cout.flush();
	}

	font1 = TTF_OpenFont(f1_temp1.c_str(), f1_temp2);
	font2 = TTF_OpenFont(f2_temp1.c_str(), f2_temp2);

	fclose(file);

	c = 0;

	std::string temp3 = "/data/units.cfg";
	char* filepath2 = const_cast<char *>(temp3.c_str());

	file = fopen(filepath2, "r");
	if(file == NULL)
	{
		cout << "The file \"" << filepath2 << "\" does not exist!\n";
		return false;
	}

	return true;
}
