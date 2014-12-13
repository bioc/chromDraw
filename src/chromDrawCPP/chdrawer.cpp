/*
* Name: chdrawer.cpp
* Description: Main functionality of chromosome drawer.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#include <iostream>
#include <cstdio>

#include "parameters.h"
#include "ideogram.h"



using namespace std;

// R package has own main function similar with this.
/*
int main(int argc, char *argv[])
{
	parameters *param = new parameters(); // parameters
	
	// load parameters
	param->loadArguments(argc,argv);

	ideogram *i = new ideogram();

	if(0 != i->loadColorPalette(param->getColourPath()))
	{
			delete(i);
			delete(param);
			exit(-1);
	}
	
	if(0 != i->loadMatrix(param->getInputMatrixPath()))
	{
			delete(i);
			delete(param);
			exit(-1);
	}

	
	
	i->draw();
	i->saveImages(param->getOutputPath());

	delete(i);
	delete(param);
	
	exit (0);
}
*/
