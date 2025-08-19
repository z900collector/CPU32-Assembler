/**
 * Process XFER instruction in different formats and if OK
 * return an object representing this instruction.
 * Created 2025-08-19 

 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>


#include "XFERInst.h"
#include "Instruction.h"
#include "Utility.h"
#include "InstSet.h"
#include "Logger.h"



using namespace std;


XFERInst::XFERInst()
{
	this->pLog = Logger::getInstance();
	this->pLog->LogMsg("XFERInst::XFERInst()");
	this->pLabel = nullptr;
}


/**
 *------------------------------------------------------------
 *
 * Determine if this object can handle in instruction
 * If it does, return a newly created "Instruction" derived object
 * else return a nullptr.
 */
Instruction * XFERInst::parse(std::vector<std::string> words)
{
	this->pLog->LogFunction("XFERInst::parse()");
	
	if(words[0]=="XFER")
	{
		return this->Process_XFER_Instruction(words);
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
 * Create an XFERInst object and return it back.
 */
Instruction *XFERInst::Process_XFER_Instruction(std::vector<std::string> words)
{
unsigned int iw = XFER;
unsigned int reg = 0;
std::stringstream params(words[1]);
std::vector<std::string> parts;
std::stringstream ss;

	this->pLog->LogFunction("Process_XFER_Instruction()");

	//
	// Tokeninze the remainder of the line into "parts"
	//
	while(params.good())
	{
		std::string substr;
		getline( params, substr, ',' );
		parts.push_back( substr );
	}

	//
	// Template code for Rs, Rd - if you have no registers to process then delete 
	//
	std::string d_reg = parts[0];
	std::string s_reg = parts[1];

	//
	// Registers are in the same place in all (trhidyrt) instructions
	//
	Utility *pUtil = new Utility();
	reg = pUtil->getRegister(d_reg);
	unsigned int d_regmask = pUtil->getRegisterMask('D',reg);
	reg = pUtil->getRegister(s_reg);
	unsigned int s_regmask = pUtil->getRegisterMask('S',reg);

	//
	// Log some debugging messages
	//
	ss<<"XFER ["<<s_reg<<"] -> ["<<d_reg<<"]";
	this->pLog->LogMsg( ss.str() );
	ss<<"IW ["<< std::hex << std::setw(8)<< std::setfill('0') << iw<<"]"<<endl;
	this->pLog->LogMsg( ss.str() );
	ss<<"D  ["<< std::hex << std::setw(8)<< std::setfill('0') << d_regmask<<"]"<<endl;
	this->pLog->LogMsg( ss.str() );
	ss<<"S  ["<< std::hex << std::setw(8)<< std::setfill('0') << s_regmask<<"]"<<endl;
	this->pLog->LogMsg( ss.str() );

	XFERInst *pInst = new XFERInst();
	pInst->setWord( iw | d_regmask | s_regmask );
	ss<<"OP [" << std::hex << setw(4)<< std::setfill('0') << pInst->_opcode << "]";
	this->pLog->LogMsg( ss.str() );
	pInst->setName("XFER");
	return pInst;
}
/* End of file */
