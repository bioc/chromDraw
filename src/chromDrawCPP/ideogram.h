/*
* Name: ideogram.h
* Description: Declaration methods and arguments for ideogram class.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef IDEOGRAM_H_
#define IDEOGRAM_H_
//#pragma once

#include <sys/types.h> // for stat().
#include <sys/stat.h> // for stat().

#include <list>
#include "karyotype.h"
#include "canvas.h"
#include "colorPalette.h"
#include "parsing.h"

#define LINEARIMGNAME "linear."		// default name of linear images
#define CIRCULARIMGNAME "circular." // default name of circular images
#define KARYOTYPE "KARYOTYPE"		// key word for loading data
#define BEGIN "BEGIN"			// key word for loading data
#define END "END"			// key word for loading data
#define COMMENT '#'			// key word for loading data

#define KARYOTYPEITEMSCOUNT 4	// count of items at one line of definiton caryopte

using namespace std;


class ideogram
{
	private:
		list<karyotype*> ideogram_p;	// list with karyotyeps
		colorPalette	palette;	// color palette
		list<canvas*> lin_sheets;	// list with sheet for linear images
		canvas *cir_sheet;		// sheet for linear and circular images

	public:
		ideogram(void);
		~ideogram(void);

		void draw();
		int loadMatrix(string path);
		void pushKaryotype(karyotype *k);
		void popKaryotype(string sAlias);
		karyotype* getKaryotype(string sAlias);
		void pushCanvas(canvas *c);
		void popCanvas(string sAlias);
		canvas* getCanvas(string sAlias);
		void saveImages(string path);
		int loadColorPalette(string path);

};

#endif // IDEOGRAM_H_

