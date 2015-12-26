/*
* Name: markSign.cpp
* Description: Definition methodes for collect information and manipulate with sign of mark.
* Author: Jan Janecka, ing  c 2015
* Contact: jan.janecka@ceitec.muni.cz
*/


#include "markSign.h"

/**
* Constructor for class signMark.
*/
markSign::markSign(void)
{
	this->setSignType(TMark);
	this->setSignLocation(canvas::LNillItem);
	this->setShape(SNillItem);
	this->setBegin(0);
	this->setEnd(0);
	this->setColorName("black");
}

/**
* Constructor for class signMark.
* @param mt Sign type.
*/
markSign::markSign(EChromosomeSignType mt)
{
	this->setSignType(mt);
}

/**
* Destructor for class signMark.
*/
markSign::~markSign(void)
{
}

/** Functionf for set shape of sign mark.
* @param sh Shape of mark.
*/
void markSign::setShape(markSign::EMarkShape sh)
{
	shape = sh;
}

/** Get shape of mark.
* @return Shape of mark.
*/
markSign::EMarkShape markSign::getShape()
{
	return shape;
}

/**
* Method for linear draw of mark.
* @param sheet Actual sheet for drawing sign.
* @param palette Actual palette for drawing.
*/
void markSign::drawLinear(canvas *sheet, colorPalette palette)
{
	sheet->setSegmentColor(palette.getColor(getColorName()));

	switch (getShape())
	{
		case SRectangle:
			sheet->lin_drawRectangleMarkSign(getBegin(), getSignLocation(), getSize());
			break;
		case SEllipse:
			sheet->lin_drawEllipseMarkSign(getBegin(), getSignLocation(), getSize());
			break;
		default:
			break;
	}
			
	
}

/**
* Method for linear draw of sign and name of mark.
* @param sheet Actual sheet for drawing sign.
* @param palette Actual palette for drawing.
* @param name Name of mark for draw.
*/
void markSign::drawLinear(canvas *sheet, colorPalette palette, string name)
{
	drawLinear(sheet, palette);
	sheet->lin_drawMarkSignName(getBegin(), getSize(), name, Color::Black);
}

/**
* Method for circular draw of mark.
* @param sheet Actual sheet for drawing sign.
* @param palette Actual palette for drawing.
*/
void markSign::drawCircular(canvas *sheet, colorPalette palette)
{
	sheet->setSegmentColor(palette.getColor(getColorName()));

	switch (getShape())
	{
		case SRectangle:
			sheet->cir_drawRectangleMarkSign(getBegin(), getSignLocation(), getSize());
			break;
		case SEllipse:
			sheet->cir_drawEllipseMarkSign(getBegin(), getSignLocation(), getSize());
			break;
		default:
			break;
	}
}

/**
* Method for circular draw of sign and name of mark.
* @param sheet Actual sheet for drawing sign.
* @param palette Actual palette for drawing.
* @param name Name of mark for draw.
*/
void markSign::drawCircular(canvas *sheet, colorPalette palette, string name)
{
	drawCircular(sheet, palette);
	sheet->cir_drawMarkSignName(getBegin(), getSize(), name, Color::Black);
}