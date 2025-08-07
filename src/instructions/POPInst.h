/**
 * Created 2025-08-07
 * Header for the POP Instruction
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef POP_12_INST_H
#define POP_12_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class POPInst : public Instruction
{
protected:
Instruction *Process_POP_Instruction(std::vector<std::string>);

public:
POPInst();
Instruction * parse(std::vector<std::string>);
};
#endif
