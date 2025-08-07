/**
 * Process CALL instruction in different formats and if OK
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


#include "CALLInst.h"
#include "Instruction.h"
#include "Utility.h"
#include "InstSet.h"
#include "Logger.h"



using namespace std;


CALLInst::CALLInst()
{
	this->pLog = Logger::getInstance();
	this->pLog->LogMsg("CALLInst() Constructor");
	this->pLabel = nullptr;
}


Instruction * CALLInst::parse(std::vector<std::string> words)
{
	this->pLog->LogFunction("parse()");
	if(words[0]=="CALL")
	{
		return this->Process_CALL_Instruction(words);
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
 * Create an CALLInst object and return it back.
 */
Instruction *CALLInst::Process_CALL_Instruction(std::vector<std::string> words)
{
unsigned int iw = CALL;
unsigned int reg = 0;
std::stringstream params(words[1]);
std::vector<std::string> parts;

	this->pLog->LogFunction("Process_CALL_Instruction()");
	while(params.good())
	{
		std::string substr;
		getline( params, substr, ',' );
		parts.push_back( substr );
	}
	std::string s_label = parts[0];


	std::stringstream ss;
	ss<<"Call this label -> ["<<s_label<<"]";
	this->pLog->LogMsg( ss.str() );

	// Create new object and a label, we match them up at the end;

	CALLInst *pInst = new CALLInst();
	pInst->setWord( iw );
	pInst->pLabel = new Label(s_label);
	ss<<"OP [" << std::hex << setw(8)<< std::setfill('0') << pInst->instruction_word << "]";
	this->pLog->LogMsg( ss.str() );
	pInst->setName("CALL");
	return pInst;
}
/* End of file */
