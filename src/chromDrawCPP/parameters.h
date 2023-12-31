/*
* Name: parameters.h
* Description: Declaration methods and argumets for loading and parsing parameters.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef PARAMETERS_H_
#define PARAMETERS_H_
//#pragma once
#include "getOpts.h"
#include "parsing.h"

#include <sys/types.h> // for stat().
#include <sys/stat.h> // for stat().

#include <string>
#include <cstdio>
#include <iostream>


#define DEFAULTDATAFORMAT "CHROMDRAW"	// default input data format
#define BEDDATAFORMAT	"BED"	// input data in the BED data format


using namespace std;

class parameters
{
public:
	parameters(void);
	~parameters(void);

private:
	string outputPath;	// path for saveing pictures
	string colourPath;	// path to file with color setting
	string inputMatrixPath;	//path to source file with matrix
	string format;	// format of input data file
	bool useScale; // use same scale for linar visualization

public:
	int loadArguments(int argc, char* argv[]);
	void help();
	void setOutputPath(string path);
	string getOutputPath();
	void setColourPath(string path);
	string getColourPath();
	void setInputMatrixPath(string path);
	string getInputMatrixPath();
	void setInputDataFormat(string format);
	string getInputDataFormat();
	void setUseScale(bool value);
	bool getUseScale();

};


static inline void ReplaceAll(std::string &str, const std::string& from, const std::string& to)
{
  size_t start_pos = 0;
  while((start_pos = str.find(from, start_pos)) != std::string::npos) 
  {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length(); 
  }

}



#endif // PARAMETERS_H_
