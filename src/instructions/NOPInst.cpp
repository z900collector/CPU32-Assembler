/**
 * NOP Instruction
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "NOPInst.h"
#include "Logger.h"
#include "InstSet.h"


NOPInst::NOPInst()
{
        this->pLog = Logger::getInstance();
}


Instruction * NOPInst::parse(std::vector<std::string> words)
{
        if(words[0]=="NOP")
        {
                Instruction *pInst = new NOPInst();
                pInst->setName("NOP");
                pInst->setWord(NOP);
                pInst->setLength(1);
                return pInst;
        }
        else
                return nullptr;
}

/* End of file */
