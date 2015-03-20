/*
* Name: chromDraw.cpp
* Description: Main controling function of chrDrawer.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/
#include "parameters.h"

#include <Board.h>
#include <Rcpp.h>
#include <vector>
#include <string>

#include <iostream>
#include <cstdio>


#include "ideogram.h"



using namespace Rcpp;
using namespace LibBoard;
using namespace std;


/**
* Methode for dealocateing memory, phase with errors 2xx.
* @param p Pointer on attribute with parameters.
* @param i Pointer on atttribute with ideogram.
*/
void freeMemErr2xx(parameters *p, ideogram *i)
{ 
  delete(i);
	delete(p);
}

/**
* Methode for dealocateing memory, phase with errors 3xx.
* @param p Pointer on attribute with parameters.
* @param i Pointer on atttribute with ideogram.
*/
void freeMemErr3xx(parameters *p, ideogram *i)
{
	freeMemErr2xx(p,i);
}

//' Main chromDraw function. The main function that controls all other C++ 
//' functions.
//' 
//' @param argc Count of input parameters.
//' @param argv Vector with input parameters strings.
//' @return Return exit sate.
// [[Rcpp::export]]
int main_chromDraw(int argc, StringVector argv) {
    
    // convert arguments vector
    vector<char*> charv(argc);
    for(int i=0; i<argc; i++)
    {
      charv[i] = argv[i];
    }
    
    // copy from chrDrawer
    // replace argv to charv
    // replace cerr << "text" << endl;  to stop("text")
    parameters *param = new parameters(); // parameters
    ideogram *i = new ideogram();
  	
  	try
  	{
  
  		// load parameters
  		if(0 == param->loadArguments(argc,&*charv.begin()))
  		{
  
  				if(0 != i->loadColorPalette(param->getColourPath()))
  				{
  						delete(i);
  						delete(param);
  						return -1;
  				}
  	
  				if(0 != i->loadMatrix(param->getInputMatrixPath()))
  				{
  						delete(i);
  						delete(param);
  						return -1;
  				}
  	
  				i->draw(param->getUseScale());
  				i->saveImages(param->getOutputPath());
  
  				delete(i);
  				delete(param);
  		}
  
  	}
  	catch(int value)
  	{
  		cout << "Error number: " << value << endl;
  		switch (value)
  		{
  			// loading color palete errors
  			case 200:
          cout << param->getColourPath() << endl;
          freeMemErr2xx(param, i);
  				stop("Can not open file with colors. File or path does not exist.");
  				break;
  			case 201:
          freeMemErr2xx(param, i);
  			  stop("Bad count of lexems in line, who defined COLOR.");
  				break;
  			case 202:
  				freeMemErr2xx(param, i);
          stop("Color is already exists");
  				break;
  			
  			// loading data matrix
  			case 300:
          cout << param->getInputMatrixPath() << endl;
          freeMemErr3xx(param, i);
  				stop("Can not open file with data input matrix. File or path does not exit.");
  				break;
  			case 301:
          freeMemErr3xx(param, i);
  				stop("Karyotype is allready exists.");
  				break;
  			case 302:
  				freeMemErr3xx(param, i);
          stop("Bad definition of karyotype!");
  				break;
  			case 303:
  				freeMemErr3xx(param, i);
          stop("Alias is not unique.");
  				break;
  			case 304:
  				freeMemErr3xx(param, i);
          stop("Bad count of lexems in line, who defined CHR.");
  				break;
  			case 305:
  				freeMemErr3xx(param, i);
          stop("Chromosome element already exists.");
  				break;
  			case 306:
  				freeMemErr3xx(param, i);
          stop("Chromosome does not exist.");
  				break;
  			case 307:
  				freeMemErr3xx(param, i);
          stop("Bad count of lexems in line, who defined BLOCK.");
  				break;
  			case 308:
  				freeMemErr3xx(param, i);
          stop("Chromosome does not exist.");
  				break;
  			case 309:
  				freeMemErr3xx(param, i);
          stop("Bad count of lexems in line, who defined CENTROMERE.");
  				break;
  			case 310:
  				freeMemErr3xx(param, i);
          stop("Bad count of lexems in line, who defined BLOCK MAPPING.");
  				break;
  			case 311:
  				freeMemErr3xx(param, i);
          stop("Incompatibile lenght of chromosome.");
  				break;
  
  			// drawing and saveing images
  			case 400:
				cout << param->getOutputPath() << endl;
				freeMemErr3xx(param, i);
				stop("Output path does not exist.");
  				break;
  
  			default:
  				break;
  		}
  		
  		return -1;
  	}
  
  
  	return 0;
}


