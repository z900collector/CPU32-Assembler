/**
 * Base class for all Instructions
 */
#ifndef Instruction_Header
#define Instruction_Header

#include <string>
#include <vector>
#include "Label.h"
#include "Logger.h"



class Instruction
{
protected:
std::string   _name="";
unsigned int  _opcode=0;
unsigned int  _length=1;
unsigned int  _mem_loc = 0;
bool          _mem_loc_flag = false;
Label	 *pLabel = nullptr;
Logger *pLog = nullptr;

public:
void setName(std::string);
void setWord(unsigned int);
void setLength(unsigned int);
void setPC(unsigned int);

unsigned int getWord();
unsigned int getLength();
unsigned int getPC();
std::string getName();
std::string toHex();

bool hasLabel();
Label * getLabel();
void dump();

virtual Instruction * parse(std::vector<std::string>)=0;
};

#endif
