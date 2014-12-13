/*
* Name: getOpts.cpp
* Description: Definoton methods for class getOpts.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#include "getOpts.h"

/**
 * Constructor for class getOpts.
 */
getOpts::getOpts()
{
	argcurent = 1;
	optID = 0;
}

/**
 * Destructor for class getOpts.
 */
getOpts::~getOpts()
{
}

/**
 * Method for parsing input arguments. (Only one char lenght)
 * @param argc Count of input arguments.
 * @param argv Vector with input arguments strings.
 * @param optv Vector with arguments definitions.
 * @return Return actual argument, if there are no more arguments return end of file - EOF.
 */
char getOpts::getOptions(int argc, char** argv, char* optv)
{
	char retval = EOF; // value for return 
	int optcurent = 0; // curent index to optv vector

	// is ther any argumets for processing
	if( argc <= argcurent)
	{
		return EOF;
	}

	while(optv[optcurent] != '\0')
	{
		if((optv[optcurent] == argv[argcurent][1]) && (argv[argcurent][2] == '\0'))
		{
			// positive match argument with chars in operating vector - optv
			retval = argv[argcurent][1];
			if(argcurent < argc-1)
			{
				if(argv[argcurent+1][0] != '-')
				{
					// curent argument have some value
					optID = argcurent + 1;
					argcurent += 2;
				}
				else
				{
					// there is no value for curent argument
					argcurent++;
				}
			}
			else
			{
				argcurent++;
			}

			return retval;

		}
		else
		{
			optcurent++;
		}
	}

	return retval;

}

/** 
 * Method which returns index to argv vector of curent argument value.
 * @return Return index value.
 */
int getOpts::getOptID()
{
	return optID;
}
