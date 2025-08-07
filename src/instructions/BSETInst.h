/**
 * Created 2025-08-07
 * Header for the BSET Instruction
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef BSET_12_INST_H
#define BSET_12_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class BSETInst : public Instruction
{
protected:
Instruction *Process_BSET_Instruction(std::vector<std::string>);

public:
BSETInst();
Instruction * parse(std::vector<std::string>);
};
#endif
