/*
* Name: colorPalette.cpp
* Description: Definition of methods for useing color palette.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#include "colorPalette.h"

/**
* Constructor of color palette.
*/
colorPalette::colorPalette(void)
{
}

/**
* Destructor of color palette.
*/
colorPalette::~colorPalette(void)
{
}

/**
* Function for load input file with colors.
* @param path Input file with path.
* @return State of loading colors.
*/
int colorPalette::loadMatrix(string path)
{
	ifstream inputFile;

	inputFile.open(path.c_str());
	if(! inputFile.good())
	{
		throw(200);
		//return -1;
	}

	while(! inputFile.eof())
	{
		list<string> lineLexemes;


		int state = parsing::getLineLexemes(&lineLexemes, &inputFile);
		if(state == 1)
		{
			break;
		}
		else if( 0 != state)
		{
			inputFile.close();
			return -1;
		}
		
		
		// color information
		if(parsing::stringToUpper(lineLexemes.front()).compare(COLOR) == 0)
		{
			
			if(lineLexemes.size() == COLORITEMSCOUNT)
			{
				list<string>::iterator it = lineLexemes.begin();
				it++;
				color *tmpColor = new color();

				tmpColor->setName(*it++);
				
				istringstream r(*it++);
				int value;
				r >> value;
				tmpColor->setRed(value);

				istringstream g(*it++);
				g >> value;
				tmpColor->setGreen(value);

				istringstream b(*it++);
				b >> value;
				tmpColor->setBlue(value);
				
				if(getColor(tmpColor->getName()) == NULL)
				{
					palette.push_back(tmpColor);
				}
				else
				{
					cout << "Color with name: "  << tmpColor->getName() << " is already exists." << endl;
					throw(202);
					return -1;
				}
			}
			else
			{
				throw(201);
			}
		}
		// comments
		else if(parsing::stringToUpper(lineLexemes.front())[0] == COMMENT)
		{
		}

	}

	return 0;
}

/**
* Function for get color by name.
* @param name Name of color.
* @return Pointer to the color if color does not exist return NULL.
*/
color* colorPalette::getColor(string name)
{
	for(list<color*>::iterator it=palette.begin(); it != palette.end(); it++)
	{
		color *c = *it;
		if(c->getName().compare(name) == 0)
		{
			return *it;
		}
	}
	return NULL;
}

/**
* Put color to the color list.
* @param r Red value of color.
* @param g Green value of color.
* @param b Blue value of color.
* @param name Name of color.
*/
void colorPalette::pusColor(int r, int g, int b, string name)
{
	color *c = new color();
	
	c->setRed(r);
	c->setGreen(g);
	c->setBlue(b);
	c->setName(name);

	palette.push_back(c);
}

/**
* Delete color from list with colors by name.
* @param name Name of deleting color.
*/
void colorPalette::popColor(string name)
{
	for(list<color*>::iterator it=palette.begin(); it != palette.end(); it++)
	{
		color *c = *it;
		if(c->getName().compare(name) == 0)
		{
			palette.remove(*it);
		}
	}
}

