/*
* Name: markSign.h
* Description: Declaration arguments and methods for one sign of mark on the chromosome.
* Author: Jan Janecka, ing  c 2015
* Contact: jan.janecka@ceitec.muni.cz
*/


#ifndef MARKSIGN_H_
#define MARKSIGN_H_
//#pragma once

#include "chromosomeSign.h"


class markSign :
	public chromosomeSign
{
	public:
		enum EMarkShape {SNillItem, SRectangle, SEllipse}; // enum of shapes of marks
		                                                            
	public:
		markSign(void);
		markSign(EChromosomeSignType mt);
		~markSign(void);
	
	private:
		EMarkShape shape;	// shape of mark

	public:
		void setShape(EMarkShape sh);
		EMarkShape getShape();


		virtual void drawLinear(canvas *sheet, colorPalette palette);
		virtual void drawLinear(canvas *sheet, colorPalette palette, string name);
		virtual void drawCircular(canvas *sheet, colorPalette palette);
		virtual void drawCircular(canvas *sheet, colorPalette palette, string name);
};

#endif // MARKSIGN_H_
