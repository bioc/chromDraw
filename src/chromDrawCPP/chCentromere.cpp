/*
* Name: chCentromere.cpp
* Description: Definition methodes for chromosome centromere.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/
#include "chCentromere.h"

/**
* Constructor for class chCentromere.
*/
chCentromere::chCentromere(void)
{
	this->setElementType(Centromere);
	this->setBegin(0);
	this->setEnd(0);
}

/**
* Constructor for class chCentromere.
* @param t type of element.
*/
chCentromere::chCentromere(EChromosomeElementType t)
{
	this->setElementType(t);
	this->setBegin(0);
	this->setEnd(0);
}

/**
* Destructor for class chCentromere.
*/
chCentromere::~chCentromere(void)
{
}

/**
* Methode for linear drawing centromere.
* @param sheet Output sheet for drawing.
* @param palette Actual color palette for drawing.
*/
void chCentromere::drawLinear(canvas *sheet, colorPalette palette)
{
	sheet->lin_drawCentromere();
}

/**
* Methode for linear drawing centromere.
* @param sheet Output sheet for drawing.
* @param palette Actual color palette for drawing.
* @param name Name of centromere.
*/
void chCentromere::drawLinear(canvas *sheet, colorPalette palette, string name)
{
	sheet->lin_drawCentromere();
}

/** 
* Methode for circular drawing centromere.
* @param sheet Output sheet for drawing .
* @param palette Actual color palette for drawing.
*/
void chCentromere::drawCircular(canvas *sheet, colorPalette palette)
{
	sheet->cir_drawCentromere();
}

/**
* Methode for circular drawing centromere.
* @param sheet Output sheet for drawing.
* @param palette Actual color palette for drawing.
* @param name Name of centromere.
*/
void chCentromere::drawCircular(canvas *sheet, colorPalette palette, string name)
{
	sheet->cir_drawCentromere();
}
