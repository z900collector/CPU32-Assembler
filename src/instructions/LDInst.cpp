/**
 * Process Load instruction in different formats and if OK
 * return an object representing this instruction.
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>


#include "LDInst.h"
#include "Instruction.h"
#include "Utility.h"
#include "InstSet.h"
#include "Logger.h"



using namespace std;


LDInst::LDInst()
{
        this->pLog = Logger::getInstance();
}


Instruction * LDInst::parse(std::vector<std::string> words)
{
        // LD Rd,Rs
        if(words[0]=="LD")
        {
                return this->LoadRegister(words);
        }
        // LDI Rd,Imm
        if(words[0]=="LDI")
        {
                return this->LoadImmediate(words);
        }
        return nullptr;
}



/**
 *------------------------------------------------------------
 * LD is defined in InstSet.h
 * Then parse and mask in the source and destination register binary value
 * Create an LDInst object and return it back.
 */
Instruction *LDInst::LoadRegister(std::vector<std::string> words)
{
unsigned int iw = LD;
unsigned int reg = 0;
std::stringstream params(words[1]);
std::vector<std::string> parts;

        while(params.good())
        {
                std::string substr;
                getline( params, substr, ',' );
                parts.push_back( substr );
        }
        Utility *pUtil = new Utility();
        std::string d_reg = parts[0];
        std::string s_reg = parts[1];
        cout<<"LD ["<<s_reg<<"] -> ["<<d_reg<<"]"<<endl;

        /* Registers are in the same place in all instructions */
        reg = pUtil->getRegister(d_reg);
        unsigned int d_regmask = pUtil->getRegisterMask('D',reg);
        reg = pUtil->getRegister(s_reg);
        unsigned int s_regmask = pUtil->getRegisterMask('S',reg);

//      cout<<"IW ["<< std::hex << std::setw(8)<< std::setfill('0') << iw<<"]"<<endl;
//      cout<<"D  ["<< std::hex << std::setw(8)<< std::setfill('0') << d_regmask<<"]"<<endl;
//      cout<<"S  ["<< std::hex << std::setw(8)<< std::setfill('0') << s_regmask<<"]"<<endl;
        LDInst *pInst = new LDInst();
        pInst->setWord( iw | d_regmask | s_regmask );
//      cout << "OP [" << std::hex << setw(8)<< std::setfill('0') << pInst->instruction_word << "]" <<endl;
        pInst->setName("LD");
		  pInst->setLength(1);
        return pInst;
}



/**
 *------------------------------------------------------------
 *
 *
 *
 */
Instruction *LDInst::LoadImmediate(std::vector<std::string> words)
{
unsigned int iw = LDI;
unsigned int reg = 0;
std::stringstream params(words[1]);
std::vector<std::string> parts;

// TODO
        while(params.good())
        {
                std::string substr;
                getline( params, substr, ',' );
                parts.push_back( substr );
        }
        Utility *pUtil = new Utility();
        std::string d_reg = parts[0];
        reg = pUtil->getRegister(d_reg);
        unsigned int d_regmask = pUtil->getRegisterMask('D',reg);
        std::string imm_value = parts[1];
        cout<<"LDI ["<<std::hex<<std::setw(4)<<std::setfill('0')<<imm_value<<"] -> ["<<d_reg<<"]"<<endl;
        LDInst *pInst = new LDInst();
        pInst->setWord(iw | d_regmask | std::stoi(imm_value,nullptr,0));
        pInst->setName("LDI");
        pInst->setLength(1);

        cout<<"D  ["<< std::hex << setw(4)<< std::setfill('0')<<d_regmask<<"]"<<endl;
        cout << "OP [0x"<<std::hex<<setw(4)<< std::setfill('0')<<pInst->getWord()<<"]" <<endl;
        return pInst;
}

/* End of file */
