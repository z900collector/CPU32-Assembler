/**
 * Common "Instruction" fields.
 *
 *
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Instruction.h"


std::string Instruction::getName()
{
	return this->_name;
}


void Instruction::setName(std::string name)
{
	this->_name=name; 
}


unsigned int Instruction::getWord()
{
	return this->_opcode;
}


void Instruction::setWord(unsigned int iw)
{
	this->_opcode = iw;
}

unsigned int Instruction::getLength()
{
	return this->_length;
}


void Instruction::setLength(unsigned int len)
{
	this->_length=len;
}



unsigned int Instruction::getPC()
{
	return this->_mem_loc;
}


void Instruction::setPC(unsigned int loc)
{
	this->_mem_loc = loc;
	this->_mem_loc_flag=true;
}



bool Instruction::hasLabel()
{
	return (this->pLabel != nullptr);
}
 
Label * Instruction::getLabel()
{
	return this->pLabel;
}




std::string Instruction::toHex()
{
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') <<std::hex << this->getWord();
	return ss.str();
}




void Instruction::dump()
{
	std::stringstream ss;
	ss.str();

	ss<<"Object Name is ["<<this->getName()<<"]"<<endl;
	ss<<"        Opcode ["<<this->toHex()<<"]"<<endl;
	ss<<"            PC ["<<std::setw(4)<<std::setfill('0')<<std::hex<<this->getPC()<<"]"<<endl;
	ss<<"        Length ["<<std::hex<<this->getLength()<<"]"<<endl;
	ss<<"       Label ? ["<<hasLabel()<<"]"<<endl<<endl;
	cout<<ss.str();
}
/* End of file */
