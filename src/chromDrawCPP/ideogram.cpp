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
* Method for load input matrix with definition of karyotypes in defined data format.
* @param path Path to input file.
* @param format Type of input data format.
* @return If everything succes retur 0.
*/
int ideogram::loadMatrix(string path, string format)
{
	int retVal;

	if(format.compare(DEFAULTDATAFORMAT) == 0)
	{
		retVal = loadChromDrawDataMatrix(path);
	}
	else if (format.compare(BEDDATAFORMAT) == 0)
	{
		retVal = loadBedDataMatrix(path);
	}
	if(retVal != 0)
	{
		return retVal;
	}
	else
	{
		this->dataCorrection();
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

/**
* Add missing information into the karyotypes.
*/
void ideogram::dataCorrection()
{
	for(list<karyotype*>::iterator it = ideogram_p.begin(); it != ideogram_p.end(); it++)
	{
		(*it)->addMissingBlocks();
	}
}


////////////////////////// PRIVATE /////////////////////////////////

/**
* Method for load input matrix with definition of karyotypes in the chromDraw data format.
* @param path Path to input file.
* @return If everything succes retur 0.
*/
int ideogram::loadChromDrawDataMatrix(string path)
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
* Method for load input matrix with definition of karyotype in the BED data format.
* @param path Path to input file.
* @return If everything succes retur 0.
*/
int ideogram::loadBedDataMatrix(string path)
{
	ifstream inputFile;

	// open input file
	inputFile.open(path.c_str());
	if(! inputFile.good())
	{
		throw(300);
		return -1;
	}

	karyotype *tmpKT = new karyotype();
	canvas *tmpCAN = new canvas();
	tmpKT->setName("BED_visualization");
	tmpKT->setAlias("bed1");
	tmpCAN->setAlias(tmpKT->getAlias());


	int blockAlias = 1;
	
	//converting variables
	stringstream convertToString;
	int value;

	bool chromosomeUninit = true;

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

		if(parsing::stringToUpper(lineLexemes.front()).compare(BROWSER) == 0)
		{
			// ignore line browser
		}else if(parsing::stringToUpper(lineLexemes.front()).compare(TRACK) == 0)
		{
			// ignore line track
		}
		else
		{
			// parsing data line in full track format of BED file.
			list<string>::iterator it = lineLexemes.begin();
			
			
			chromosome *chr;
		
			// chrom - The name of the chromosome
			if( !(tmpKT->isChromosomeExist(*it)))
			{
				chr = new chromosome();
				chr->setName(*it);
				chr->setAlias(*(it++));
				chromosomeUninit = true;
			}
			else
			{	// chromosome is exist
				chr = tmpKT->getChromosome(*(it++));
				chromosomeUninit = false;
			}
			//chromStart - The starting position of the feature in the chromosome or scaffold. The first base in a chromosome is numbered 0.
			(it++);	//ignore this value
			//chromEnd - The ending position of the feature in the chromosome or scaffold. The chromEnd base is not included in the display of the feature. For example, the first 100 bases of a chromosome are defined as chromStart=0, chromEnd=100, and span the bases numbered 0-99. 
			(it++); //ignore this value
			//name - Defines the name of the BED line. This label is displayed to the left of the BED line in the Genome Browser window when the track is open to full display mode or directly to the left of the item in pack mode.
			
			chBlock	*block = new chBlock();
	
	
			block->setName(*(it++));
			convertToString << blockAlias;
			block->setAlias(convertToString.str());
			blockAlias++;

			//score - A score between 0 and 1000.
			(it++); //ignore this value
			//strand - Defines the strand - either '+' or '-'.
			(it++); //ignore this value
			//thickStart - The starting position at which the feature is drawn thickly (for example, the start codon in gene displays). When there is no thick part, thickStart and thickEnd are usually set to the chromStart position.
			istringstream s0(*it++);
			s0 >> value;
			block->setBegin(value);
			if((chr->getBegin() > value) || chromosomeUninit)
			{
				chr->setBegin(value);
			}
			//thickEnd - The ending position at which the feature is drawn thickly (for example, the stop codon in gene displays).
			istringstream s1(*it++);
			s1 >> value;
			block->setEnd(value);
			if((chr->getEnd() < value) || chromosomeUninit)
			{
				chr->setEnd(value);
			}
			
			//itemRgb - An RGB value of the form R,G,B (e.g. 255,0,0).
			block->setColorName(*it);
			// find position of rgb delimiter
			unsigned first = ((string)(*it)).find(RGBDELIMITER);
			unsigned last = ((string)(*it)).find_last_of(RGBDELIMITER);
			istringstream sr(((string)(*it)).substr(0,first));
			istringstream sg(((string)(*it)).substr(first+((string)RGBDELIMITER).length(),last));
			istringstream sb(((string)(*it)).substr(last+((string)RGBDELIMITER).length(),((string)(*it)).length()));
			int r,g,b;
			sr >> r;
			sg >> g;
			sb >> b;
			//push color in to the pallete
			this->palette.pusColor(r,g,b,*it++);

			//add block in to the chromosome
			chr->pushElement(block);
			//add chromosome in to the karyotype
			if( !(tmpKT->isChromosomeExist(chr->getAlias())))
			{
				tmpKT->pushChromosome(chr);
			}

		}

	}
	
	this->pushKaryotype(tmpKT);
	this->pushCanvas(tmpCAN);

	return 0;
}

