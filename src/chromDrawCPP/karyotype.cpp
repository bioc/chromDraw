/*
* Name: karyotype.cpp
* Description: Definition methods for work with karyotype
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/


#include "karyotype.h"

/**
* Constructor for karyotype.
*/
karyotype::karyotype(void)
{
}

/**
* Destructor for karyotype.
*/
karyotype::~karyotype(void)
{
	/*
	for(list<chromosome*>::iterator it=katype.begin(); it != katype.end(); it++)
	{
		delete *it;
		//katype.remove(*it);
	}
	*/
}


/**
* Method for set name of karyotype.
* @param name Name of karyotype.
*/
void karyotype::setName(string name)
{
	this->name = name;
}

/**
* Method for get name of actual karyotype.
* @return Name of karyotype.
*/
string karyotype::getName()
{
	return name;
}

/**
* Method for set alias string.
* @param sAlias Alias of karyotype.
*/
void karyotype::setAlias(string sAlias)
{
	alias = sAlias;
}

/**
* Method for get alias string.
* @return Alias of karyotype.
*/
string karyotype::getAlias()
{
	return alias;
}

/**
* Insert chromosome to the actual karyotype.
* @param c Inserted chromosome.
*/
void karyotype::pushChromosome(chromosome *c)
{
	katype.push_back(c);
}

/**
* Remove chromosome from the actual karyotype by his alias.
* @param sAlias Alias of removed chromosome.
*/
void karyotype::popChromosome(string sAlias)
{
	katype.remove(getChromosome(sAlias));	
}

/**
* Get chromosome by his alias.
* @param sAlias Alias for searching chromosome.
* @return Pointer to chromosome, if chromosome does not exist return NULL.
*/
chromosome* karyotype::getChromosome(string sAlias)
{
	for(list<chromosome*>::iterator it = katype.begin(); it != katype.end(); it++)
	{
		chromosome *c = *it;

		if(c->getAlias().compare(sAlias) == 0)
		{
			return c;
		}
	}
	return NULL;
}

/**
* Get chromosome rank by his alias.
* @param sAlias Alias for searching chromosome.
* @return Chromosome rank in curent karyotype if chromosome does not exist return -1.
*/
int karyotype::getChromosomeRank(string sAlias)
{
	int rank = 0;
	for(list<chromosome*>::iterator it = katype.begin(); it != katype.end(); it++)
	{
		if((*it)->getAlias().compare(sAlias) == 0)
		{
			return rank;
		}
		else
		{
			rank++;
		}
	}
	return -1;
}

/** Check if the chromosome exist by alias.
* @param sAlias Alias for searching chromosome.
* @return If chromosome exist return TRUE else return FALSE.
*/
bool karyotype::isChromosomeExist(string sAlias)
{
	if(getChromosome(sAlias) == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
* Load karyotype information from file.
* @param inputFile Opened input file.
* @return If all load succes return 0 else return -1.
*/
int karyotype::loadMatrix(ifstream *inputFile)
{
	//int numberOfChromosome = 0;

	while(! inputFile->eof())
	{
		list<string> lineLexemes;


		int state = parsing::getLineLexemes(&lineLexemes, inputFile);
		if(state == 1)
		{
			break;
		}
		else if( 0 != state)
		{
			return -1;
		}
		
		
		// chromosome information
		if(parsing::stringToUpper(lineLexemes.front()).compare(CHR) == 0)
		{
			
			if(lineLexemes.size() == CHRITEMSCOUNT)
			{
				chromosome *chr = new chromosome();
				list<string>::iterator it = lineLexemes.begin();
				it++;

				chr->setName(*(it++));
				if(! isChromosomeExist(*it))
				{
					chr->setAlias(*(it++));
				}
				else
				{
					cout << "Alias: " << *it << " is not unique." << endl;
					delete chr;
					throw(303);
					return -1;
				}
				
				istringstream s0(*it++);
				int value;
				s0 >> value;
				chr->setBegin(value);

				istringstream s1(*it);
				s1 >> value;
				chr->setEnd(value);
				
				
				// push chromosome to karyotyp
				pushChromosome(chr);
			}
			else
			{
				for(list<string>::iterator it = lineLexemes.begin(); it != lineLexemes.end(); it++)
				{
				  cout << *it << " ";
				}
				cout << endl;
				throw(304);
				return -1;
			}
			
		}


		// block information
		else if(parsing::stringToUpper(lineLexemes.front()).compare(BLOCK) == 0)
		{
			
			if((lineLexemes.size() == BLOCKITEMSCOUNT) || (lineLexemes.size() == BLOCKITEMSCOUNT+1))
			{
				list<string>::iterator it = lineLexemes.begin();
				it++;
				chBlock	*block = new chBlock();
				string nameOfChromosome;

				block->setName(*it++);
				block->setAlias(*it++);
				
				nameOfChromosome = *it++;
				
				istringstream s0(*it++);
				int value;
				s0 >> value;
				block->setBegin(value);

				istringstream s1(*it++);
				s1 >> value;
				block->setEnd(value);


				if(lineLexemes.size() == BLOCKITEMSCOUNT+1)
				{
					block->setColorName(*it);
				}
				else
				{
					block->setColorName(DEFAULTCOLORS[getChromosomeRank(nameOfChromosome) % NUMOFDEFAULTCOLORS]);					
				}

				chromosome *chr = getChromosome(nameOfChromosome);

				if(chr != NULL) 
				{
					if(! chr->isElementexist(block->getAlias()))
					{
						chr->pushElement(block);
					}
					else
					{
						cout << "Chromosome element with internal alias: "  << block->getAlias() << " is allready exists." << endl;
						delete block;
						throw(305);
						return -1;
					}
				}
				else
				{
					cout << "Chromosome with internal alias: "  << nameOfChromosome << " does not exist." << endl;
					delete block;
					throw(306);
					return -1;
				}

			}
			else
			{
				for(list<string>::iterator it = lineLexemes.begin(); it != lineLexemes.end(); it++)
				{
				  cout << *it << " ";
				}
				cout << endl;
				throw(307);
				return -1;
			}
			
		}


		// centromere
		else if(parsing::stringToUpper(lineLexemes.front()).compare(CENTROMERE) == 0)
		{
			
			if(lineLexemes.size() == CENTROMEREITEMSCOUNT)
			{
				list<string>::iterator it = lineLexemes.begin();
				chCentromere *centromere = new chCentromere();
				it++;	

			
				chromosome *chr = getChromosome(*it);
				if(chr != NULL)
				{
					chr->pushElement(centromere);
				}
				else
				{
					cout << "Chromosome with internal alias: "  << *it << " does not exist." << endl;
					delete centromere;
					throw(308);
					return -1;
				}

			}
			else
			{
				for(list<string>::iterator it = lineLexemes.begin(); it != lineLexemes.end(); it++)
				{
				  cout << *it << " ";
				}
				cout << endl;
				throw(309);
				return -1;
			}
		}

//TODO predat o tridu vyse -> do ideogramu
		// mapping blocks
		else if(parsing::stringToUpper(lineLexemes.front()).compare(MAP) == 0)
		{
			
			if(lineLexemes.size() == MAPITEMSCOUNT)
			{
				//list<string>::iterator it = lineLexemes.begin()++;
			}
			else
			{
				throw(310);
				return -1;
			}
		}


		// comment
		else if(parsing::stringToUpper(lineLexemes.front())[0] == COMMENT)
		{
		}
		else
		{
			// check chromosomes
			for(list<chromosome*>::iterator it=katype.begin(); it != katype.end(); it++)
			{
				if((*it)->checkChromosomeData() != 0)
				{
					// incompatibile count of bases
					cout << "Incompatibile lenght of chromosome  " << (*it)->getName() << endl;
					throw(311);
					return -1;
				}
			}

			break;
		}

		
	}
	
	// sort blocks in this karyotype
	sortBlocks();

	return 0;
}

/** 
* Method for draw curent karyotype.
* @param sheet Input sheet for drawing.
* @param palette Color palete for drawing.
* @param liner Type of drawing, if parameter set as TRUE this mean linear drawing else circular drawing.
*/
void karyotype::draw(canvas *sheet, colorPalette palette, bool linear)
{
	int maxLenght = 0;
	unsigned long int totalLenght = 0;
	int centromereCount = 0;

	// get karyotype lenght and other atributes
	for(list<chromosome*>::iterator it=katype.begin(); it != katype.end(); it++)
	{
		if(maxLenght < (*it)->getChromosomLenght())
		{
			maxLenght = (*it)->getChromosomLenght();
		}
		totalLenght += (*it)->getChromosomLenght();
		centromereCount += (*it)->getCentromereCount();
	}

	if(linear)
	{
		if(!sheet->lin_isInit())
		{
			sheet->lin_init(maxLenght, katype.size());
		}
	}
	else
	{
		if(sheet->cir_isInit())
		{
			sheet->cir_nextCircle(totalLenght, katype.size(), centromereCount, getMaxStringLenghtChrName());
		}
		else
		{
			sheet->cir_init(totalLenght, katype.size(), centromereCount);
		}

	}

	for(list<chromosome*>::iterator it=katype.begin(); it != katype.end(); it++)
	{
		if(linear)
		{
			(*it)->draw(sheet, palette, true);
			sheet->lin_nextChromosom();
		}
		else
		{
			(*it)->draw(sheet, palette, false);
		}
	}

}

/**
* Get maximul string lenght for drawing of all blocks.
* @return Maximum string lenght for drawing.
*/
int karyotype::getMaxStringLenghtBlock()
{
	int retVal = 0;
	
	for(list<chromosome*>::iterator it = katype.begin(); it != katype.end(); it++)
	{
		if(retVal < (*it)->getMaxStringLenghtBlock())
		{
			retVal = (*it)->getMaxStringLenghtBlock();
		}
	}

	return retVal;
}

/**
* Get maximul string lenght in px for drawing of all chromosomes.
* @return Maximum string lenght in px for drawing.
*/
float karyotype::getMaxStringLenghtChrName()
{
	float retVal = 0;

	for(list<chromosome*>::iterator it = katype.begin(); it != katype.end(); it++)
	{
		float pomLen = charsLenghts::getStringPxLengh((*it)->getName());
		if(retVal < pomLen )
		{
			retVal = pomLen;
		}
	}

	return retVal;
}

/**
* Get lenght of longest chromosome in karyotype
* @return Lenght of longest chromosome
*/
int karyotype::getMaxChromosomeLenght()
{
	int maxLenght = 0;

	for(list<chromosome*>::iterator itch=katype.begin(); itch != katype.end(); itch++)
	{
		if(maxLenght < (*itch)->getChromosomLenght())
		{
			maxLenght = (*itch)->getChromosomLenght();
		}
	}

	return maxLenght;
}


/**
* Get count of chromosomes in karyotype
* @return Count of chromosomes
*/
int karyotype::getChromosomeCount()
{
	return katype.size();
}

//-----------------PRIVATE-------------------
/**
* Methode for sort blocks in all chromosomes.
*/
void karyotype::sortBlocks()
{
	for(list<chromosome*>::iterator it = katype.begin(); it != katype.end(); it++)
	{
		//sort chromosome elements
		(*it)->sortElements();
	}
}

