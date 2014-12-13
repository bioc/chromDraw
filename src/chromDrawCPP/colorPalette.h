/*
* Name: colorPalette.h
* Description: Declaration methods and arguments for colors settings.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef COLORPALETE_H_
#define COLORPALETE_H_
//#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include "color.h"
#include "parsing.h"

#define COMMENT '#'
#define COLOR "COLOR"

#define COLORITEMSCOUNT 5 // number of items at one line of color definition

#define NUMOFDEFAULTCOLORS 8	// number of default colors

using namespace std;

// name of default colors for brasicae
const string DEFAULTCOLORS[NUMOFDEFAULTCOLORS] = {"yellow", "red", "blue", "violet", "orange", "green", "light_blue", "pink"};


class colorPalette
{
	public:
		colorPalette(void);
		~colorPalette(void);

	private:
		list<color*> palette;	// list of colors with name and RGB values

	public:
		int loadMatrix(string path);
		color* getColor(string name);
		void pusColor(int r, int g, int b, string name);
		void popColor(string name);


};


#endif // COLORPALETE_H_
