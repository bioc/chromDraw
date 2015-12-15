/*
* Name: karyotype.h
* Description: Declaration methods and definition constants for work with karyotype.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef KARYOTYPE_H_
#define KARYOTYPE_H_
//#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <cstring>
#include <locale>
#include <sstream>
#include "chromosome.h"
#include "colorPalette.h"
#include "parsing.h"
#include "charsLenghts.h"


//definition key words for load imput matrix.
#define CHR "CHR"	// chromosome
#define BLOCK "BLOCK"	// block
#define MAP "MAP"	// mapping
#define TO "TO"		// mapping to chromosome
#define CENTROMERE "CENTROMERE"	// centromere
#define COMMENT '#'	// comment
#define MARK "MARK" // sign - mark
#define RECTANGLE "RECTANGLE"	// rectangle shape of mark
#define ELLIPSE "ELLIPSE"		//elipse shape of mark

// definition columns for load each imput items.
#define CHRITEMSCOUNT 5	
#define BLOCKITEMSCOUNT 6
#define MAPITEMSCOUNT 8
#define CENTROMEREITEMSCOUNT 2
#define FISHITEMSCOUNT 6

using namespace std;

#define MAXLINELEN 256

class karyotype
{
	public:
		karyotype(void);
		~karyotype(void);
	
	private:
		string name;	// name of karyotype
		string alias; // alias of karyotype
		list<chromosome*> katype; // karyotype contain chromosomes	
		int internalAliasMark;	// For generateing distinguish internal alias for marks. 

	public:
		void setName(string name);
		string getName();
		void setAlias(string sAlias);
		string getAlias();
		void pushChromosome(chromosome *c);
		void popChromosome(string sAlias);
		chromosome* getChromosome(string sAlias);
		int getChromosomeRank(string sAlias);
		bool isChromosomeExist(string sAlias);
		int loadMatrix(ifstream *inputFile);
		void draw(canvas *sheet, colorPalette palette, bool linear);
		int getMaxStringLenghtBlock();
		float getMaxStringLenghtChrName();
		int getMaxChromosomeLenght();
		int getChromosomeCount();
		void addMissingBlocks();
	
	private:
		void sortBlocks();
		void incrementInternalMarkAlias();
		string getInternalMarkAlias();
		void calculateNewData();
		
};

#endif // KARYOTYPE_H_

