/**
 * CLI Parse Class
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef Parse_CLI_H
#define Parse_CLI_H

#include <string>
#include <vector>
#include <stdexcept>
#include <ostream>
#include <iostream>
#include "GlobalParameters.h"
#include "Logger.h"


using namespace std;

class ParseCLI
{
protected:
GlobalParameters *pGP;
Logger *pLog;

public:
ParseCLI( GlobalParameters * );
void parse(int argc, char* argv[]);
};
#endif
