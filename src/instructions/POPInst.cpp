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
}


Instruction * POPInst::parse(std::vector<std::string> words)
{
	// LD Rd,Rs
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
unsigned int iw = LD;
unsigned int reg = 0;
std::stringstream params(words[1]);
std::vector<std::string> parts;

	while(params.good())
	{
		std::string substr;
		getline( params, substr, ',' );
		parts.push_back( substr );
	}
	Utility *pUtil = new Utility();
	std::string d_reg = parts[0];
	std::string s_reg = parts[1];
	cout<<"LD ["<<s_reg<<"] -> ["<<d_reg<<"]"<<endl;

	/* Registers are in the same place in all instructions */
	reg = pUtil->getRegister(d_reg);
	unsigned int d_regmask = pUtil->getRegisterMask('D',reg);
	reg = pUtil->getRegister(s_reg);
	unsigned int s_regmask = pUtil->getRegisterMask('S',reg);

//	cout<<"IW ["<< std::hex << std::setw(8)<< std::setfill('0') << iw<<"]"<<endl;
//	cout<<"D  ["<< std::hex << std::setw(8)<< std::setfill('0') << d_regmask<<"]"<<endl;
//	cout<<"S  ["<< std::hex << std::setw(8)<< std::setfill('0') << s_regmask<<"]"<<endl;
	POPInst *pInst = new POPInst();
	pInst->setWord( iw | d_regmask | s_regmask );
//	cout << "OP [" << std::hex << setw(8)<< std::setfill('0') << pInst->instruction_word << "]" <<endl;
	pInst->setName("LD");
	return pInst;
}
/* End of file */
