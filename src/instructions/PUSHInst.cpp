/**
 * Process PUSH instruction in different formats and if OK
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


#include "PUSHInst.h"


using namespace std;


PUSHInst::PUSHInst()
{
	this->pLog = Logger::getInstance();
	this->pLabel=nullptr;
}


Instruction * PUSHInst::parse(std::vector<std::string> words)
{
	if(words[0]=="PUSH")
	{
		return this->Process_PUSH_Instruction(words);
	}
	return nullptr;
}



/**
 *------------------------------------------------------------
 * mask in the source register binary value
 * Create an PUSHInst object and return it back.
 *
 * push r1
 *
 */
Instruction *PUSHInst::Process_PUSH_Instruction(std::vector<std::string> words)
{
unsigned int iw = PUSH;
unsigned int reg = 0;
std::stringstream params(words[1]);
std::vector<std::string> parts;

	this->pLog->LogFunction("Process_PUSH_Instruction()");
	while(params.good())
	{
		std::string substr;
		getline( params, substr, ',' );
		parts.push_back( substr );
	}
	Utility *pUtil = new Utility();
	std::string s_reg = parts[0];

	std::stringstream ss;
	ss<<"PUSH ["<<s_reg<<"]"<<endl;
	this->pLog->LogMsg(ss.str());

	/* Registers are in the same place in all instructions */
	reg = pUtil->getRegister(s_reg);
	unsigned int s_regmask = pUtil->getRegisterMask('S',reg);

	ss<<"IW ["<< std::hex << std::setw(8)<< std::setfill('0') << iw<<"]"<<endl;
	this->pLog->LogMsg( ss.str() );

	ss<<"S  ["<< std::hex << std::setw(8)<< std::setfill('0') << s_regmask<<"]"<<endl;
	this->pLog->LogMsg( ss.str() );

	PUSHInst *pInst = new PUSHInst();
	pInst->setWord( iw | s_regmask );
	ss << "OP [" << std::hex << setw(8)<< std::setfill('0') << pInst->instruction_word << "]" <<endl;
	this->pLog->LogMsg( ss.str() );

	pInst->setName("PUSH");
	return pInst;
}
/* End of file */
