/**
 * Process RSP instruction in different formats and if OK
 * return an object representing this instruction.
 * Created 2025-08-18 

 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>


#include "RSPInst.h"
#include "Instruction.h"
#include "Utility.h"
#include "InstSet.h"
#include "Logger.h"



using namespace std;


RSPInst::RSPInst()
{
	this->pLog = Logger::getInstance();
	this->pLog->LogMsg("RSPInst::RSPInst()");
	this->pLabel = nullptr;
}


/**
 *------------------------------------------------------------
 *
 * Determine if this object can handle in instruction
 * If it does, return a newly created "Instruction" derived object
 * else return a nullptr.
 */
Instruction * RSPInst::parse(std::vector<std::string> words)
{
	this->pLog->LogFunction("RSPInst::parse()");
	
	if(words[0]=="RSP")
	{
		return this->Process_RSP_Instruction(words);
	}
	//
	// Put any versions of the OPCODE here 
	// i.e. LD, LDI, LDM, LDR - then call something to process them.
	//
	return nullptr;
}



/**
 *------------------------------------------------------------
 *
 * Parse the line and mask in the additional parameters
 * If there is source and destination registers then parse those
 * and biwise OR them into the basic OPCODE.
 *
 * Create an RSPInst object and return it back.
 */
Instruction *RSPInst::Process_RSP_Instruction(std::vector<std::string> words)
{
unsigned int iw = RSP;
unsigned int reg = 0;
std::stringstream ss;

	this->pLog->LogFunction("Process_RSP_Instruction()");

	RSPInst *pInst = new RSPInst();
	pInst->setWord( iw );
	ss<<"OP [" << std::hex << setw(4)<< std::setfill('0') << pInst->_opcode<< "]";
	this->pLog->LogMsg( ss.str() );
	pInst->setName("RSP");
	return pInst;
}
/* End of file */
