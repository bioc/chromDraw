/*
* Name: color.h
* Description: Declaration methods class color.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef COLOR_H_
#define COLOR_H_
//#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

class color
{
	public:
		color(void);
		~color(void);
	private:
		int red;	// value of red color
		int green;	// value of green color
		int blue;	// value of blue color
		string name;// color name


	public:
		void setRed(int value);
		int getRed();
		void setGreen(int value);
		int getGreen();
		void setBlue(int value);
		int getBlue();
		void setName(string s);
		string getName();
};


#endif // COLOR_H_
