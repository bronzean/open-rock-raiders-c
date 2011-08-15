/* Copyright Ciprian Ilies */
#pragma once
#include "../../Engine.hpp"

namespace cfg
{
	class variable //A variable. What exactly is it? It's a variable read in from a config file.
	{
	public:
		std::vector<std::string> values; //What values does it have? (The data inside the parantheses.
		std::string name; //The actual data of the variable. (The stuff inside the brackets).

		variable(); //Constructor.
		~variable(); //Deconstructor.
	};
}
