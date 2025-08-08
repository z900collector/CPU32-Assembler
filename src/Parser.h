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

vector<Label *> Labels;                                         // Labels encoutered (with PC value)
//vector<Instruction *> MissingLabels;    // Labels referenced which have not yet been discovered
vector<Instruction *> IList;            // list of decoded instructions in order
vector<Instruction *> *pISet;           // The list of Instructions we can decode



public:
Parser();
std::string toHex( unsigned int );
std::vector<Instruction *> parse( fstream *, GlobalParameters *);
void CheckForDirective(std::string, ProgramCounter *);
unsigned int CheckForLabel(std::string, std::vector<Label*> *, ProgramCounter *);

bool AssociateLabels( std::vector<Instruction*> *, std::vector<Label*> *);

};
#endif
