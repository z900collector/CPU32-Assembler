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
std::string   instruction_name="";
unsigned int  instruction_word=0;
unsigned int  instruction_length=1;
unsigned int  _mem_loc;
bool          _mem_loc_flag;
Label	 *pLabel;

public:
std::string getName();
void setName(std::string);
unsigned int getWord();
void setWord(unsigned int);
unsigned int getLength();
void setLength(unsigned int);
unsigned int getLocation();
void setLocation(unsigned int);
std::string toHex();

bool hasLabel();
Label * getLabel();

virtual Instruction * parse(std::vector<std::string>)=0;
};

#endif
