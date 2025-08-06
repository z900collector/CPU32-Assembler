/**
 * One pass OO Assembler for home built TTL CPU
 *
 * Native Instruction Set influenced by the MIPS and Z80
 *
 * Building: g++ *.h *.cpp  -o asm
 * (No make file yet)
 *
 * Sid Young (C)2025
 * Free for non-commercial use.
 *
 */


#include <regex>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>


#include "Logger.h"
#include "ParseCLI.h"
#include "Parser.h"
#include "ProgramCounter.h"
#include "Label.h"
#include "Instruction.h"
#include "GlobalParameters.h"


using namespace std;

/**
 *----------------------------------------
 *
 * DIAGNOSTIC
 * Dump out the Instructions as parsed.
void DumpList(vector<Instruction *> *pIList)
{
        if( pIList != 0)
        {
                cout<<endl;
                const auto length = pIList->size();
                cout<< "Instruction list size is "<< length << endl;
                for(int x = 0; x < length; x++)
                {
                        cout<< pIList[x]->getName()<<endl;
                }
        }
}
 */
/**
 *============================================================
 *
 *                           M A I N
 *
 * Create a vector to hold labels and instructions we can process
 * Thenreach line and process
 *
 *============================================================
 */
int main(int argc, char *argv[])
{
fstream _srcFile;

        Logger *pLog = Logger::getInstance();
        pLog->setLogDir("/logs");
        pLog->setFileName("assembler-debug");
        pLog->Start();
        GlobalParameters *pGP = GlobalParameters::getInstance();
        pLog->LogMsg("Create Parser - parse CLI");
        ParseCLI *pCLI = new ParseCLI( pGP );
        try {
                pCLI->parse(argc, argv);
        } catch (const std::exception &x)
        {
                pLog->LogMsg("ERROR - CLI Parser failed");
                std::cerr << "ERROR: " << x.what() << '\n';
                std::cerr << "usage: spasm -n -d <input_file> [-o <output_file>]...\n";
                std::cerr << "       options first, then files <opt> <input_file> [-o <output_file>]...\n";
                std::cerr << "       <opt> <input_file> [-o <output_file>]...\n";
                return EXIT_FAILURE;
        }
        pLog->LogMsg( "Source file ["+pGP->getInputFile()+"]" );
        pLog->LogMsg( "  Output to ["+pGP->getOutputFile()+"]" );
//      pLog->LogMsg( "Dump Labels ["+pGP->getDumpFlag()+"]" );
//      pLog->LogMsg( "Line Numbers["+pGP->getLineNumberFlag()+"]" );

        _srcFile.open(pGP->getInputFile(), ios::in);
        if(_srcFile.is_open())
        {
                pLog->LogMsg( "File opened." );
					 cout<<"Open file [ "<<pGP->getInputFile()<<" ]"<<endl;
                Parser *pParser = new Parser();
                const auto pIList = pParser->parse(&_srcFile, pGP);
                pLog->LogMsg( "Close File." );
                _srcFile.close();
                delete pParser;
        }
        else
        {
                pLog->LogMsg( "ERROR - File Not Found." );
                cerr << "ERROR - file not found - Unable to open file!" << endl;
        }

        delete pCLI;
        pLog->End();
        return 0;
}
/* End of file */




