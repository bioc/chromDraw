/*
* Name: getOpts.h
* Description: Declaration methods for class getOpts.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef GETOPTS_H_
#define GETOPTS_H_

#include <iostream>
#include <cstdio>
#include <string.h>


using namespace std;

class getOpts 
{
	public:
		getOpts();
		virtual ~getOpts();

	private:
		int argcurent;	//number of current argument
		int optID;	// id of option from vector with arguments

	public:
		char getOptions(int argc, char** argv, char* optv, char** optvExpanded); // methode for arguments parssing
		int getOptID();	// get index on curent value of argument
};

#endif /* GETOPTS_H_ */
