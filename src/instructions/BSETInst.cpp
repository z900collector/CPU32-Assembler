/**
 * Process BSET instruction in different formats and if OK
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


#include "BSETInst.h"
#include "Instruction.h"
#include "Utility.h"
#include "InstSet.h"
#include "Logger.h"



using namespace std;


BSETInst::BSETInst()
{
	this->pLog = Logger::getInstance();
	this->pLog->LogMsg("BSETInst() Constructor");
	this->pLabel = nullptr;
}


Instruction * BSETInst::parse(std::vector<std::string> words)
{
	this->pLog->LogFunction("parse()");
	if(words[0]=="BSET")
	{
		return this->Process_BSET_Instruction(words);
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
 * Create an BSETInst object and return it back.
 */
Instruction *BSETInst::Process_BSET_Instruction(std::vector<std::string> words)
{
unsigned int iw = BSET;
unsigned int reg = 0;
std::stringstream params(words[1]);
std::vector<std::string> parts;

	this->pLog->LogFunction("Process_BSET_Instruction()");
	while(params.good())
	{
		std::string substr;
		getline( params, substr, ',' );
		parts.push_back( substr );
	}
	Utility *pUtil = new Utility();
	std::string d_reg = parts[0];
	std::string s_reg = parts[1];

	/* Registers are in the same place in all instructions */
	reg = pUtil->getRegister(d_reg);
	unsigned int d_regmask = pUtil->getRegisterMask('D',reg);
	reg = pUtil->getRegister(s_reg);
	unsigned int s_regmask = pUtil->getRegisterMask('S',reg);

	std::stringstream ss;
	ss<<"BSET ["<<s_reg<<"] -> ["<<d_reg<<"]";
	this->pLog->LogMsg( ss.str() );
	ss<<"IW ["<< std::hex << std::setw(4)<< std::setfill('0') << iw<<"]"<<endl;
	this->pLog->LogMsg( ss.str() );
	ss<<"D  ["<< std::hex << std::setw(4)<< std::setfill('0') << d_regmask<<"]"<<endl;
	this->pLog->LogMsg( ss.str() );
	ss<<"S  ["<< std::hex << std::setw(4)<< std::setfill('0') << s_regmask<<"]"<<endl;
	this->pLog->LogMsg( ss.str() );

	BSETInst *pInst = new BSETInst();
	pInst->setWord( iw | d_regmask | s_regmask );
	ss<<"OP [0x"<< std::hex << setw(4)<<std::setfill('0')<<pInst->getWord()<<"]";
	this->pLog->LogMsg( ss.str() );
	pInst->setName("BSET");
	pInst->setLength(1);
	return pInst;
}
/* End of file */
