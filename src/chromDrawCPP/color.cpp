/*
* Name: color.cpp
* Description: Definition methods for class color.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#include "color.h"

/**
* Constructor for class color.
*/
color::color(void)
{
	red = 0;
	green = 0;
	blue = 0;
	name = "";
}

/**
* Destructor for class color.
*/
color::~color(void)
{
}

/**
* Methode to set red color value.
* @param value Red color value.
*/
void color::setRed(int value)
{
	if(value > 255)
	{
		red = 255;
	}
	else if(value < 0)
	{
		red = 0;
	}
	else
	{
		red = value;
	}
}

/**
* Methode to get red color value.
* @return Red color value.
*/
int color::getRed()
{
	return red;
}

/**
* Methode to set green color value.
* @param value Green color value.
*/ 
void color::setGreen(int value)
{
	if(value > 255)
	{
		green = 255;
	}
	else if(value < 0)
	{
		green = 0;
	}
	else
	{
		green = value;
	}
}

/**
* Methode to get green color value.
* @return Green color value. 
*/
int color::getGreen()
{
	return green;
}

/**
* Methode to set blue color value.
* @param value Blue color value.
*/
void color::setBlue(int value)
{
	if(value > 255)
	{
		blue = 255;
	}
	else if(value < 0)
	{
		blue = 0;
	}
	else
	{
		blue = value;
	}
}

/**
* Methode to get blue color value.
* @return Blue color value.
*/
int color::getBlue()
{
	return blue;
}

/**
* Methode to set color name.
* @param s Name of color.
*/
void color::setName(string s)
{
	name = s;
}

/**
* Methode to get color name.
* @return Color name.
*/
string color::getName()
{
	return name;
}
