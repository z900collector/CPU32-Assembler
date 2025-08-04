/**
 * GlobalParameters.cpp
 *
 * Singleton class to hold parameters used throught code.
 * 
 * See: assemble.cpp for initial creation
 *
 *
 * (C) Sid Young
 * Free for Non-Commercial Use
 */
#include <string>
#include "GlobalParameters.h"
#include "Label.h"
#include "Instruction.h"

using namespace std;

GlobalParameters* GlobalParameters::instance = 0;


GlobalParameters* GlobalParameters::getInstance()
{
        if(instance == 0)
        {
                instance = new GlobalParameters();
        }
        return instance;
}



void GlobalParameters::setDumpFlag(bool f)
{
        this->_dump_labels = f;
}

bool GlobalParameters::getDumpFlag()
{
        return this->_dump_labels;
}


void GlobalParameters::setLineNumberFlag( bool f)
{
        this->_print_line_numbers = f;
}


bool GlobalParameters::getLineNumberFlag()
{
        return this->_print_line_numbers;
}


string GlobalParameters::getInputFile()
{
        return this->_source_file;
}

void GlobalParameters::setInputFile(string f)
{
        this->_source_file = f;
}


string GlobalParameters::getOutputFile()
{
        return this->_output_file;
}

void GlobalParameters::setOutputFile(string f)
{
        this->_output_file = f;
}
/* End of file */
