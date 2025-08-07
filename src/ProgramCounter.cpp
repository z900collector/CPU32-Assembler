/**
 * Represents the Program Counter in memory
 *
 * Initially 0, gets set via a '.org xxxxh' statement
 *
 * Increments by "n" bytes each time an instruction class
 * processes a valid instruction. So PC will always point
 * to next available location.
 *
 * Each time we encounter a label, grab the PC value.
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */


#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "ProgramCounter.h"

using namespace std;

ProgramCounter::ProgramCounter()
{
	this->pLog = Logger::getInstance();
	this->pLog->LogMsg("ProgramCounter::ProgramCounter()");
	this->pc = 0;
}


void ProgramCounter::incPC(unsigned int v)
{
	this->pLog->LogFunction("incPC()");
	this->pc=this->pc+v;
	std::stringstream ss;
	ss<<"PC ["<<this->pc<<"]";
	this->pLog->LogMsg( ss.str() );
}

void ProgramCounter::setPC(unsigned int v)
{
	this->pLog->LogFunction("setPC()");
	this->pc=v;
	std::stringstream ss;
	ss<<"PC ["<<this->pc<<"]";
	this->pLog->LogMsg( ss.str() );
}

unsigned int ProgramCounter::getPC() const
{
	return this->pc;
}

string ProgramCounter::DisplayAsHex()
{
	stringstream ss;
	ss << std::setw(4) << std::setfill('0') << std::hex << this->pc;
	return ss.str();
}
/* End of file */
