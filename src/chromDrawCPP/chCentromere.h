/*
* Name: chCentromere.h
* Description: Declaration methodes for chromosome centromere.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef CHCENTROMERE_H_
#define CHCENTROMERE_H_
//#pragma once

#include "chromosomeElement.h"

using namespace std;

class chCentromere :
	public chromosomeElement
{
	public:
		chCentromere(void);
		chCentromere(EChromosomeElementType t);
		~chCentromere(void);

		virtual void drawLinear(canvas *sheet, colorPalette palette);
		virtual void drawLinear(canvas *sheet, colorPalette palette, string name);
		virtual void drawCircular(canvas *sheet, colorPalette palette);
		virtual void drawCircular(canvas *sheet, colorPalette palette, string name);
};

#endif // CHCENTROMERE_H_
