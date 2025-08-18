/**
 * Source code parser header file.
 *
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#ifndef Parser_Header
#define Parser_Header

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ostream>
#include <iostream>
#include <regex>
#include <cctype>
#include <stdexcept>

#include "Logger.h"
#include "ProgramCounter.h"
#include "GlobalParameters.h"
#include "Label.h"
#include "Instruction.h"


using namespace std;


class Parser
{
protected:
Logger *pLog;
ProgramCounter *pPC;
GlobalParameters *pGP;

//
// Labels encoutered (with PC value) while parsing the source file.
//
vector<Label *> Labels;
//
// The list of instruction objects decoded from the source file
// It is in order and contains the fuly decoded instruction etc
//
vector<Instruction *> IList;
//
// The actual instruction set we can decode for.
//
vector<Instruction *> *pISet;



public:
Parser();
std::string toHex( unsigned int );
std::vector<Instruction *> parse( fstream *, GlobalParameters *);
void CheckForDirective(std::string, ProgramCounter *);
unsigned int CheckForLabel(std::string, std::vector<Label*> *, ProgramCounter *);

bool AssociateLabels( std::vector<Instruction*> *, std::vector<Label*> *);
bool WriteBinaryFile(std::vector<Instruction*> *);

};
#endif
