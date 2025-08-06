/**
 * Various utility functions common to many operations but not all!
 *
 *
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <iomanip>

#include "Utility.h"



/**
 *------------------------------------------------------------
 *
 * Rotate the register index till its in the right place.
 * This type of Utility has Source and Destination Registers
 * encoded in the same instruction at different spots.
 *
 * 16 Bit Format
 * TTiiiiii SSSDDD00
 * TTiiiiii SSSDDD00 76543210
 * TTiiiiii SSSDDD00 -------- 76543210
 *
 * BITS  Reg  Mask
 * 16     D     2
 * 16     S     5
 * 24     D    10
 * 24     S    13
 * 32     D    18
 * 32     S    21;
 */
unsigned int Utility::getRegisterMask(char reg, unsigned int mask)
{
        switch(reg)
        {
                case 'D':
                        mask = mask << 2;
                        break;
                case 'S':
                        mask = mask << 5;
                        break;
        }
        return mask;
}



/**
 *------------------------------------------------------------
 *
 * Given a string representing the register as R1, R2 etc
 * return an INT 0-x
 * This RISC design used R0 to R8
 *
 */
unsigned int Utility::getRegister(std::string r_name)
{
unsigned int rv = 0;

        char r_index = r_name.at(1);

        if(r_name.at(0) == 'R')
        {
                rv = int(r_index)-48;
        }
        else
        {
                throw std::invalid_argument("Registers should start with R");
        }
        return rv;
}



/**
 *------------------------------------------------------------
 *
 * One way to trim the LHS of a string
 *
 */
std::string Utility::ltrim(std::string str)
{
        const std::string nothing = "";
        const auto line = std::regex_replace(str, std::regex( "^\\s+" ), nothing);
        return line;
}



std::string Utility::rtrim(std::string str)
{
        const std::string nothing = "";
        const auto trimmed = std::regex_replace(str, std::regex( "\\s+$" ), nothing);
        return trimmed;
}


/**
 *------------------------------------------------------------
 *
 * Given a string, split it into tokens
 *
 */
std::vector<std::string> Utility::split(const std::string& str)
{
std::vector<std::string> tokens;
std::istringstream iss(str);
std::string token;

        while (iss >> token)
        {
                tokens.push_back(token);
        }
        return tokens;
}
/* End of file */
