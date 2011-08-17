/* Copyright Ciprian Ilies */
#include "parser.hpp"
using namespace std;

namespace cfg
{
	bool parse_config_file(string filepath, vector<variable> *variables)
	{
		variable new_variable; //The variable that was just read in.
		string variable_name = ""; //The data inside the brackets.
		string paramater = ""; //The paramater, that was just read in, to the variable, that was just read in.

		char current_char = ' '; //The last char read in from the file.

		int c = 0; //Used when reading in the file.

		bool comment = true; //Did a comment start?

		bool done_reading_variable = false; //Did it finish reading in the variable?

		FILE *file = NULL; //The file.

		file = fopen(filepath.c_str(), "r"); //Open the file for reading.
		if(!file) //Error checking.
		{
			cout << "Failed to open file: \"" << filepath << "\".\n"; //Let the user know there was an error.

			return false; //Let the caller know this failed.
		}

		while(c != EOF) //Loop through the file.
		{
			c = getc(file); //Grab the next character.
			current_char = (char)c; //Cast to char.

			if(current_char == ']' || current_char == '\n') //If the end of the line hath been read in or the closing bracket hath been found...
			{
				comment = true; //Comment started! That means we do NOT save what we read just read in.
				done_reading_variable = true; //Yay, we read in the variable. Now it's time to grab its paramaters and then add all this to the vector of variables we are given in the function paramaters.
			}

			if(!comment) //Checks if we're currently NOT in a comment.
			{
				variable_name += current_char; //Save the current character.
			}

			if(current_char == '[') //Has the opening bracket been found?
			{
				comment = false; //Yay, time to start saving all the chars being read in.
			}

			if(done_reading_variable) //Check if it's time to check the variable's paramaters.
			{
				new_variable.name = variable_name; //Save the variable's name.

				bool quit = false; //Controls the loop below.
				bool start = false; //Pretty much like bool comment, except it looks for the parantheses.

				while(c  != EOF && !quit) //While not end of file and quit = false.
				{
					c = getc(file); //Grab the next char.
					current_char = (char)c; //Cast to char.

					if(current_char == '\n') //End of line?
					{
						start = false; //Set this to false.
						quit = true; //And tell it to stop looping.
					}

					if(current_char == ')') //Check if it's the closing paranthes.
					{
						start = false; //Stop saving.
						new_variable.values.push_back(paramater); //Add this to the variable's value list.
						paramater = ""; //Reset this.
					}
					else if(current_char == '(') //Found the opening paranthesis?
					{
						start = true; //Start recording.
					}
					else if(start) //Recording time?
					{
						paramater += current_char; //Save the current char.
					}
				}

				out_string << "Variable name: " << variable_name << "\n";

				variable_name = ""; //Reset this.

				variables->push_back(new_variable); //Save this new variable.

				new_variable.name = ""; //Reset this.
				new_variable.values.clear(); //Empty this.

				done_reading_variable = false;
			}
		}

		fclose(file); //Close the file.

		return true; //Success!
	}
}
