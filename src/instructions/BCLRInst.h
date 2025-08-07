/**
 * Created 2025-08-07
 * Header for the BCLR Instruction
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef BCLR_12_INST_H
#define BCLR_12_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class BCLRInst : public Instruction
{
protected:
Instruction *Process_BCLR_Instruction(std::vector<std::string>);

public:
BCLRInst();
Instruction * parse(std::vector<std::string>);
};
#endif
