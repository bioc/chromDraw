/*
* Name: chromosomeMark.h
* Description: Declaration methods and arguments for basic class type of chromosom mark.
* Author: Jan Janecka, ing  c 2015
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef CHROMOSOMEMARK_H_
#define CHROMOSOMEMARK_H_
//#pragma once

#include <cstdio>
#include <iostream>
#include "canvas.h"
#include "colorPalette.h"

using namespace std;

#define EMPTYSTRING "\"\""

class chromosomeMark
{
	public:
		enum EChromosomeMarkType {TNillItem, TFish}; // enum of chromosome marks
		enum EChromosomeMarkLocation {LNillItem, LBlock, LCentromere, LTelomere};	// enum of marks location

	public:
		chromosomeMark(void);
		~chromosomeMark(void);
	private:
		EChromosomeMarkType type; // type of mark
		EChromosomeMarkLocation location; // location fo mark
		string name;	// name of mark for showing
		//string alias;	// alias for internal using and finding
		int start;		// begin of element
		int stop;		// end of element
		string colorName;	// alias of color for curent element
		int size;		// size of mark

	public:
		void setMarkType(EChromosomeMarkType t);
		EChromosomeMarkType getMarkType();
		void setMarkLocation(EChromosomeMarkLocation l);
		EChromosomeMarkLocation getMarkLocation();
		void setName(string s);
		string getName();
		//void setAlias(string s);
		//string getAlias();
		void setBegin(int i);
		int getBegin();
		void setEnd(int i);
		int getEnd();
		void setColorName(string s);
		string getColorName();
		void setSize(int si);
		int getSize();



		virtual void drawLinear(canvas *sheet, colorPalette palette);
		virtual void drawLinear(canvas *sheet, colorPalette palette, string name);
		virtual void drawCircular(canvas *sheet, colorPalette palette);
		virtual void drawCircular(canvas *sheet, colorPalette palette, string name);
};

#endif // CHROMOSOMEMARK_H_