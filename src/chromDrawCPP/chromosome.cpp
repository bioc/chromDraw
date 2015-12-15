/*
* Name: chromosome.cpp
* Description: Definition methods for chromosome
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#include "chromosome.h"


/**
* Constructor for class chromosome.
*/
chromosome::chromosome(void)
{
}

/**
* Destructor for class chromosome.
*/
chromosome::~chromosome(void)
{
	/*
	for(int i=chr.size(); i > 0; i--)
	{
		delete chr.back();
		chr.pop_back();
	}
	chr.clear();
	*/
}

/**
* Set name of chromosome.
* @param s Name of chromosome.
*/
void chromosome::setName(string s)
{
	if(s.compare(EMPTYSTRING) == 0)
	{
		name = "";
	}
	else
	{
		name = s;
	}
}

/** 
* Get name of chromosome.
* @return String value with name of chromosome.
*/
string chromosome::getName()
{
	return name;
}

/**
* Set alias name of chromosome.
* @param s Unicate alias name of chromosome.
*/
void chromosome::setAlias(string s)
{
	alias = s;
}

/**
* Get alias of chromosome.
* @return String value with alias of chromosme.
*/
string chromosome::getAlias()
{
	return alias;
}

/** 
* Set start position of chromosome.
* @param i Start of chromosome.
*/
void chromosome::setBegin(int i)
{
	start = i;
}

/**
* Get start position of chromosome.
* @return Integer value of start postion.
*/
int chromosome::getBegin()
{
	return start;
}

/**
* Set stop position of chromosme.
* @param i Stop position of chromosome.
*/
void chromosome::setEnd(int i)
{
	stop = i;
}

/**
* Get stop position of chromosome.
* @return Integer value of end chromosme position.
*/
int chromosome::getEnd()
{
	return stop;
}

/**
* Methode for linear or circular type of chromosme.
* @param sheet Output sheet for drawing.
* @param palette Actual color palette for drawing.
* @param liner True for linear drawing and false for circular drawing.
*/
void chromosome::draw(canvas *sheet, colorPalette palette, bool linear)
{
	
	// draw chromosom name - linear
	if(linear)
	{
		sheet->lin_drawChromosomeName(getName());
	}

	// draw north telomere
	if(getBegin() == 0)
	{
		if(linear)
		{
			sheet->lin_drawTelomere(true);
		}
		else
		{
			sheet->cir_drawTelomere(true);
		}
	}
	else
	{
		if(!linear)
		{
			sheet->cir_skipTelomere(true);
		}
	}

	// draw blocks
	for(list<chromosomeElement*>::iterator it=chr.begin(); it != chr.end(); it++)
	{
		if(linear)
		{
			(*it)->drawLinear(sheet, palette, (*it)->getName());
		}
		else
		{
			(*it)->drawCircular(sheet, palette, (*it)->getName());
		}
	}
	
	// draw south telomere
	if(getBegin() == 0)
	{
		if(linear)
		{	
			sheet->lin_drawTelomere(false);
		}
		else
		{
			sheet->cir_drawTelomere(false);
		}
	}
	else
	{
		if(!linear)
		{
			sheet->cir_skipTelomere(false);
		}
	}

	
	// draw chromosom name - circular
	if(!linear)
	{
		sheet->cir_drawChromosomeName(getName());
	}

	// draw marks
	for(list<chromosomeSign*>::iterator it=signs.begin(); it != signs.end(); it++)
	{
		if(linear)
		{	
			sheet->lin_initForMarks();
		}
		if(linear)
		{
			(*it)->drawLinear(sheet, palette, (*it)->getName());
		}
		else
		{
			sheet->cir_initForMarks();
			(*it)->drawCircular(sheet, palette, (*it)->getName());
			sheet->cir_finisDrawMarksForChromosome();
		}
	}
	
}

/**
* Push chromosome element to the list of chromosome elements.
* @param element Inserted chromosome element.
*/
void chromosome::pushElement(chromosomeElement *element)
{
	// check correct values
	if((element->getBegin() >= start) && (element->getEnd() <= stop) && (element->getBegin() <= element->getEnd()))
	{
		chr.push_back(element);
	}
}

/** 
* Get chromosome element by alias.
* @param sAlias Alias of chromosome.
* @return Chromosome element if does not exist return NULL.
*/
chromosomeElement* chromosome::getElement(string sAlias)
{
	
	for(list<chromosomeElement*>::iterator it = chr.begin(); it != chr.end(); it++)
	{
		chromosomeElement *c = *it;

		if(c->getAlias().compare(sAlias) == 0)
		{
			return c;
		}
	}
	return NULL;
}


/** 
* Delete element form list of chromosome elements.
* @param sAlias Alias of deleted chromosome element.
*/
void chromosome::popElement(string sAlias)
{
	chr.remove(getElement(sAlias));
}


/**
* Check if element with input alias name is exist.
* @param sAlias Alias name of checking element.
* @return True if element is exist and false if element is not exist.
*/
bool chromosome::isElementexist(string sAlias)
{
	if(getElement(sAlias) == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

/**
* Get lenght of curent chromosome.
* @return  Integer value of lenght chromosome.
*/
int chromosome::getChromosomLenght()
{
	int lenght;
	
	lenght = stop - start;
	if(lenght < 0)
		return 0;

	return lenght;
}


/**
* Get count of centromeres in actual chromosome.
* @return Count of centromeres.
*/
int chromosome::getCentromereCount()
{
	int count = 0;

	for(list<chromosomeElement*>::iterator it = chr.begin(); it != chr.end(); it++)
	{
		if((*it)->getElementType() == chCentromere::Centromere)
		{
			count++;
		}
	}

	return count;
}

/**
* Check data if are they correct.
* @return Return 0 if everything is OK.
*/
int chromosome::checkChromosomeData()
{
	int len = 0;
	bool blockExist = false;

	for(list<chromosomeElement*>::iterator it=chr.begin(); it != chr.end(); it++)
	{
		if(!blockExist)
		{
			if((*it)->getElementType() == chromosomeElement::Block)
			{
				blockExist = true;
			}
		}
		if((*it)->getElementType() == chromosomeElement::Block)
		{	// skipping centromere
			len += (*it)->getEnd() - (*it)->getBegin();
		}
	}
	if(((getEnd() - getBegin()) != len) && (!chr.empty()))
	{
		return 1;
	}

	// if no block defined add one block for draw chromosome with out any others blocks.
	if(!blockExist)
	{
		chBlock *block = new	chBlock();
		block->setBegin(getBegin());
		block->setEnd(getEnd());
		pushElement(block);
	}
	return 0;
}

/**
* Add missing block to complete whole chromosome.
*/
void chromosome::addMissingBlocks()
{
	this->sortElements();
	list<chromosomeElement*> tmpList;

	int curentPos = this->getBegin();
	for(list<chromosomeElement*>::iterator it=chr.begin(); it != chr.end(); it++)
	{
		if((*it)->getElementType() == chromosomeElement::Block)
		{
			if((*it)->getBegin() == curentPos)
			{
				curentPos = (*it)->getEnd();
			}
			else if((*it)->getBegin() > curentPos)
			{
				// insert blank block
				chBlock *block = new chBlock();
				block->setBegin(curentPos);
				block->setEnd((*it)->getBegin());
				tmpList.push_back(block);
				curentPos=(*it)->getEnd();
			}
		}
	}
	if(curentPos < this->getEnd())
	{
		// insert blank block
		chBlock *block = new chBlock();
		block->setBegin(curentPos);
		block->setEnd(this->getEnd());
		tmpList.push_back(block);
	}

	// copy new items
	for(list<chromosomeElement*>::iterator it=tmpList.begin(); it != tmpList.end(); it++)
	{
		pushElement(*it);
	}
	this->sortElements();
}

/**
* Get maximum lenght of chromosome block name.
* @return Integer value of lenght block string name.
*/
int chromosome::getMaxStringLenghtBlock()
{
	unsigned int retVal = 0;

	for(list<chromosomeElement*>::iterator it = chr.begin(); it != chr.end(); it++)
	{
		if(retVal < (*it)->getName().length())
		{
			retVal = (*it)->getName().length();
		}
	}

	return retVal;
}


/**
* Sort all elements in this chromosome.
*/
void chromosome::sortElements()
{
	list<chromosomeElement*> tmp;

	int size = chr.size();

	for(int i=1; i <= size; i++)
	{
		chBlock *lastBlock = NULL;
		chCentromere *lastCentromere = NULL;
		for(list<chromosomeElement*>::iterator it=chr.begin(); it != chr.end(); it++)
		{
			if((*it)->getElementType() == chromosomeElement::Block)
			{
				if(lastBlock == NULL)
				{
					lastBlock = (chBlock*)(*it);
					lastCentromere = NULL;
					it++;
					if(it != chr.end())
					{
						if((*it)->getElementType() == chromosomeElement::Centromere)
						{	
							lastCentromere = (chCentromere*)(*it); // jedna se o centrumeru nemusim se vracet
						} 
						else
						{
							it--;  // nejedna se o centromeru musim se vratit 
						}
					}
					else
					{
						it--; // jsem na konci seznamu musim se vratit 
					}
				}
				else
				{
					if(lastBlock->getEnd() > (*it)->getBegin())
					{
						lastBlock = (chBlock*)(*it);
						lastCentromere = NULL;
						it++;
						if(it != chr.end())
						{
							if((*it)->getElementType() == chromosomeElement::Centromere)
							{	
								lastCentromere = (chCentromere*)(*it); // jedna se o centrumeru nemusim se vracet
							} 
							else
							{
								it--;  // nejedna se o centromeru musim se vratit 
							}
						}
						else
						{
							it--; // jsem na konci seznamu musim se vratit 
						}
					}
				}
			}
			else
			{
				// v pripade ze je centromera prvni 
				if(lastBlock == NULL)
				{
					lastCentromere = (chCentromere*)(*it);
					size++; // bude vlozena pouze centromera a ne i blok - korekce size
					break;
				}
			}

		}
		if(lastBlock != NULL)
		{
			chr.remove(lastBlock);
			tmp.push_back(lastBlock);
		}
		if(lastCentromere != NULL)
		{
			chr.remove(lastCentromere);
			tmp.push_back(lastCentromere);
			size--; // zpetna korekce poctu prvku v chromosomu
		}

	}

	chr.swap(tmp);
}

/**
* Get lenght of north arm since centromere.
* @return Lenght of arm.
*/
int chromosome::getNorthArmLenght()
{
	int len=0;
	for(list<chromosomeElement*>::iterator it=chr.begin(); it != chr.end(); it++)
	{
		if((*it)->getElementType() == chromosomeElement::Centromere)
		{
			return len;
		}
		else
		{
			len += abs((*it)->getEnd() - (*it)->getBegin());
		}
	}
	return len;
}

/**
* Get lenght of south arm since centromere.
* @return Lenght of arm.
*/
int chromosome::getSouthArmLenght()
{
	int len=0;
	bool findCen=false; // true if centromere was crossed
	for(list<chromosomeElement*>::iterator it=chr.begin(); it != chr.end(); it++)
	{
		if((*it)->getElementType() == chromosomeElement::Centromere)
		{
			findCen = true;
		}
		else
		{
			if(findCen)
			{
				len += abs((*it)->getEnd() - (*it)->getBegin());
			}
		}
	}
	return len;
}

/**
* Methode set position of centromere into the marks in centromere.
* Methode set location into the marks.
*/
void chromosome::addMarksInformation()
{
	for(list<chromosomeSign*>::iterator it=signs.begin(); it != signs.end(); it++)
	{
		if((*it)->getSignLocation() == canvas::LCentromere)
		{// mark in centromere
			(*it)->setBegin(getNorthArmLenght());
		}
		else if((*it)->getBegin() <= getNorthArmLenght())
		{
			(*it)->setSignLocation(canvas::LNorthArm);
		}
		else if(((*it)->getBegin() > getNorthArmLenght()) && ((*it)->getBegin() <= getChromosomLenght()))
		{
			(*it)->setSignLocation(canvas::LSouthArm);
		}
	}
}


///////////////////// MARKS ////////////////////////////////

/**
* Push chromosome sign to the list of chromosome signs.
* @param sign Inserted chromosome sign.
*/
void chromosome::pushSign(chromosomeSign *sign)
{
	// check correct values
	if((sign->getBegin() >= start) && (sign->getEnd() <= stop) && (sign->getBegin() <= sign->getEnd()))
	{
		signs.push_back(sign);
	}
}

/** 
* Get chromosome sign by alias.
* @param sAlias Alias of sign.
* @return Chromosome sign if does not exist return NULL.
*/
chromosomeSign* chromosome::getSign(string sAlias)
{
	for(list<chromosomeSign*>::iterator it = signs.begin(); it != signs.end(); it++)
	{
		chromosomeSign *c = *it;

		if(c->getAlias().compare(sAlias) == 0)
		{
			return c;
		}
	}
	return NULL;
}


/** 
* Delete sign form list of chromosome signs.
* @param sAlias Alias of deleted chromosome sign.
*/
void chromosome::popSign(string sAlias)
{
	signs.remove(getSign(sAlias));
}
	
/**
* Check if sign with input alias name is exist.
* @param sAlias Alias name of checking sign.
* @return True if the sign is exist and false if the sign is not exist.
*/
bool chromosome::isSignExist(string sAlias)
{
	if(getElement(sAlias) == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}


