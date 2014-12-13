/*
* Name: chBlock.h
* Description: Declaration arguments and methods for one block of chromosome.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef CHBLOCK_H_
#define CHBLOCK_H_
//#pragma once

#include "chromosomeElement.h"


using namespace std;

class chBlock :
	public chromosomeElement
{
	public:
		chBlock(void);
		chBlock(EChromosomeElementType t);
		~chBlock(void);

	virtual void drawLinear(canvas *sheet, colorPalette palette);
	virtual void drawLinear(canvas *sheet, colorPalette palette, string name);
	virtual void drawCircular(canvas *sheet, colorPalette palette);
	virtual void drawCircular(canvas *sheet, colorPalette palette, string name);
};

#endif // CHBLOCK_H_
