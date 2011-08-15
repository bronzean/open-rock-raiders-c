/* Copyright Ciprian Ilies */
#pragma once
#include "../../Engine.hpp"
#include "variable.hpp"

namespace cfg
{
	bool parse_config_file(std::string filepath, std::vector<variable> *variables); //Parse a config file. The first paramater asks for the filepath, and the second paramater asks for a pointer to a vector of variables.
}
