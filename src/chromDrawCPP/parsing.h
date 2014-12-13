/*
* Name: parsing.h
* Description: Definition functions shared across all classes.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef PARSING_H_
#define PARSING_H_
//#pragma once

#include <string>
#include <list>
#include <fstream>

#define MAXLINELEN 256	// max lenght of line

using namespace std;

class parsing
{
	public:
	
	/**
	* Function get each of lexems from imput line. Separator is a white space.
	* @param lexems Output list with lexemes.
	* @param file	Input line with lexemes.
	* @return Return state of parsing, if is OK return 0.
	*/
	static int getLineLexemes(list<string> *lexems, ifstream *file)
	{
		char line[MAXLINELEN];
		string lexem;
		int pos = 0;

		do
		{
			if(!file->eof())
			{
				file->getline(line,MAXLINELEN);
				pos = 0;
				while((line[pos] != 0) && (pos < MAXLINELEN))
				{
					if(isspace(line[pos]))
					{
						pos++;
						while(isspace(line[pos]))
						{
							pos++;
						}
						if(lexem.length() != 0)
						{
							lexems->push_back(lexem);
						}
						lexem.clear();
					}
					else
					{
						lexem += line[pos];
						pos++;
					}
				}
			}
			if(lexem.length() != 0)
			{
				lexems->push_back(lexem);
			}	


			if((lexems->size() == 0) && (file->eof()))
			{
				return 1;
			}
		}
		while(lexems->size() == 0);
	
	

		return 0;
	}

	/**
	* Function for converting string to upper string.
	* @param s Input string to convert.
	* @return Output string with upper lethers.
	*/
	static string stringToUpper(string s)
	{
		string retS = "";

		for(unsigned int i=0; i < s.length(); i++)
		{
			retS += toupper(s[i]);
		}

		return retS;
	}
};

#endif	// PARSING_H_
