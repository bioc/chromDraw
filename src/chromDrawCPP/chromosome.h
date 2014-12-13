/*
* Name: chromosome.h
* Description: Declaration methods for chromosome.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_
//#pragma once

#include <cstdio>
#include <iostream>
#include <list>
#include "chCentromere.h"
#include "chBlock.h"
#include "canvas.h"
#include "colorPalette.h"

using namespace std;

class chromosome
{
	public:
		chromosome(void);
		~chromosome(void);

	private:
		string name;	// name of chromosome
		string alias;	// unic alias of chromosome
		int start;		// start position of chromosome
		int stop;		// stop position of chromosome
		list<chromosomeElement*> chr;	// chromosome elements

	public:
		void draw(canvas *sheet, colorPalette palette, bool linear);
		void setName(string s);
		string getName();
		void setAlias(string s);
		string getAlias();
		void setBegin(int i);
		int getBegin();
		void setEnd(int i);
		int getEnd();
		void pushElement(chromosomeElement *element);
		chromosomeElement* getElement(string sAlias);
		void popElement(string sAlias);
		bool isElementexist(string sAlias);
		int getChromosomLenght();
		int getCentromereCount();
		int checkChromosomeData();
		int getMaxStringLenghtBlock();
		void sortElements();

};


#endif // CHROMOSOME_H_
