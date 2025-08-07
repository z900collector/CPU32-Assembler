/**
 *
 * Process INC & DEC instructions
 *
 * Format:
 *  DEC Rd   where "d" is 0-8
 *  DEC (Rd) memory pointed to by Register
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#ifndef INC_DEC_INST_Header
#define INC_DEC_INST_Header

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class INCDECInst : public Instruction
{
protected:
Instruction * Decrement(std::vector<std::string>);
Instruction * Increment(std::vector<std::string>);

public:
INCDECInst();
Instruction * parse(std::vector<std::string>);
};
#endif
