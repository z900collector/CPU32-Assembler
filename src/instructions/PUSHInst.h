/**
 * Created 2025-08-07
 * Header for the PUSH Instruction
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef PUSH_08_INST_H
#define PUSH_08_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"
#include "Utility.h"
#include "InstSet.h"



class PUSHInst : public Instruction
{
protected:
Instruction *Process_PUSH_Instruction(std::vector<std::string>);

public:
PUSHInst();
Instruction * parse(std::vector<std::string>);
};
#endif
