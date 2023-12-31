/*
* Name: parameters.cpp
* Description: Definition function for loading parameters.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/


#include "parameters.h"


/**
* Constructor for class parameters.
*/
parameters::parameters(void)
{	
	outputPath = "";
	colourPath = "./inst/extdata/default_colors.txt";
	inputMatrixPath = "";
	format = DEFAULTDATAFORMAT;
	useScale = false;
}

/**
* Destructor for class parameters.
*/
parameters::~parameters(void)
{
}

/**
* Loading arguments.
* @param argc Arguments count.
* @param argv Vectors with arguments.
* @return Return 0 load was succesful or 1 load with errors.
*/
int parameters::loadArguments(int argc, char* argv[])
{
	char op_char;
	char params[10] = "hocdsf"; // parameters short cuts
	// expande parametres
	char *paramsExpanded[10] = {"--help",
								"--outputpath",
								"--colorinputpath",
								"--datainputpath",
								"--scale",
								"--format"};
	getOpts* opts = new getOpts();
 
  

	while((op_char = opts->getOptions(argc,argv, params, paramsExpanded)) != EOF)
	{

		switch (op_char)
		{
			case 'h':
					this->help();
					return 1;
				break;
			case 'o':
					{
					  int Result = 0;
					  if(((string)argv[opts->getOptID()]).length() != 0)
					  {
						#ifdef _WIN32 || _WIN64
        					  struct _stat buf; 
        					  Result = _stat( ((string)argv[opts->getOptID()]).c_str(), &buf);
        				  #else
        					  struct stat buf;
        					  Result = stat(((string)argv[opts->getOptID()]).c_str(), &buf );
        				  #endif
        				}
  
        				if(Result != 0)
        				{
        				  //output path does not exist.
        				  throw(400);
        				}
								this->setOutputPath(argv[opts->getOptID()]);
					}
				break;
			case 'c':
					this->setColourPath(argv[opts->getOptID()]);
				break;
			case 'd':
					this->setInputMatrixPath(argv[opts->getOptID()]);
				break;
			case 's':
				this->setUseScale(true);
				break;
			case 'f':
				if(parsing::stringToUpper(((string)argv[opts->getOptID()])).compare(DEFAULTDATAFORMAT) == 0)
				{	
					this->setInputDataFormat(DEFAULTDATAFORMAT);
				}
				else if(parsing::stringToUpper(((string)argv[opts->getOptID()])).compare(BEDDATAFORMAT) == 0)
				{
					this->setInputDataFormat(BEDDATAFORMAT);
				}
				else
				{
					// unsupporte input data format.
					throw(100);
				}
				break;
			default:
					return 1;
				break;
		}
	}
	
	delete(opts);
	return 0;
}


/**
* Show help.
*/
void parameters::help()
{
	cout << "This program generate linear and circular chromosomes pictures." << endl << endl;
	cout << "OPTIONS:" << endl;
	cout << "-h , --help	Show help." << endl;
	cout << "-o , --outputpath	Path to output directory." << endl;
	cout << "-d , --datainputpath	Path to input file with chromosome matrix." << endl;
	cout << "-c	, --colorinputpathFile with path to color settings." << endl;
	cout << "-s , --scale Use same scale for linear visualization" << endl;
  cout << "-f , --format Type of input data format - bed or chromdraw. Default is chromdraw"  << endl;

}

/**
* Set path for results.
* @param path Path for saveing pictures.
*/
void parameters::setOutputPath(string path)
{

	if((path[path.length()-1] == '\\') || (path[path.length()-1] == '/'))
	{
		outputPath = path;
	}
	else
	{
#ifdef _WIN32 || _WIN64
		
			outputPath = path + "\\";

#else

			outputPath = path + "/";
      
#endif
	}


#ifdef _WIN32 || _WIN64
      ReplaceAll(outputPath, "/", "\\"); 
      
#else
      ReplaceAll( outputPath, "\\", "/"); 
#endif
	
}

/**
* Get string contain path for saveing pictures.
* @return String with path.
*/
string parameters::getOutputPath()
{
	return outputPath;
}

/**
* Set path to file who cotain color settings.
* @param path String with path.
*/
void parameters::setColourPath(string path)
{
	colourPath = path;
}

/**
* Get string containing path to color settings.
* @return String with path.
*/
string parameters::getColourPath()
{
	return colourPath;
}

/**
* Set path for chromosomes input matrix.
* @param path String with path.
*/
void parameters::setInputMatrixPath(string path)
{
	inputMatrixPath = path;
}

/**
* Get path with chromosomes matrix input.
* @return String with path.
*/
string parameters::getInputMatrixPath()
{
	return inputMatrixPath;
}
/**
* Set type of input data format.
* @param format Input data format.
*/
void parameters::setInputDataFormat(string format)
{
	
	this->format=format;
}

/**
* Get input data format.
* @return Input data format.
*/
string parameters::getInputDataFormat()
{
	return this->format;
}

/**
* Set use scale for linear visualization
* @param value True for use scale, False for do not use scale
*/
void parameters::setUseScale(bool value)
{
	useScale = value;
}

/**
* Get use scale for linear visualization
* @return True for use scale, False for do not use scale
*/
bool parameters::getUseScale()
{
	return useScale;
}