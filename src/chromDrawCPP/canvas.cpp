/*
* Name: canvas.cpp
* Description: Definition methods for draw basic elements.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/


#include "canvas.h"

/**
* Constructor for class canvas.
*/
canvas::canvas(void)
{
	canvas::init();
}

/**
* Destructor for class canvas.
*/
canvas::~canvas(void)
{
}

/**
 * Set canvas alias name.
 * @param sAlias String with alias name of canvas.
 */
void canvas::setAlias(string sAlias)
{
	alias = sAlias;
}

/** 
 * Get alias name of curent canvas.
 * @return Return string with alias name.
 */
string canvas::getAlias()
{
	return alias;
}




/**
* Method for initialization sheet settings
*/
void canvas::init()
{
	lin_initState = false;
	cir_initState = false;
	sheet.setPenColorRGBi(0, 0, 0);
	sheet.setLineWidth(LINEWIDTH);
	max_x = 0.0;
	max_y = 0.0;
	min_x = 0.0;
	min_y = 0.0;

	last_x = 0.0;
	last_y = 0.0;
	lin_countChr = 0;
	cir_radius = 0.0;
	cir_angle = 0.0;
	cir_angle_startLastChromosome = 0.0;
	cir_angle_stopLastChromosome = 0.0;
}

/**
* Mehtode for saveing to image svg and eps.
* @param path Path to save picture.
* @return Retrun saveing status, if it si OK return 0.
*/
void canvas::save(string path)
{
	/*
	// draw border
	sheet.setPenColorRGBi(255, 255, 255);
	sheet.drawDot(0.0 - BORDER, 0.0 + BORDER);
	sheet.drawDot(0.0 - BORDER, PAGEWIDTH - BORDER);
	sheet.drawDot(PAGEHEIGHT + BORDER, 0.0 + BORDER);
	sheet.drawDot(PAGEHEIGHT + BORDER, PAGEWIDTH - BORDER);
	*/
	// save
	//double x = abs(min_x)+abs(max_x);
	//double y = abs(min_y)+abs(max_y);
	
	sheet.setPenColorRGBi(255, 255, 255);
	sheet.drawDot(min_x, min_y);
	sheet.drawDot(max_x, max_y);

	sheet.save((path+"svg").c_str());
	sheet.save((path+"eps").c_str());
//		sheet.save((path+"svg").c_str());
//  	sheet.save((path+"eps").c_str());
	//sheet.saveSVG(path.c_str(), PAGEHEIGHT, PAGEWIDTH);
}

/**
* Set RGB color for segment.
* @param r Red color.
* @param g Green color.
* @param b Blue color.
*/
void canvas::setSegmentColor(int r, int g, int b)
{
	sheet.setFillColorRGBi(r,g,b);
}

/**
* Set RGB color for segment.
* @param c RGB color.
*/
void canvas::setSegmentColor(color *c)
{
	if(c != NULL)
	{
		setSegmentColor(c->getRed(), c->getGreen(), c->getBlue());
	}
}

// ------- methods for linear drawing -------------

/**
 * Method for check if linear coordinate were initialized.
 * @return Return TRUE when was initialized else return FALSE.
 */
bool canvas::lin_isInit()
{
	return lin_initState;
}

/**
* Linear draw initialization.
* @param maxChromosomLenght Maximal lenght of all drawing chromosomes.
* @param count Count is number of chromosomes for drawing.
*/
void canvas::lin_init(int maxChromosomLenght, int count)
{
	lin_initState = true;
	lin_scale = MAXLINSCALE/maxChromosomLenght;
	lin_countChr = count;
}

/**
* Set coordinates in sheet for next chromosom.
*/
void canvas::lin_nextChromosom()
{
	last_x += LIN_CHROMOSOMDISTANC;
	last_y = 0.0;
	if(last_x > max_x)
		max_x = last_x;
}

/**
* Draw linear segment of chromosome.
* @param lenght Lenght of chromosome.
*/
void canvas::lin_drawSegment(int lenght)
{
	sheet.setLineWidth( LINEWIDTH );
	sheet.setPenColor( Color::Black );
	sheet.drawRectangle(last_x-0.5*CHROMOSOMEWIDTH, last_y, CHROMOSOMEWIDTH, lenght*lin_scale);
	last_y -= (float)(lenght*lin_scale);
	if(last_y < min_y)
		min_y = last_y;
	if(last_y > max_y)
		max_y = last_y;
}

/**
* Draw linear centromere.
*/
void canvas::lin_drawCentromere()
{
	sheet.setLineWidth( LINEWIDTH );
	sheet.setPenColor( Color::Black );
	sheet.drawLine(last_x-0.5*CHROMOSOMEWIDTH, last_y, last_x+0.5*CHROMOSOMEWIDTH, last_y-LIN_CENTROMEREHEIGHT);
	sheet.drawLine(last_x+0.5*CHROMOSOMEWIDTH, last_y, last_x-0.5*CHROMOSOMEWIDTH, last_y-LIN_CENTROMEREHEIGHT);
	sheet.drawLine(last_x-0.5*CHROMOSOMEWIDTH, last_y, last_x+0.5*CHROMOSOMEWIDTH, last_y);
	sheet.drawLine(last_x-0.5*CHROMOSOMEWIDTH, last_y-LIN_CENTROMEREHEIGHT, last_x+0.5*CHROMOSOMEWIDTH, last_y-LIN_CENTROMEREHEIGHT);
	last_y -= LIN_CENTROMEREHEIGHT;
	if(last_y < min_y)
		min_y = last_y;
	if(last_y > max_y)
		max_y = last_y;
}

/**
* Draw linear name of chromosome.
* @param name Name of chromosome.
*/
void canvas::lin_drawChromosomeName(string name)
{
	sheet.setPenColor(Color::Black).setFont(FONTNAME, FONTSIZECHRNAME);

	// calculate coordinates for start text
	double x = ((FONTSIZECHRNAME * (charsLenghts::getStringPxLengh(name)/2.0)) / 10);
	double y = ARIALWIDTH * FONTSIZECHRNAME / 1052.0;
	
	sheet.drawText(last_x - x, last_y + y, name.c_str());

	if(last_y + y + FONTSIZECHRNAME < min_y)
		min_y = (float)(last_y + y + FONTSIZECHRNAME);
	if(last_y + y + FONTSIZECHRNAME > max_y)
		max_y = (float)(last_y + y + FONTSIZECHRNAME);
	if(last_x - x < min_x)
		min_x = (float)(last_x - x);
	if(last_x - x > max_x)
		max_x = (float)(last_x - x);

}

/**
* Draw name for last drawed block.
* @param lenght Lenght of last block.
* @param name Name of block.
* @param c Color of drawing text.
*/
void canvas::lin_drawBlockName(int lenght, string name, Color c)
{
	sheet.setPenColor(c).setFont(FONTNAME, FONTSIZECHRNAME);
	
	// calculate coordinates for start text
	double x = ((FONTSIZECHRNAME * (charsLenghts::getStringPxLengh(name)/2.0)) / 10);
	double y = (0.5 * lenght * lin_scale) - (ARIALWIDTH * FONTSIZECHRNAME / 744.0) / 2.0;
	
	sheet.drawText(last_x - x, last_y + y, name.c_str());
}

/**
* Draw north or south telomere.
* @param north TRUE for north telomere and FALSE for south telomere.
*/
void canvas::lin_drawTelomere(bool north)
{
	vector<Point> points;
	double y;

	// calculate start y coordinate
	if(north)
	{
		y = last_y - TELOMERERADIUS - LINEWIDTH;
	}
	else
	{
		double x = -0.5*CHROMOSOMEWIDTH + LINEWIDTH;
		y = last_y + sqrt(TELOMERERADIUS*TELOMERERADIUS - x*x) - 0.5*LINEWIDTH;
	}

	// Create points of telomere radius
	for(double x = -0.5*CHROMOSOMEWIDTH + LINEWIDTH; x <= 0.5*CHROMOSOMEWIDTH - LINEWIDTH; x += 0.5)
	{
		if(north)
		{
			points.push_back( Point( last_x + x, y + sqrt(TELOMERERADIUS*TELOMERERADIUS - x*x) ) );
		}
		else
		{
			points.push_back( Point( last_x + x, y - sqrt(TELOMERERADIUS*TELOMERERADIUS - x*x) ) );
		}
	}

	// Draw black circle segment and fill it
	sheet.setLineWidth( LINEWIDTH );
	sheet.setPenColor( Color::Black );
	sheet.setFillColor( Color::Black);
	sheet.drawClosedPolyline(points);

	// calculate stop y coordinate
	if(north)
	{
		double x = 0.5*CHROMOSOMEWIDTH;
		last_y = (float)(y + sqrt(TELOMERERADIUS*TELOMERERADIUS - x*x) + LINEWIDTH);
	}
	else
	{
		double x = -0.5*CHROMOSOMEWIDTH + LINEWIDTH;
		last_y = (float)(y + sqrt(TELOMERERADIUS*TELOMERERADIUS - x*x) - LINEWIDTH);
	}


	if(last_y < min_y)
		min_y = last_y;
	if(last_y > max_y)
		max_y = last_y;
}



// ------- methods for circular drawing -----------

/**
* Check circular drawing initialization.
* @return TRUE if circular draw was initialized else return FALSE.
*/
bool canvas::cir_isInit()
{
	return cir_initState;
}

/**
* Ciruclar draw initialization.
* @param lenght Sum lenght of all chromosomes in curent karyotype.
* @param countChromosome Count of all chromosomes in curent karyotype.
* @param countCentromere Count of all centromeres in curent karyotype.
*/
void canvas::cir_init(unsigned long int lenght, int countChromosome, int countCentromere)
{
	cir_initState = true;
	cir_angle = 0.0;

	int t = (int)((countChromosome / 3)+0.5); // zvetseni  pocatecniho radiusu pri velkem poctu chromosomu
	cir_radius = (float)(CIR_STARTRADIUS + t*150);
	double p = (1.0 - countChromosome*CIR_CHROMOSOMEDISTANC - countCentromere*CIR_CENTROMEREHEIGHT ); // percentage of spaces and centromeres
	cir_scale = 2 * M_PI * cir_radius * p / lenght;

	cir_angle_startLastChromosome = 0.0;
	cir_angle_stopLastChromosome = 0.0;
}

/**
* Set coordinates in sheet for next karyotype.
* @param lenght Sum of lenghte each chromosomes.
* @param countChromosome Count of chromosomes.
* @param countCentromere Total count of centromeres for curent karyotype.
* @param maxStringLenghtChrName Maximum lenght of chromosom name in px.
*/
void canvas::cir_nextCircle(unsigned long int lenght, int countChromosome, int countCentromere, float maxStringLenghtChrName)
{
	cir_angle = 0.0;
	cir_radius += 0.5*CHROMOSOMEWIDTH;
	cir_radius += CIR_CIRCLEDISTANC;
	cir_radius += (float)((maxStringLenghtChrName) * FONTSIZECHRNAME / 10.0);
	cir_scale = 2 * M_PI * cir_radius * (1.0 - countChromosome*CIR_CHROMOSOMEDISTANC - countCentromere*CIR_CENTROMEREHEIGHT ) / lenght;

	cir_angle_startLastChromosome = 0.0;
	cir_angle_stopLastChromosome = 0.0;
	
	max_x = (float)(cir_radius + 0.5*CHROMOSOMEWIDTH);
	max_y = (float)(cir_radius + 0.5*CHROMOSOMEWIDTH);
	min_x = (float)((-1)*cir_radius - 0.5*CHROMOSOMEWIDTH);
	min_y = (float)((-1)*cir_radius - 0.5*CHROMOSOMEWIDTH);
}

/**
* Draw circular segment of chromosome.
* @param lenght Lenght of chromosome.
*/
void canvas::cir_drawSegment(int lenght)
{
	vector<Point> points;
	double stop_angle = cir_angle + (lenght * cir_scale) / cir_radius;
	//double stop_angle_upper = stop_angle_lower + 0.002;

	// lower radius
	for ( double a = cir_angle; a <= stop_angle; a += 0.002 ) 
	{
	  points.push_back( Point( sin(a) * (cir_radius - CHROMOSOMEWIDTH/2), cos(a) * (cir_radius - CHROMOSOMEWIDTH/2) ) );
	 }
	// upper radius
	for ( double a = stop_angle; a >= cir_angle; a -= 0.002 ) 
	{
	  points.push_back( Point( sin(a) * (cir_radius + CHROMOSOMEWIDTH/2), cos(a) * (cir_radius + CHROMOSOMEWIDTH/2) ) );
	}

	sheet.setLineWidth( LINEWIDTH );
	sheet.setPenColor( Color::Black );
	sheet.drawClosedPolyline(points);

	cir_angle = (float)(stop_angle); 
}

/**
* Draw circular centromere.
*/
void canvas::cir_drawCentromere()
{
	double stop_angle = cir_angle + 2*M_PI * CIR_CENTROMEREHEIGHT;
	
	// count positions for lower segment of circle
	double start_x0, start_y0, stop_x0, stop_y0;
	start_x0 = sin(cir_angle) * (cir_radius - CHROMOSOMEWIDTH/2);
	start_y0 = cos(cir_angle) * (cir_radius - CHROMOSOMEWIDTH/2);
	stop_x0 = sin(stop_angle) * (cir_radius - CHROMOSOMEWIDTH/2);
	stop_y0 = cos(stop_angle) * (cir_radius - CHROMOSOMEWIDTH/2);

	// count positions for upper segment of circle
	double start_x1, start_y1, stop_x1, stop_y1;
	start_x1 = sin(cir_angle) * (cir_radius + CHROMOSOMEWIDTH/2);
	start_y1 = cos(cir_angle) * (cir_radius + CHROMOSOMEWIDTH/2);
	stop_x1 = sin(stop_angle) * (cir_radius + CHROMOSOMEWIDTH/2);
	stop_y1 = cos(stop_angle) * (cir_radius + CHROMOSOMEWIDTH/2);

	sheet.setLineWidth( LINEWIDTH );
	sheet.setPenColor( Color::Black );
	sheet.drawLine(start_x0, start_y0, stop_x1, stop_y1);
	sheet.drawLine(start_x1, start_y1, stop_x0, stop_y0);
	sheet.drawLine(start_x0, start_y0, start_x1, start_y1);
	sheet.drawLine(stop_x0, stop_y0, stop_x1, stop_y1);


	cir_angle = (float)(stop_angle);
}


/**
* Draw name of choromosom.
* @param name Chromosoma name.
*/
void canvas::cir_drawChromosomeName(string name)
{
	// calculate position of mid coordinates for curent chromosom
	float cir_textRotation = (float)(-1.0*(cir_angle_startLastChromosome + (cir_angle_stopLastChromosome - cir_angle_startLastChromosome)/2.0));

	sheet.setPenColor(Color::Black).setFont(FONTNAME, FONTSIZECHRNAME);
	sheet.drawText(0.0, 0.0, name.c_str());
	
	// text lenght in pixels
	float textLen = (float)(charsLenghts::getStringPxLengh(name+" ") * FONTSIZECHRNAME / 10.0);

	if(cir_textRotation > (-1.0*M_PI))
	{
		// right side of circle
		sheet.last<Text>().translate(0.0, 0.5*charsLenghts::getStringPxLengh(" ") * FONTSIZECHRNAME / 10.0 + 0.5 * CHROMOSOMEWIDTH);
		sheet.last<Text>().rotate(90 * Board::Degree);
	
		if(max_x < cir_radius + 0.5 * CHROMOSOMEWIDTH + textLen)
		{
			max_x = (float)(cir_radius + 0.5 * CHROMOSOMEWIDTH + textLen);
		}
	}
	else
	{
		// left side of circle
		//sheet.last<Text>().translate(0.0, ARIALWIDTH * FONTSIZECHRNAME / 1052.0 + CHROMOSOMEWIDTH);
		sheet.last<Text>().translate(0.0, (charsLenghts::getStringPxLengh(name) + 0.5*charsLenghts::getStringPxLengh(" ")) * FONTSIZECHRNAME / 10 + 0.5 * CHROMOSOMEWIDTH);
		sheet.last<Text>().rotate(-90 * Board::Degree);

		if(min_x > (-1)*cir_radius - 0.5 * CHROMOSOMEWIDTH - textLen)
		{
			min_x = (float)((-1)*cir_radius - 0.5 * CHROMOSOMEWIDTH - textLen);
		}
	}

	if(max_y < cir_radius + 0.5 * CHROMOSOMEWIDTH + textLen)
	{
		max_y = (float)(cir_radius + 0.5 * CHROMOSOMEWIDTH + textLen);
	}
	if(min_y > (-1)*cir_radius - 0.5 * CHROMOSOMEWIDTH - textLen)
	{
		min_y = (float)((-1)*cir_radius - 0.5 * CHROMOSOMEWIDTH - textLen);
	}

	sheet.last<Text>().translate(0.0, cir_radius + 0.15*CIR_CIRCLEDISTANC);
	sheet.last<Text>().rotate(cir_textRotation, Point(0.0, 0.0));

}


/**
* Draw name of chromosome block.
* @param lenght Lenght of curent block.
* @param name Name of block.
* @param c Color of text.
*/
void canvas::cir_drawBlockName(int lenght, string name, Color c)
{
	float blockStartAngle = (float)(cir_angle - (lenght * cir_scale) / cir_radius);
	// rozdeleni bloku na poloviny  nasledne posunuti
	float cir_textRotation = (float)(-1.0*(blockStartAngle + (cir_angle - blockStartAngle)/2.0));

	sheet.setPenColor(c).setFont(FONTNAME, FONTSIZECHRNAME);
	
	sheet.drawText(0.0, 0.0, name.c_str());
//sheet.last<Text>().translate(0.0, -1.0 * ARIALWIDTH * FONTSIZECHRNAME / 1052.0 - 0.5 * CHROMOSOMEWIDTH);
	
	
	
	if(cir_textRotation > (-1.0*M_PI))
	{
		//sheet.last<Text>().translate(0.0, -1.0 * name.length() * ARIALWIDTH * FONTSIZECHRNAME / 526.0);
		sheet.last<Text>().translate(0.0, -0.5 * charsLenghts::getStringPxLengh(name) * FONTSIZECHRNAME / 10.0);
		sheet.last<Text>().rotate(90 * Board::Degree);
	}
	else
	{
		sheet.last<Text>().translate(0.0, 0.5 * charsLenghts::getStringPxLengh(name) * FONTSIZECHRNAME / 10.0);
		sheet.last<Text>().rotate(-90 * Board::Degree);
	}
	sheet.last<Text>().translate(0.0, cir_radius);
	sheet.last<Text>().rotate(cir_textRotation, Point(0.0, 0.0));

	// korekce vzhledem k velikosti pisma
	if(cir_textRotation > (-1.0*M_PI))
	{
		sheet.last<Text>().rotate((-0.5*FONTSIZECHRNAME / cir_radius),  Point(0.0, 0.0));
	}
	else
	{
		sheet.last<Text>().rotate((0.5*FONTSIZECHRNAME / cir_radius),  Point(0.0, 0.0));
	}
}

/**
* Draw telomeres - start/end point of chromosom.
* @param north TRUE for north telomere and FALSE for south telomere.
*/
void canvas::cir_drawTelomere(bool north)
{
	vector<Point> points;

	//double x;
	//x = sqrt(TELOMERERADIUS*TELOMERERADIUS - (0.5*CHROMOSOMEWIDTH)*(0.5*CHROMOSOMEWIDTH));
	//double Sx = 0.0 + x;			// center of telomere radius
	//double Sy = cir_radius;	// center of telomere radius

	if(north)
	{
		cir_angle += (float)(CIR_CHROMOSOMEDISTANC * M_PI);
	}

	//double radius_telomere = (x - 2*LINEWIDTH) / cir_radius;	// radius of width telomere

	float telomereWidth = (float)(sqrt(TELOMERERADIUS*TELOMERERADIUS - 0.0) - sqrt(TELOMERERADIUS*TELOMERERADIUS - 0.5*CHROMOSOMEWIDTH*0.5*CHROMOSOMEWIDTH)); 

	for(double x = -0.5*CHROMOSOMEWIDTH + LINEWIDTH; x <= 0.5*CHROMOSOMEWIDTH - LINEWIDTH; x += 0.5)
	{
		Point tmpPoint;

		if(north)
		{
			tmpPoint = Point(x, sqrt(TELOMERERADIUS*TELOMERERADIUS - x*x)).rotate(90 * Board::Degree, Point(0.0, 0.0)); 
			tmpPoint += Point(TELOMERERADIUS - telomereWidth + LINEWIDTH, cir_radius);
			cir_angle_startLastChromosome = cir_angle;
		}
		else
		{
			tmpPoint = Point(x, sqrt(TELOMERERADIUS*TELOMERERADIUS - x*x)).rotate(-90 * Board::Degree, Point(0.0, 0.0));
			tmpPoint += Point(- TELOMERERADIUS + telomereWidth - LINEWIDTH, cir_radius);
		}
		
		tmpPoint.rotate(-cir_angle, Point(0.0, 0.0));
		points.push_back(tmpPoint);
		
	}

	// Draw black circle segment and fill it
	sheet.setLineWidth( LINEWIDTH );
	sheet.setPenColor( Color::Black );
	sheet.setFillColor( Color::Black);
	sheet.drawClosedPolyline(points);

	if(!north)
	{	// actualize end position of chromosom.
		cir_angle += (float)(CIR_CHROMOSOMEDISTANC * M_PI);
		cir_angle_stopLastChromosome = cir_angle;
	}

}



/**
* Convert RGB color to grayscale.
* @param r Red color.
* @param g Green color.
* @param b Blue color.
* @return Greyscale value.
*/
float canvas::rgbToGray(float r, float g, float b)
{
	return (float)(0.299*r + 0.589*g + 0.114*b);
}

/** Convert RGB color to grayscale.
* @param c Input color.
* @return Greyscale value.
*/
float canvas::rgbToGray(color *c)
{
	if(c != NULL)
	{
		return (float)(0.299*c->getRed() + 0.589*c->getGreen() + 0.114*c->getBlue());
	}
	else
	{
		return 0.0;
	}
}
