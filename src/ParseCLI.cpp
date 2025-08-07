/**
 * Parse the CLI arguments
 *
 * Format
 * asm <inputfile> -n -d
 * -o <outputfile (default output is <inputfile>.bin
 * -v  verbose output
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */

#include <string>
#include <vector>
#include <stdexcept>
#include <ostream>
#include <sstream>
#include <iostream>
#include "GlobalParameters.h"
#include "ParseCLI.h"
#include "Logger.h"

using namespace std;

ParseCLI::ParseCLI( GlobalParameters *p )
{
	this->pLog = Logger::getInstance();
	this->pLog->LogMsg("ParseCLI() Object Constructed");
	this->pGP = p;
}



void ParseCLI::parse(int argc, char* argv[])
{
	this->pLog->LogFunction("parse()");

	bool _output_file_flag = false;
	if(argc > 64)
	{
		throw std::out_of_range (" too many input parameters! ");
	}

	std::vector<string> args(argv + 1, argv + argc);


	for(const auto& arg : args)
	{

		if(this->pGP->getInputFile().empty())
		{
			if(arg == "-n")
			{
				if(this->pGP->getLineNumberFlag()==true)
				{
					throw std::runtime_error(" cannot use -n parameter twice!");
				}
				this->pGP->setLineNumberFlag(true);
				continue;
			}
			if(arg == "-d" || arg == "--dump")
			{
					  if(this->pGP->getDumpFlag() == true)
					  {
								 throw std::runtime_error(" cannot use -d/--dump parameter twice!");
					  }
					  this->pGP->setDumpFlag(true);
					  continue;
			}
		}
		else
		{
			if(_output_file_flag == true)
			{
				 this->pGP->setOutputFile(arg);
				 continue;
			}
			if((arg == "-o") && (_output_file_flag == false))
			{
				 _output_file_flag = true;
				 continue;
			}
		}
		this->pGP->setInputFile(arg);
	}
}
/* End of file */
