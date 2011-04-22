/* Copyright the ORR-C Dev Team */
#pragma once
#include "../Engine.hpp"
using namespace std;

class parser
{
public:
	//char filepath[200];
	FILE* file;
	int c;
	ofstream myfile;
	char temp;
	char temp2;
	bool comment;

	bool parse_map_cfg2(const char filepath[200]); //Testing another method of doing it
	bool parse_map_layer(const char folderpath[200]);
};

extern parser Parser;
