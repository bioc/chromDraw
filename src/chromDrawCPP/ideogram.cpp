/*
* Name: ideogram.cpp
* Description: Definition of methods for class ideogram. Ideogram
*              is a main class for chromosom drawing.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/


#include "ideogram.h"


/**
* Constructor for class ideogram.
*/
ideogram::ideogram(void)
{
	cir_sheet = new canvas();
}

/**
* Destructor for class ideogram.
*/
ideogram::~ideogram(void)
{
	 delete(cir_sheet);
}

/**
* Method for draw all karyotepes to linear and circular pictures.
*/
void ideogram::draw(bool useScale)
{
// TODO efektivneji ziskavat hodnotu maximalni delky chromosomu pro jednotlive karyotypy, mozna ulozit pri nacitani dat. (privatni promenna)
	int maxLenght = 0;

	if(useScale)
	{
		for(list<karyotype*>::iterator itk = ideogram_p.begin(); itk != ideogram_p.end(); itk++)
		{
			if(maxLenght < (*itk)->getMaxChromosomeLenght())
			{
				maxLenght = (*itk)->getMaxChromosomeLenght();
			}
		}
	}

	for(list<karyotype*>::iterator it = ideogram_p.begin(); it != ideogram_p.end(); it++)
	{
		// linear draw
		if(useScale)
		{
			getCanvas((*it)->getAlias())->lin_init(maxLenght, (*it)->getChromosomeCount());
		}
		(*it)->draw(getCanvas((*it)->getAlias()), palette, true);

		// circular draw
		(*it)->draw(cir_sheet, palette, false);
	}
}

/**
* Method for load input matrix with definition of karyotypes.
* @param path Path to input file.
* @return If everything succes retur 0.
*/
int ideogram::loadMatrix(string path)
{
	ifstream inputFile;

	// open input file
	inputFile.open(path.c_str());
	if(! inputFile.good())
	{
		throw(300);
		return -1;
	}

	while(! inputFile.eof())
	{
		list<string> lineLexemes;
		// read line and cut it to lexems
		int state = parsing::getLineLexemes(&lineLexemes, &inputFile);
		if(state == 1)
		{
			break;
		}
		else if( 0 != state)
		{
			inputFile.close();
			return -1;
		}

		if(parsing::stringToUpper(lineLexemes.front()).compare(KARYOTYPE) == 0)
		{
			if(parsing::stringToUpper(lineLexemes.back()).compare(BEGIN) == 0)
			{
			
				// load karyotype information
				if(lineLexemes.size() == KARYOTYPEITEMSCOUNT)
				{
					karyotype *tmpKT = new karyotype();
					canvas *tmpCAN = new canvas();

					list<string>::iterator it = lineLexemes.begin();
					it++;

					tmpKT->setName(*(it++));
					tmpKT->setAlias(*(it++));
					tmpCAN->setAlias(tmpKT->getAlias());

					if(getKaryotype(tmpKT->getAlias()) == NULL)
					{
						try
						{
							if(0 != tmpKT->loadMatrix(&inputFile))
							{
								inputFile.close();
								delete tmpKT;
								delete tmpCAN;
								return -1;
							}
						}
						catch (int value)
						{
							inputFile.close();
							delete tmpKT;
							delete tmpCAN;
							throw(value);
						}

						this->pushKaryotype(tmpKT);
						this->pushCanvas(tmpCAN);
					}
					else
					{
						cout << "Karyotype with alias: " << tmpKT->getAlias() << " is allready exists." << endl;
						delete tmpKT;
						delete tmpCAN;
						throw(301);
						return -1;
					}

				}
				else
				{
					throw(302);
					return -1;
				}

			}
		}
		else if(parsing::stringToUpper(lineLexemes.back()).compare(END) == 0)
		{
		}
		else if(parsing::stringToUpper(lineLexemes.front())[0] == COMMENT)
		{
		}
		else
		{
			throw(302);
			return -1;
		}


	}

	return 0;
}


/**
* Insert karyotype to the list including all karyotypes.
* @param k Inserted karyotype.
*/
void ideogram::pushKaryotype(karyotype *k)
{
	ideogram_p.push_back(k);
}


/**
* Remove karyotype from the list. Selection karyotype is by alias.
* @param sAlias Alias of removed karyotype.
*/
void ideogram::popKaryotype(string sAlias)
{
	ideogram_p.remove(getKaryotype(sAlias));
}

/** 
* Finding karyotype by alias string.
* @param sAlias Alias of searching karyotype.
* @return Pointer on finded karyotype. If karyotype does not exit return NULL.
*/
karyotype* ideogram::getKaryotype(string sAlias)
{
	for(list<karyotype*>::iterator it = ideogram_p.begin(); it != ideogram_p.end(); it++)
	{
		karyotype *c = *it;

		if(c->getAlias().compare(sAlias) == 0)
		{
			return c;
		}
	}
	return NULL;
}

/**
* Insert canvas to list with linear canvases.
* @param c Canvas for inserting.
*/
void ideogram::pushCanvas(canvas *c)
{
	lin_sheets.push_back(c);
}

/**
* Remove canvas from list with linear canvases.
* @param sAlias Remove canvas from list - alias of canvas.
*/
void ideogram::popCanvas(string sAlias)
{
	lin_sheets.remove(getCanvas(sAlias));
}


/**
* Get pointer on canvas. Finding by his alias.
* @param sAlias Alias of searching canvas.
* @return Pointer on canvas. If canvas does not exit then return NULL.
*/
canvas* ideogram::getCanvas(string sAlias)
{
	for(list<canvas*>::iterator it = lin_sheets.begin(); it != lin_sheets.end(); it++)
	{
		if((*it)->getAlias().compare(sAlias) == 0)
		{
			return (*it);
		}
	}
	return NULL;
}

/**
* Save all images.
* @param path Path for saveing images.
*/
void ideogram::saveImages(string path)
{
  /*
	int Result = 0;
	// Check if the path exist.
	if(path.length() != 0)
	{
	  #ifdef _WIN32 || _WIN64
	      struct _stat buf; 
	      Result = _stat( path.c_str(), &buf );
	  #else
	      struct stat buf;
	      Result = stat( path.c_str(), &buf );
	  #endif
	}
  
	if(Result != 0)
	{
	  //output path does not exist.
	  throw(400);
	}
	*/
	for(list<canvas*>::iterator it = lin_sheets.begin(); it != lin_sheets.end(); it++)
	{
		(*it)->save(path + (*it)->getAlias()+LINEARIMGNAME);
	}
	cir_sheet->save(path + CIRCULARIMGNAME);
}

/**
* Loading color palete from file.
* @param path Path to file with colors.
* @return State of loading. If all succe then return 0.
*/
int ideogram::loadColorPalette(string path)
{
	return palette.loadMatrix(path);
}

