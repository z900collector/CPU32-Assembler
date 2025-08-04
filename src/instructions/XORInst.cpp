/**
 * Process XOR instructions
 *
 * XOR Rd       ; XOR the Register with the integer ALU
 * XOR (Rd)     ; memory with the integer ALU
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>


#include "Instruction.h"
#include "Utility.h"
#include "XORInst.h"
#include "InstSet.h"
#include "Logger.h"

using namespace std;


XORInst::XORInst()
{
        this->pLog = Logger::getInstance();
}


Instruction * XORInst::parse(std::vector<std::string> words)
{

        // XOR Rs
        if(words[0]=="XOR")
        {
                return this->XORRegister(words);
        }
        return nullptr;
}



/**
 *------------------------------------------------------------
 *
 *
 *
 */
Instruction *XORInst::XORRegister(std::vector<std::string> words)
{
unsigned int iw = XOR_R;
unsigned int reg = 0;
std::stringstream params(words[1]);
std::vector<std::string> parts;
std::string s_reg = "";
unsigned int s_regmask=0;

        while(params.good())
        {
                std::string substr;
                getline( params, substr, ',' );
                parts.push_back( substr );
        }
        Utility *pUtil = new Utility();
        reg = parts.size();
        if(reg == 1)
        {
                if(parts[0].at(0) == 'R')
                {
                        s_reg = parts[0];
                        reg = pUtil->getRegister(s_reg);
                        s_regmask = pUtil->getRegisterMask('S',reg);
                        Instruction *pInst = new XORInst();
                        pInst->setWord( iw | s_regmask );
                        pInst->setName("XOR");
                        return pInst;
                }
                // XOR ($0xaa55)        // hex
                // XOR ($1055)          // decimal location
                // XOR (#label)         // label
                // XOR (R2)
                if(parts[0].at(0) == '(')
                {
                        iw = XOR_M;
                        std::cout<<"Token Processing: "<<parts[0]<<std::endl;
                        parts[0].pop_back();    // last char
                        parts[0].erase(0, 1);   //first char
                        switch(parts[0].at(0))
                        {
                                case 'R':
                                        reg = pUtil->getRegister(parts[0]);
                                        s_regmask = pUtil->getRegisterMask('S',reg);
                                        iw = XOR_RM | s_regmask;
                                        break;
                                case '#':
                                        // label - work out how to do that.
                                        break;
                                case '$':
                                        // absolute mem location in decimal or hex
                                        break;
                                default:
                                        std::cout<<"UNKNOWN TOKEN: "<<parts[0]<<std::endl;
                                        break;
                        }
                        std::cout<<"XOR Memory["<<s_reg<<"]"<<std::endl;
                }
                Instruction *pInst = new XORInst();
                pInst->setWord( iw );
                pInst->setName("XOR");
                return pInst;
        }
        return nullptr;
}
/* End of file */
