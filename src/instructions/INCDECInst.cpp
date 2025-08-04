/**
 * Process INC & DEC instructions
 *
 * Format:
 *  DEC Rd   where "d" is 0-8
 *  DEC (Rd) memory pointed to by Register
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "INCDECInst.h"
#include "Instruction.h"
#include "InstSet.h"
#include "Utility.h"
#include "Logger.h"


INCDECInst::INCDECInst()
{
        this->pLog = Logger::getInstance();
}



Instruction * INCDECInst::parse(std::vector<std::string> words)
{
        if(words[0]=="DEC")
        {
                return this->Decrement(words);
        }
        if(words[0]=="INC")
        {
                return this->Increment(words);
        }
        return nullptr;
}



/**
 * DEC R<n> or DEC (R<n>)
 *
 */
Instruction *INCDECInst::Decrement(std::vector<std::string> words)
{
unsigned int reg = 0;
std::string d_reg = "";
unsigned int iw=0;
std::stringstream params(words[1]);
std::vector<std::string> parts;
char mem_token = words[1].at(0);

        Utility *pUtil = new Utility();

        // DEC (R<n>) - strip (), get register and amend instruction_word (iw)
        //      cpu should read the address in Rs and fetch the memory value into the ALU
        // then dec it and store it back to memory
        if(mem_token == '(')
        {
                words[1].pop_back();
                words[1].erase(0, 1);
                d_reg = words[1];
                iw = DEC_M;
        }
        else    // Format: DEC R<n>
        {
                iw = DEC_R;
                while(params.good())
                {
                        std::string substr;
                        getline( params, substr, '(' );
                        parts.push_back( substr );
                }
                d_reg = parts[0];
        }
        /* Registers are in the same place in all instructions */
        reg = pUtil->getRegister(d_reg);
        unsigned int d_regmask = pUtil->getRegisterMask('D',reg);

        /* return a new inst of this instruction */
        Instruction *pInst = new INCDECInst();
        pInst->setName("DEC");
        pInst->setWord(iw | d_regmask);
        return  pInst;
}



/**
 * INC R<n> or INC (R<n>)
 *
 */
Instruction * INCDECInst::Increment(std::vector<std::string> words)
{
unsigned int iw=0;
unsigned int reg = 0;
std::string d_reg = "";

        std::stringstream params(words[1]);
        std::vector<std::string> parts;
        char mem_token = words[1].at(0);

        // INC (R<n>) - strip (), get register and amend instruction_word (iw)
        //      cpu should read the address in Rs and fetch the memory value into the ALU
        // then dec it and store it back to memory
        Utility *pUtil = new Utility();
        if(mem_token == '(')
        {
                words[1].pop_back();
                words[1].erase(0, 1);
                d_reg = words[1];
                iw = INC_M;
        }
        else    // Format: INC R<n>
        {
                iw = INC_R;
                while(params.good())
                {
                        std::string substr;
                        getline( params, substr, '(' );
                        parts.push_back( substr );
                }
                d_reg = parts[0];
        }
        /* Registers are in the same place in all instructions */
        reg = pUtil->getRegister(d_reg);
        unsigned int d_regmask = pUtil->getRegisterMask('D',reg);

        /* return a new inst of this instruction */
        Instruction *pInst = new INCDECInst();
        pInst->setName("INC");
        pInst->setWord(iw | d_regmask);
        return  pInst;
}

/* End of file */
