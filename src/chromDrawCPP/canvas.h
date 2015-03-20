/*
* Name: canvas.h
* Description: Declaration methods and constant for class canvas.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef CANVAS_H_
#define CANVAS_H_
//#pragma once

#include <string>
#include <vector>
#include <cmath>

#include <Board.h>
#include "color.h"
#include "charsLenghts.h"

#define PAGEHEIGHT 210 // Output page size
#define PAGEWIDTH	297	// Output page size

#define MAXLINSCALE 900.0	// Maximum value for drawing linear chromosome px ~ A4 page 1052
#define BORDER 0.07*MAXLINSCALE	// Border of picture

#define LIN_CHROMOSOMDISTANC 200	// Distance between two linear chromosomes
#define CIR_CIRCLEDISTANC 100			// Distance between two circular chromosomes
#define CIR_STARTRADIUS	500			// Radius of first circle
#define CHROMOSOMEWIDTH 60			// Each chromosomes widht
#define TELOMERERADIUS 35				// Radius for telomere ends
//#define CHROMOSOMEDISTANCE 0.2		// Distance between two chromosomes
#define LIN_CENTROMEREHEIGHT 60			// Height / lenght of centromere

#define CIR_CENTROMEREHEIGHT 0.0075 // procentualni cast kruhu
#define CIR_CHROMOSOMEDISTANC 0.015// distance between two blocks
//#define CIR_CENTROMEREHEIGHT 0.015 // procentualni cast kruhu
//#define CIR_CHROMOSOMEDISTANC 0.03125 // distance between two blocks
//#define CIR_CHROMOSOMEDISTANC 0.0 // distance between two blocks

#define LINEWIDTH 1.5

#define ARIALWIDTH 540	// Arial widht for 10.0
#define FONTNAME Fonts::Helvetica
#define FONTSIZECHRNAME 30.0


#define THRESHOLDGREY 128.0		// threshold of grey intensity for decide black or white text

using namespace LibBoard;
using namespace std;

class canvas
{
	public:
		canvas(void);
		~canvas(void);

	private:
		bool lin_initState;	// linear drawing was initialized
		bool cir_initState;	// circular drawing was initialized
		string alias;	// alias name of canvas
		float last_x;	// x coordinate of pen
		float last_y; // y coordinate of pen
		float max_x; // max x coordinate for draw border
		float min_x; // minimum x coordinate for draw border
		float max_y; // max y coordinate for draw border
		float min_y; // minimum y coordinate for draw border
		Board sheet;	// sheet for paintig elements
		double lin_scale;	// conversion scale between chromosom bases lenght and picture size
		double cir_scale;
		int lin_countChr;	// number of chromosomes
		float cir_radius;	// actual radius for circle
		float cir_angle;	// last angle after drawing
		float cir_angle_startLastChromosome;	// angle of strat last drawed chromosome
		float cir_angle_stopLastChromosome;	// angle of stop last drawed chromosome

	public:
		void setAlias(string sAlias);
		string getAlias();
		void init();
		void save(string path);
		void setSegmentColor(int r, int g, int b);
		void setSegmentColor(color *c);

		// methods for linear drawing
		bool lin_isInit();
		void lin_init(int maxChromosomLenght, int count);	// maximu of lenght all chromosomes
		void lin_nextChromosom();
		void lin_drawSegment(int lenght);
		void lin_drawCentromere();
		void lin_drawChromosomeName(string name);
		void lin_drawBlockName(int lenght, string name, Color c);
		void lin_drawTelomere(bool north);

		// methods for circular drawing
		bool cir_isInit();
		void cir_init(unsigned long int lenght, int countChromosome, int countCentromere);	// maximu of lenght all chromosomes
		void cir_nextCircle(unsigned long int lenght, int countChromosome, int countCentromere, float maxStringLenghtChrName);
		void cir_drawSegment(int lenght);
		void cir_drawCentromere();
		void cir_drawChromosomeName(string name);
		void cir_drawBlockName(int lenght, string name, Color c);
		void cir_drawTelomere(bool north);


		float rgbToGray(float r, float g, float b);
		float rgbToGray(color *c);
};


#endif // CANVAS_H_ 
