/*
* Name: chromosomeSign.cpp
* Description: Definition basic methods for marks of chromosome
* Author: Jan Janecka, ing  c 2015
* Contact: jan.janecka@ceitec.muni.cz
*/


#include "chromosomeSign.h"


/**
* Constructor for chromosomeSign.
*/
chromosomeSign::chromosomeSign(void)
{
	type = TNillItem;
	location = canvas::LNillItem;
	start=0;
	stop=0;
	colorName="";

}


/**
* Destructor for chromosomeSign.
*/
chromosomeSign::~chromosomeSign(void)
{
}

/**
* Function for set type of sign.
* @param t Type of sign.
*/
void chromosomeSign::setSignType(EChromosomeSignType t)
{
	type = t;
}

/**
* Get sign type.
* @return Type of sign.
*/
chromosomeSign::EChromosomeSignType chromosomeSign::getSignType()
{
	return type;
}
/**
* Function for set sign location on the chromosome element.
* @param l Type of chromosome element.
*/
void chromosomeSign::setSignLocation(canvas::ELocationOnChromosome l)
{
	location = l;
}

/**
* Get sign location on the chromosome element.
* @return Type of chromosome element.
*/
canvas::ELocationOnChromosome chromosomeSign::getSignLocation()
{
	return location;
}

/**
* Function for set name of sign.
* @param s Name of sign.
*/
void chromosomeSign::setName(string s)
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
* Function get name of sign.
* @return Name of sign.
*/
string chromosomeSign::getName()
{
	return name;
}


/**
* Function for set alias string of sign.
* @param s Alias string of sign.
*/
void chromosomeSign::setAlias(string s)
{
	alias = s;
}

/**
* Function for get alias string of sign.
* @return Alias string of sign.
*/
string chromosomeSign::getAlias()
{
	return alias;
}

/**
* Function for set begin of sign.
* @param i Begin value of sign.
*/
void chromosomeSign::setBegin(int i)
{
	start = i;
}

/**
* Get sign begin value.
* @return Begin of sign.
*/
int chromosomeSign::getBegin()
{
	return start;
}

/**
* Function for set end of sign.
* @param i End value of sign.
*/
void chromosomeSign::setEnd(int i)
{
	stop = i;
}

/**
* Get end value of sign.
* @return End of sign.
*/
int chromosomeSign::getEnd()
{
	return stop;
}

/**
* Function for set color name.
* @param s String of color name.
*/
void chromosomeSign::setColorName(string s)
{
	colorName = s;
}

/**
* Get string of color name.
* @return String of color name.
*/
string chromosomeSign::getColorName()
{
	return colorName;
}

/**
* Function for set size of sign.
* @param si Size of sign.
*/
void chromosomeSign::setSize(int si)
{
	size = si;
}

/**
* Get size of sign
* @return Size of sign
*/
int chromosomeSign::getSize()
{
	return size;
}

// -----------------------------------------------
// ------------ Virtual Methods ------------------
// -----------------------------------------------

/**
* Virtual method for linear draw of sign.
* @param sheet Actual sheet for drawing sign.
* @param palette Actual palette for drawing.
*/
void chromosomeSign::drawLinear(canvas *sheet, colorPalette palette)
{
}

/**
* Virtual method for linear draw of sign and name of sign.
* @param sheet Actual sheet for drawing mark.
* @param palette Actual palette for drawing.
* @param name Name of sign for draw.
*/
void chromosomeSign::drawLinear(canvas *sheet, colorPalette palette, string name)
{
}

/**
* Virtual method for circular draw of sign.
* @param sheet Actual sheet for drawing sign.
* @param palette Actual palette for drawing.
*/
void chromosomeSign::drawCircular(canvas *sheet, colorPalette palette)
{
}

/**
* Virtual method for circular draw of sign and name of sign.
* @param sheet Actual sheet for drawing sign.
* @param palette Actual palette for drawing.
* @param name Name of sign for draw.
*/
void chromosomeSign::drawCircular(canvas *sheet, colorPalette palette, string name)
{
}
