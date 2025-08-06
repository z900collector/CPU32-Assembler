/**
 * Parse the source file, line by line.
 *
 * If the line does not have/start with a directive, check for an instruction
 * iterate through the vector of instructions till found and instance an instruction
 * object to process that line, if successfull, the object will produce binary code.
 *
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */

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


#include "ParseCLI.h"
#include "Parser.h"
#include "ProgramCounter.h"
#include "Label.h"
#include "Utility.h"
#include "Instruction.h"
#include "InstLoader.h"
#include "GlobalParameters.h"
#include "Logger.h"


using namespace std;


Parser::Parser()
{
	this->pLog = Logger::getInstance();
}

/**
 *----------------------------------------
 *
 *
 *
 */
std::string Parser::Parser::toHex( unsigned x )
{
char hex_string[20];
sprintf(hex_string, "%X", x);
return hex_string;
}



/**
 *------------------------------------------------------------
 *
 * blank spaces removed, now check for a directive in UPPERCASE
 *
 */
void Parser::CheckForDirective(std::string _line, ProgramCounter *pc)
{
	this->pLog->LogFunction("Parser::CheckForDirective()");

	Utility *pU = new Utility();
	std::transform(_line.begin(), _line.end(), _line.begin(), ::toupper);
	const auto line = pU->ltrim(_line);
	const auto trimmed = pU->rtrim(line);
	auto words = pU->split(trimmed);

//	  for(const auto& word : words)
//	  {
//		  std::cout << word << std::endl;
//	  }
	if( words[0] == ".DB")
	{
		 pLog->LogMsg(".db Directive "+words[1]);
	}
	if( words[0] == ".ORG")
	{
		int v = std::stoi(words[1],nullptr,16);
		pc->setPC( (unsigned) v );
		std::stringstream ss;
		ss << "0x" << std::hex << v;
		pLog->LogMsg(".org Directive "+ss.str());
	}
}



/**
 *------------------------------------------------------------
 *
 * Check if label found, need vector to our labels.
 * Check for dup label, if so, error rv = 1
 * Otherwise add it with PC value rv = 1
 */
unsigned int Parser::CheckForLabel(std::string _line, std::vector<Label*> *lTable, ProgramCounter *pc)
{
	this->pLog->LogFunction("Parser::CheckForLabel()");

	Utility *pU = new Utility();
	auto words = pU->split(_line);
	words[0].resize(words[0].size() - 1);
	for(auto it = lTable->begin() ; it != lTable->end(); ++it)
	{
//		  cout<<"NAME = "<<(*it)->getName()<<endl;
		if((*it)->getName()== words[0])
		{
			if( (*it)->isDefined())
			{
				cout<<"ERROR - label ["<<words[0]<<"] already defined!"<<endl;
				return 1;		   // error - already in table
			}
		}
	}
	(*lTable).push_back(new Label(words[0], pc->getPC()));
	return 0;
}



/**
 *----------------------------------------
 *
 *
 * "Labels" holds known labels as encountered
 * "MissingLabels" holds Instructions that need a Label but it has not yet been passed.
 *		 If size() > 0 at end of run then there is a missing Label
 */
vector<Instruction *> Parser::parse( fstream *pSourceFile, GlobalParameters *p )
{
unsigned int _line_number = 0;
string LINE;

	this->pLog->LogFunction("Parser::parse()");

	this->pGP = p;
	Utility *pU = new Utility();
	InstLoader *pIL = new InstLoader();
	this->pISet = pIL->load();
	int count = this->pISet->size();
	std::stringstream ss;
	ss<<count;
	pLog->LogMsg("Instruction Set Loaded - "+ss.str()+" instruction groups loaded.");

	this->pPC = new ProgramCounter();
	pPC->setPC(0);

	pLog->LogMsg("Read File.");
	while(getline(*pSourceFile, LINE))
	{
		_line_number++;
		if((this->pGP->getLineNumberFlag()==true)&&(this->pGP->getDumpFlag()==false))
			cout << _line_number<<": "<<LINE<<endl;;

		/* skip blank lines */
		if( LINE.length() ==0 )
		{
			continue;
		}

		string line = pU->ltrim( LINE  ) ;
		char _cLetter = line.at(0);
		if(isalpha(LINE[0]))
		{
				this->CheckForLabel(LINE, &Labels, pPC);
				pLog->LogMsg("Found possible LABEL ["+LINE+"]");
				vector<std::string> components = pU->split(LINE);
				unsigned int count = components.size();
				pLog->LogMsg("Component Count: ["+std::to_string(count)+"]");
				if(count == 1)
				{
					continue;
				}
				unsigned int i = 1;
				pLog->LogMsg("Rebuild LINE");
				LINE="";
				do
				{
					LINE += components[i++]+'\t';   // skip the label
					pLog->LogMsg("LINE: ["+LINE+"]");
					--count;
				} while (count>0);

		}
//		  else
//		  {
			switch(_cLetter)
			{
				case ';':
					continue;
				case '.':
					this->CheckForDirective(LINE, pPC);
					break;
				default:
					string _line = LINE;
					std::transform(_line.begin(), _line.end(), _line.begin(), ::toupper);
					const auto line = pU->ltrim( _line );
					const auto trimmed = pU->rtrim( line );
					vector<std::string> words = pU->split(trimmed);
					for(std::vector<Instruction *>::size_type x = 0; x < this->pISet->size() ; x++)
					{
						Instruction *pI = this->pISet->at(x);
						auto *pInst = pI->parse( words );		   // give each instruction the chance to parse the line.
						if( pInst != NULL)
						{
							IList.push_back( pInst );
							unsigned int iLength = pInst->getLength();
							pPC->incPC(iLength);
							pLog->LogMsg(pPC->DisplayAsHex()+" OP: "+pInst->getName()+" "+pInst->toHex());
						}
					}
					break;
			}
//		  }
	}
	if(pGP->getDumpFlag()==true)
	{
		cout<< "Instruction list size is "<< IList.size() << endl;
		for(std::vector<Instruction*>::size_type x = 0; x < IList.size(); x++)
		{
			cout<<IList[x]->getName()<<endl;
		}
	}

	pLog->LogMsg("Discovered Labels");
	cout<<endl<<"Discovered Labels"<<endl;

	std::vector<Label *>::iterator iter, end;
	for(iter = Labels.begin(), end=Labels.end(); iter != end; ++iter)
	{
		string n = (*iter)->getName();
		unsigned int l = (*iter)->getLocation();
		bool f = (*iter)->isDefined();
		std::stringstream ss;
		string valid = f ? "":"- undefined";
		ss << "0x" << std::hex << l << " - "<<n<<" "<<valid;
		pLog->LogMsg(ss.str());
	}
	return IList;
}
/* end of file */
