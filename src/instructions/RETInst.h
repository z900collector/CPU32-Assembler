/**
 * Created 2025-08-07
 * Header for the RET Instruction
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef RET_14_INST_H
#define RET_14_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class RETInst : public Instruction
{
protected:
Instruction *Process_RET_Instruction(std::vector<std::string>);

public:
RETInst();
Instruction * parse(std::vector<std::string>);
};
#endif
