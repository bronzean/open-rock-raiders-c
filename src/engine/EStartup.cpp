/* Copyright the ORR-C Dev Team */
//Contains all of the startup code
#include "../Engine.hpp"
#include "Interface.hpp"
#include "EPrototypes.hpp"

using namespace std;

bool startup(bool fullscreen, int screen_w, int screen_h, int screen_bpp, std::string screen_capt, bool load_from_cfg)
{
	std::cout << "\nInitializing\n";

	if(SDL_Init( SDL_INIT_EVERYTHING ) == -1) //Initialize everything
	{
		std::cerr << "\nError initializing SDL\n";
		return false;
	}

	if(TTF_Init() == -1) //Initialize SDL_ttf
	{
		std::cerr << "\nError initializing SDL_ttf\n";
		return false;    
	}

	if (SDLNet_Init() == -1) //Initialise SDL_net
	{
		std::cerr << "Failed to intialise SDL_net: " << SDLNet_GetError() << "\n";
		return false;
	}

	if(load_settings() == false)
	{
		//TODO: Make the error loading more specific and print out the problems to the console window
		//Probably would have to be done in the load_settings() function
		std::cerr << "\nError loading settings from cfg\n";
	}

	if(!threed_gfx) //Checks whether or not 3D graphics are being used.
	{
		//Ok, not using 3D graphics...

		//If the game is set to run fullscreen, do it.
		if(FULLSCREEN == true)
		{
			screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, screen_bpp, SDL_FULLSCREEN);//Set video mode as fullscreen
			std::cout << "\nRunning fullscreen\n";
			//SDL_SWSURFACE|SDL_ANYFORMAT
		}
		else
		{
			if(true) //TODO: Change this to if(system_memory) { ... }
			{
    				screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, screen_bpp, SDL_HWSURFACE|SDL_ANYFORMAT|SDL_DOUBLEBUF); // Set video mode... A crucial part
			}
			std::cout << "\nRunning windowed\n";
		}
	}
	else
	{
		//Oh look, using 3D graphics.

		if(FULLSCREEN == true)
		{
			screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, screen_bpp, SDL_FULLSCREEN|SDL_OPENGL|SDL_GL_DOUBLEBUFFER|SDL_HWPALETTE);
			std::cout << "\nRunning 3D fullscreen\n";
		}
		else
		{
			screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, screen_bpp, SDL_OPENGL|SDL_GL_DOUBLEBUFFER|SDL_HWPALETTE);
			std::cout << "\nRunning 3D windowed\n";
		}

		glShadeModel(GL_SMOOTH); // Enable smooth shading

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Set the background black

		glClearDepth(1.0f); //Depth buffer setup

		glEnable(GL_DEPTH_TEST); //Enables Depth Testing

		glDepthFunc(GL_LEQUAL); //The Type Of Depth Test To Do

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Sets the perspective calculations.

		resizeGlWindow(SCREEN_WIDTH, SCREEN_HEIGHT); //Sets up the window for 3D mode.
	}

	if(screen == NULL) //Error checking
	{
		std::cerr << "\nError setting video mode\n";
		return false;
	}

	SDL_WM_SetCaption(screen_capt.c_str(), NULL);
	std::cout << "\nSet caption to: " << screen_capt << std::endl;

	std::cout << "\nSetting varius variables.\n";

	title_screen_text1_spr = TTF_RenderText_Solid(font1, "Press enter to enter the test level", c_white); //Let the player know they have to press enter to enter the game.
	title_screen_text2_spr = TTF_RenderText_Solid(font1, "Tales of Mining and Great Riches", c_white); //Nifty little saying on the title screen.

	cout << "Setting global teleport button's variables.\n";
	//Interface.g_teleport_button.sprite = img_load3(teleport_button_path); //Load the sprite.
	//img_load_safe(teleport_button_path, *Interface.g_teleport_button.sprite); //Load the sprite.
	if(!img_load_safe(teleport_button_path, &Interface.g_teleport_button.sprite)) //Load the sprite.
	{
		cout << "Failed loading teleport button sprite.\n";
		return false;
	}
	//Interface.g_teleport_button.d_sprite = img_load3(no_teleport_button_path); //Load the disabled button's sprites.
	//img_load_safe(no_teleport_button_path, *Interface.g_teleport_button.d_sprite); //Load the disabled button's sprites.
	if(!img_load_safe(no_teleport_button_path, &Interface.g_teleport_button.d_sprite)) //Load the disabled button's sprites.
	{
		cout << "Failed loading teleport button disabled sprite.\n";
		return false;
	}
	Interface.g_teleport_button.x2 = Interface.g_teleport_button.x1 + Interface.g_teleport_button.sprite->w; //Set the x of the botomn right corner of the teleport button.
	cout << "2\n";
	Interface.g_teleport_button.y2 = Interface.g_teleport_button.y1 + Interface.g_teleport_button.sprite->h; //Set the y of the botomn right corner of the teleport button.
	cout << "3\n";

	cout << "Loading title screen's sprite.\n";
	//title_screen = img_load3(title_screen_path); //Load the title screen.
	//img_load_safe(title_screen_path, *title_screen);
	if(!img_load_safe(title_screen_path, &title_screen))
	{
		cout << "Failed loading title screen sprite.\n";
		return false;
	}

	std::cout << "\nSucesfully Initialized\n";

	cout << "Setting the \"Construct Wall\" button's variables.\n";
	SDL_Surface* temp_spr = NULL; //Temporary sprite holding the construct wall button's sprite.
	//temp_spr = img_load3("data/resource/interface/button/construction/build_wall.png");
	if(!img_load_safe("data/resource/interface/button/construction/build_wall.png", &temp_spr))
	{
		cout << "Failed loading wall construction sprite.\n";
		return false;
	}
	Interface.construct_wall_button.init(temp_spr->w, temp_spr->h, 0, 0, temp_spr, NULL); //Initialize the construct wall button.
	Interface.construct_wall_button.state = 1; //Make it start out enabled!
	Interface.construct_wall_button.x1 = 550; //TODO: Make this be loaded from the interface cfg.
	Interface.construct_wall_button.y1 = 100; //TODO: Make this be loaded from the interface cfg.
	Interface.construct_wall_button.x2 = Interface.construct_wall_button.x1 + Interface.construct_wall_button.sprite->w; //Set the construct wall button's bottom right corner's x.
	Interface.construct_wall_button.y2 = Interface.construct_wall_button.y1 + Interface.construct_wall_button.sprite->h; //Set the construct wall button's bottom right corner's y.

	choose_wall_location_spr = TTF_RenderText_Solid(font1, choose_wall_location_str.c_str(), c_white);

	//Everything initialized fine.
	return true;
}

bool load_settings()
{
	//This is all the junk needed by the parser
	FILE* file = NULL;
	int c = 0;
	char temp = ' ';
	bool comment = true;
	string command = "";
	string num_command = "";
	bool check_command = false;

	//Here lay all the variables the parser needs for setting variables and such for the game.
	const char filepath[200] = "data/game.cfg";
	const char interface_filepath[200] = "";
	const char* interface_filepath2 = "";
	std::string temp2 = "";
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

			else if(command == "3D")
			{
				std::cout << "\nRunning 3D\n";

				threed_gfx = true; //Let the game know it will be running in 3D.
			}

			else if(command == "PORT")
			{
				std::cout << "\nEncountered the variable that specifies the port the server will be running on.\n";

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
						port_number = atoi(num_command.c_str());
						cout << "\nPort number = " << port_number << "\n";
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

			else if(command == "CLIENT_UPDATE_INTERVAL")
			{
				std::cout << "\nEncountered the variable that specifies the rate at which the client will be asking the server for updates.\n";

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
						client_update_interval = atoi(num_command.c_str());
						cout << "\nClient update interval (in MS) = " << client_update_interval << "\n";
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

			else if(command == "MAP")
			{
				std::cout << "\nEncountered the variable that specifies the map filepath.\n";

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
						temp2 = num_command;
						map_folder_path = const_cast<char *>(temp2.c_str());
						cout << "Map path is: " << map_folder_path << "\n";

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

			else if(command == "SERVER")
			{
				std::cout << "\nRunning in server mode.\n";

				server = true; //Let the game know it will be running in 3D.
			}

			else if(command == "MAX_CLIENTS")
			{
				std::cout << "\nEncountered the variable that specifies the maximum amount of clients that can connect to the server.\n";

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
						max_clients = atoi(num_command.c_str());
						cout << "\nPort number = " << port_number << "\n";
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
						//Interface.g_teleport_button.sprite = img_load2(num_command.c_str()); //Load the teleport button's sprite and assign it.
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
						std::cout << "\nTeleport button path = " << num_command << "\n";
						//Interface.g_teleport_button.d_sprite = img_load2(num_command); //Load the teleport button's disabled sprite.
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

	//std::string temp3 = "/data/units.cfg";
	//char* filepath2 = const_cast<char *>(temp3.c_str());

	//file = fopen(filepath2, "r");
	//if(file == NULL)
	//{
	//	cout << "The file \"" << filepath2 << "\" does not exist!\n";
	//	return false;
	//}

	return true;
}
