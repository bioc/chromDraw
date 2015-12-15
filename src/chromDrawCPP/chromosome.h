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
#include "markSign.h"

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
		list<chromosomeSign*> signs;	// chromosome signs

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
		// elements
		void pushElement(chromosomeElement *element);
		chromosomeElement* getElement(string sAlias);
		void popElement(string sAlias);
		bool isElementexist(string sAlias);
		int getChromosomLenght();
		int getCentromereCount();
		int checkChromosomeData();
		void addMissingBlocks();
		int getMaxStringLenghtBlock();
		void sortElements();
		int getNorthArmLenght();
		int getSouthArmLenght();
		// marks
		void addMarksInformation();
		void pushSign(chromosomeSign *mark);
		chromosomeSign* getSign(string sAlias);
		void popSign(string sAlias);
		bool isSignExist(string sAlias);

};


#endif // CHROMOSOME_H_
