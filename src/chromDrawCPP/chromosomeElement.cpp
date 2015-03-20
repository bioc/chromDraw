/*
* Name: chromosomeElement.cpp
* Description: Definition basic methods for basic elements of chromosome
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#include "chromosomeElement.h"

/**
* Constructor for chromosomeElement.
*/
chromosomeElement::chromosomeElement(void)
{
	type = NillItem;
}

/**
* Destructor for chromosomeElement.
*/
chromosomeElement::~chromosomeElement(void)
{

}

/**
* Function for set type of element.
* @param t Type of element.
*/
void chromosomeElement::setElementType(EChromosomeElementType t)
{
	type = t;
}

/**
* Get element type.
* @return Type of element.
*/
chromosomeElement::EChromosomeElementType chromosomeElement::getElementType()
{
	return type;
}

/**
* Function for set name of element.
* @param s Name of element.
*/
void chromosomeElement::setName(string s)
{
	if(s.compare(EMPTYSTRING) == 0)
	{
		name = "";
	}
	else
	{
		name = s;
	}
}

/**
* Function get name of element.
* @return Name of element.
*/
string chromosomeElement::getName()
{
	return name;
}

/**
* Function for set alias string.
* @param s String of alias.
*/
void chromosomeElement::setAlias(string s)
{
	alias = s;
}

/**
* Function get alias string.
* @return Get alias string.
*/
string chromosomeElement::getAlias()
{
	return alias;
}

/**
* Function for set begin of element.
* @param i Begin value of element.
*/
void chromosomeElement::setBegin(int i)
{
	start = i;
}

/**
* Get element begin value.
* @return Begin of element.
*/
int chromosomeElement::getBegin()
{
	return start;
}

/**
* Function for set end of element.
* @param i End value of element.
*/
void chromosomeElement::setEnd(int i)
{
	stop = i;
}

/**
* Get element end value.
* @return End of element.
*/
int chromosomeElement::getEnd()
{
	return stop;
}

/**
* Function for set color name.
* @param s String of color name.
*/
void chromosomeElement::setColorName(string s)
{
	colorName = s;
}

/**
* Get string of color name.
* @return String of color name.
*/
string chromosomeElement::getColorName()
{
	return colorName;
}

/**
* Method for draw linear name of chromosome element.
* @param sheet Actual sheet for drawing text.
*/
void chromosomeElement::drawLinearName(canvas *sheet)
{

}

/**
* Method for draw circular name of chromosome element.
* @param sheet Actual sheet for drawing text.
*/
void chromosomeElement::drawCircularName(canvas *sheet)
{
}

// -----------------------------------------------
// ------------ Virtual Methods ------------------
// -----------------------------------------------

/**
* Virtual method for linear draw of element.
* @param sheet Actual sheet for drawing element.
* @param palette Actual palette for drawing.
*/
void chromosomeElement::drawLinear(canvas *sheet, colorPalette palette)
{
}

/**
* Virtual method for linear draw of element and element name.
* @param sheet Actual sheet for drawing element.
* @param palette Actual palette for drawing.
* @param name Name of element for draw.
*/
void chromosomeElement::drawLinear(canvas *sheet, colorPalette palette, string name)
{
}

/**
* Virtual method for circular draw of element.
* @param sheet Actual sheet for drawing element.
* @param palette Actual palette for drawing.
*/
void chromosomeElement::drawCircular(canvas *sheet, colorPalette palette)
{
}

/**
* Virtual method for circular draw of element and element name.
* @param sheet Actual sheet for drawing element.
* @param palette Actual palette for drawing.
* @param name Name of element for draw.
*/
void chromosomeElement::drawCircular(canvas *sheet, colorPalette palette, string name)
{
}
