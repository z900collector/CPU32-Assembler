/**
 * Create a new instance of a HALT instruction
 * set parametres and return it.
 *
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>


#include "HALTInst.h"
#include "Instruction.h"
#include "InstSet.h"
#include "Logger.h"


HALTInst::HALTInst()
{
	this->pLog = Logger::getInstance();
	this->pLabel = nullptr;
}

Instruction * HALTInst::parse(std::vector<std::string> words)
{
	this->pLog->LogFunction("parse()");
	if(words[0]=="HALT")
	{
		this->pLog->LogFunction("parse()");
		Instruction *pInst = new HALTInst();
		pInst->setWord(HALT);
		pInst->setName("HALT");
		pInst->setLength(1);
		return pInst;
	}
	else
		return nullptr;
}
/* End of file */
