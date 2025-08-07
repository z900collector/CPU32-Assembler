/**
 * Created 2025-08-07
 * Header for the CALL Instruction
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef CALL_12_INST_H
#define CALL_12_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class CALLInst : public Instruction
{
protected:
Instruction *Process_CALL_Instruction(std::vector<std::string>);

public:
CALLInst();
Instruction * parse(std::vector<std::string>);
};
#endif
