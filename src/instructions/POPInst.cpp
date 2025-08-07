/**
 * Process POP instruction in different formats and if OK
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


#include "POPInst.h"
#include "Instruction.h"
#include "Utility.h"
#include "InstSet.h"
#include "Logger.h"



using namespace std;


POPInst::POPInst()
{
	this->pLog = Logger::getInstance();
	this->pLabel = nullptr;
}


Instruction * POPInst::parse(std::vector<std::string> words)
{
	// POP Rs
	if(words[0]=="POP")
	{
		return this->Process_POP_Instruction(words);
	}
	return nullptr;
}



/**
 *------------------------------------------------------------
 * Then parse and mask in the source and destination register binary value
 * Create an POPInst object and return it back.
 */
Instruction *POPInst::Process_POP_Instruction(std::vector<std::string> words)
{
unsigned int iw = POP;
unsigned int reg = 0;
std::stringstream params(words[1]);
std::vector<std::string> parts;

	this->pLog->LogFunction("Process_POP_Instruction()");
	while(params.good())
	{
		std::string substr;
		getline( params, substr, ',' );
		parts.push_back( substr );
	}
	Utility *pUtil = new Utility();
	std::string s_reg = parts[0];

	std::stringstream ss;
	ss<<"POP ["<<s_reg;

	reg = pUtil->getRegister(s_reg);
	unsigned int s_regmask = pUtil->getRegisterMask('S',reg);

	ss<<"IW ["<< std::hex << std::setw(4)<< std::setfill('0') << iw<<"]";
	ss<<"S  ["<< std::hex << std::setw(4)<< std::setfill('0') << s_regmask<<"]";
	POPInst *pInst = new POPInst();
	pInst->setWord( iw | s_regmask );
	ss<< "OP [0x"<<std::hex << setw(4)<< std::setfill('0') << pInst->getWord() << "]";
	pInst->setName("POP");
	pInst->setLength(1);
	return pInst;
}
/* End of file */
