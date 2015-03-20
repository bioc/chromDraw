/*
* Name: chromosomeElement.h
* Description: Declaration methods and arguments for basic class type of chromosom element.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef CHROMOSOMEELEMENT_H_
#define CHROMOSOMEELEMENT_H_
//#pragma once

#include <cstdio>
#include <iostream>
#include "canvas.h"
#include "colorPalette.h"

using namespace std;

#define EMPTYSTRING "\"\""


class chromosomeElement
{
	public:
		enum EChromosomeElementType {NillItem, Block, Centromere}; // enum of elements type

	public:
		chromosomeElement(void);
		~chromosomeElement(void);
	
	private:
		EChromosomeElementType type; // type of element
		string name;	// name of elemenet for showing
		string alias;	// alias for internal using and finding
		int start;		// begin of element
		int stop;		// end of element
		string colorName;	// alias of color for curent element

	public:
		void setElementType(EChromosomeElementType t);
		EChromosomeElementType getElementType();
		void setName(string s);
		string getName();
		void setAlias(string s);
		string getAlias();
		void setBegin(int i);
		int getBegin();
		void setEnd(int i);
		int getEnd();
		void setColorName(string s);
		string getColorName();

		void drawLinearName(canvas *sheet);
		void drawCircularName(canvas *sheet);

		virtual void drawLinear(canvas *sheet, colorPalette palette);
		virtual void drawLinear(canvas *sheet, colorPalette palette, string name);
		virtual void drawCircular(canvas *sheet, colorPalette palette);
		virtual void drawCircular(canvas *sheet, colorPalette palette, string name);

};

#endif // CHROMOSOMEELEMENT_H_
