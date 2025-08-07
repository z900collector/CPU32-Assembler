/**
 * DEVELOPMENT - xfer between registers
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>


#include "XFERInst.h"
#include "Instruction.h"
#include "Utility.h"
#include "InstSet.h"
#include "Logger.h"



using namespace std;


XFERInst::XFERInst()
{
        this->pLog = Logger::getInstance();
}


Instruction * XFERInst::parse(std::vector<std::string> words)
{
        // XFER Rd,Rs
        if(words[0]=="XFER")
        {
                return this->XferToRegister(words);
        }
        return nullptr;
}



/**
 *------------------------------------------------------------
 *
 *
 *
 */
Instruction *XFERInst::XferToRegister(std::vector<std::string> words)
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
        cout<<"XFER ["<<s_reg<<"] -> ["<<d_reg<<"]"<<endl;

        /* Registers are in the same place in all instructions */
        reg = pUtil->getRegister(d_reg);
        unsigned int d_regmask = pUtil->getRegisterMask('D',reg);
        reg = pUtil->getRegister(s_reg);
        unsigned int s_regmask = pUtil->getRegisterMask('S',reg);

//      cout<<"IW ["<< std::hex << std::setw(8)<< std::setfill('0') << iw<<"]"<<endl;
//      cout<<"D  ["<< std::hex << std::setw(8)<< std::setfill('0') << d_regmask<<"]"<<endl;
//      cout<<"S  ["<< std::hex << std::setw(8)<< std::setfill('0') << s_regmask<<"]"<<endl;
        XFERInst *pInst = new XFERInst();
        pInst->setWord( iw | d_regmask | s_regmask );
//      cout << "OP [" << std::hex << setw(8)<< std::setfill('0') << pInst->instruction_word << "]" <<endl;
        pInst->setName("XFER");
		  pInst->setLength(1);
        return pInst;
}

/* End of file */
