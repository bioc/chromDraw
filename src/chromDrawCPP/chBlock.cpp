/*
* Name: chBlock.cpp
* Description: Definition methodes for collect information and manipulate with block of chromosome.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#include "chBlock.h"

/**
* Constructor for class chBlock.
*/
chBlock::chBlock(void)
{
	this->setElementType(Block);
}

/**
* Constructor for class chBlock.
* @param t Type of chromosome element.
*/
chBlock::chBlock(EChromosomeElementType t)
{
	this->setElementType(t);
}

/**
* Destructor for class chBlock.
*/
chBlock::~chBlock(void)
{
}

/**
* Methode for draw linear segment of chromosome.
* @param sheet Sheet for painting elements.
* @param palette Palete of color.
* @param name Name of block.
*/
void chBlock::drawLinear(canvas *sheet, colorPalette palette, string name)
{
	int lenght;
	lenght = getEnd() - getBegin();
	if(lenght < 0 )
		lenght = 0;

	sheet->setSegmentColor(palette.getColor(getColorName()));
	sheet->lin_drawSegment(lenght);
	// set text color dependent of block color
	if(THRESHOLDGREY <= sheet->rgbToGray(palette.getColor(getColorName())))
	{
		sheet->lin_drawBlockName(lenght, name, Color::Black);
	}
	else
	{
		sheet->lin_drawBlockName(lenght, name, Color(200,200,200));
	}
}

/**
* Methode for draw linear segment of chromosome.
* @param sheet Sheet for painting elements.
* @param palette Palete of color.
*/
void chBlock::drawLinear(canvas *sheet, colorPalette palette)
{
	
	int lenght;
	lenght = getEnd() - getBegin();
	if(lenght < 0 )
		lenght = 0;

	sheet->setSegmentColor(palette.getColor(getColorName()));
	sheet->lin_drawSegment(lenght);
}

/**
* Methode for draw circular segment of chromosome.
* @param sheet Sheet for painting elements.
* @param palette Palete of color.
*/
void chBlock::drawCircular(canvas *sheet, colorPalette palette)
{
	int lenght;
	lenght = getEnd() - getBegin();
	if(lenght < 0 )
		lenght = 0;

	sheet->setSegmentColor(palette.getColor(getColorName()));
	sheet->cir_drawSegment(lenght);
}

/**
* Methode for draw circular segment of chromosome.
* @param sheet Sheet for painting elements.
* @param palette Palete of color.
* @param name Name of segment.
*/
void chBlock::drawCircular(canvas *sheet, colorPalette palette, string name)
{
	int lenght;
	lenght = getEnd() - getBegin();
	if(lenght < 0 )
		lenght = 0;

	sheet->setSegmentColor(palette.getColor(getColorName()));
	sheet->cir_drawSegment(lenght);
	if(THRESHOLDGREY <= sheet->rgbToGray(palette.getColor(getColorName())))
	{
		sheet->cir_drawBlockName(lenght, name, Color::Black);
	}
	else
	{
		sheet->cir_drawBlockName(lenght, name, Color(200,200,200));
	}
}
