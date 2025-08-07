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


std::string Instruction::getName() { return this->instruction_name;  }
void Instruction::setName(std::string name) { this->instruction_name=name;  }
unsigned int Instruction::getWord() { return this->instruction_word; }
void Instruction::setWord(unsigned int iw) { this->instruction_word=iw; }
unsigned int Instruction::getLength() { return this->instruction_length; }
void Instruction::setLength(unsigned int len) { this->instruction_length=len; }
unsigned int Instruction::getLocation(){ return this->_mem_loc; }
void Instruction::setLocation(unsigned int loc) {this->_mem_loc = loc;this->_mem_loc_flag=true; }

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

/* End of file */
