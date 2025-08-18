/**
 * Created 2025-08-18
 * Header for the RSP Instruction
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef RSP_15_INST_H
#define RSP_15_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class RSPInst : public Instruction
{
protected:
Logger *pLog;
Instruction *Process_RSP_Instruction(std::vector<std::string>);
Label *pLabel;

public:
RSPInst();
Instruction * parse(std::vector<std::string>);
};
#endif
