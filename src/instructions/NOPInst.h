#ifndef NOP_INST_H
#define NOP_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Logger.h"

class NOPInst : public Instruction
{
protected:
Logger *pLog;

public:
NOPInst();
Instruction * parse(std::vector<std::string>);
};
#endif
