/**
 * Process RET instruction in different formats and if OK
 * return an object representing this instruction.
 * Created 2025-08-07 

 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>


#include "RETInst.h"
#include "Instruction.h"
#include "Utility.h"
#include "InstSet.h"
#include "Logger.h"



using namespace std;


RETInst::RETInst()
{
	this->pLog = Logger::getInstance();
	this->pLog->LogMsg("RETInst() Constructor");
	this->pLabel = nullptr;
}


Instruction * RETInst::parse(std::vector<std::string> words)
{
	this->pLog->LogFunction("RETInst::parse()");
	if(words[0]=="RET")
	{
		return this->Process_RET_Instruction(words);
	}
	return nullptr;
}



/**
 *------------------------------------------------------------
 *
 * Parse the line and mask in the additional parameters
 * If there is source and destination registers then parse those
 * and biwise OR them into the basic OPCODE.
 *
 * Create an RETInst object and return it back.
 */
Instruction *RETInst::Process_RET_Instruction(std::vector<std::string> words)
{

	this->pLog->LogFunction("Process_RET_Instruction()");

	RETInst *pInst = new RETInst();
	pInst->setName("RET");
	pInst->setWord(RET);
	pInst->setLength(1);
	return pInst;
}
/* End of file */
