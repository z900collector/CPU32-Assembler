/**
 * Created 2025-08-07
 * Header for the BTST Instruction
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef BTST_12_INST_H
#define BTST_12_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class BTSTInst : public Instruction
{
protected:
Logger *pLog;
Instruction *Process_BTST_Instruction(std::vector<std::string>);
Label *pLabel;

public:
BTSTInst();
Instruction * parse(std::vector<std::string>);
};
#endif
