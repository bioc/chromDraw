/*
* Name: chromosomeMark.cpp
* Description: Definition basic methods for marks of chromosome
* Author: Jan Janecka, ing  c 2015
* Contact: jan.janecka@ceitec.muni.cz
*/


#include "chromosomeMark.h"


/**
* Constructor for chromosomeMark.
*/
chromosomeMark::chromosomeMark(void)
{
	type = TNillItem;
	location = LNillItem;
}


/**
* Destructor for chromosomeMark.
*/
chromosomeMark::~chromosomeMark(void)
{
}

/**
* Function for set type of mark.
* @param t Type of mark.
*/
void chromosomeMark::setMarkType(EChromosomeMarkType t)
{
	type = t;
}

/**
* Get mark type.
* @return Type of mark.
*/
chromosomeMark::EChromosomeMarkType chromosomeMark::getMarkType()
{
	return type;
}
/**
* Function for set mark location on the chromosome element.
* @param l Type of chromosome element.
*/
void chromosomeMark::setMarkLocation(EChromosomeMarkLocation l)
{
	location = l;
}

/**
* Get mark location on the chromosome element.
* @return Type of chromosome element.
*/
chromosomeMark::EChromosomeMarkLocation chromosomeMark::getMarkLocation()
{
	return location;
}

/**
* Function for set name of mark.
* @param s Name of mark.
*/
void chromosomeMark::setName(string s)
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
* Function get name of mark.
* @return Name of mark.
*/
string chromosomeMark::getName()
{
	return name;
}


/**
* Function for set begin of mark.
* @param i Begin value of mark.
*/
void chromosomeMark::setBegin(int i)
{
	start = i;
}

/**
* Get mark begin value.
* @return Begin of mark.
*/
int chromosomeMark::getBegin()
{
	return start;
}

/**
* Function for set end of mark.
* @param i End value of mark.
*/
void chromosomeMark::setEnd(int i)
{
	stop = i;
}

/**
* Get end value of mark.
* @return End of mark.
*/
int chromosomeMark::getEnd()
{
	return stop;
}

/**
* Function for set color name.
* @param s String of color name.
*/
void chromosomeMark::setColorName(string s)
{
	colorName = s;
}

/**
* Get string of color name.
* @return String of color name.
*/
string chromosomeMark::getColorName()
{
	return colorName;
}

/**
* Function for set size of mark.
* @param si Size of mark.
*/
void chromosomeMark::setSize(int si)
{
	size = si;
}

/**
* Get size of mark
* @return Size of mark
*/
int chromosomeMark::getSize()
{
	return size;
}

// -----------------------------------------------
// ------------ Virtual Methods ------------------
// -----------------------------------------------

/**
* Virtual method for linear draw of mark.
* @param sheet Actual sheet for drawing mark.
* @param palette Actual palette for drawing.
*/
void chromosomeMark::drawLinear(canvas *sheet, colorPalette palette)
{
}

/**
* Virtual method for linear draw of mark and name of mark.
* @param sheet Actual sheet for drawing mark.
* @param palette Actual palette for drawing.
* @param name Name of mark for draw.
*/
void chromosomeMark::drawLinear(canvas *sheet, colorPalette palette, string name)
{
}

/**
* Virtual method for circular draw of mark.
* @param sheet Actual sheet for drawing mark.
* @param palette Actual palette for drawing.
*/
void chromosomeMark::drawCircular(canvas *sheet, colorPalette palette)
{
}

/**
* Virtual method for circular draw of mark and name of mark.
* @param sheet Actual sheet for drawing mark.
* @param palette Actual palette for drawing.
* @param name Name of mark for draw.
*/
void chromosomeMark::drawCircular(canvas *sheet, colorPalette palette, string name)
{
}
