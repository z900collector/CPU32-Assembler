#ifndef LOAD_INST_H
#define LOAD_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class LDInst : public Instruction
{
protected:
Instruction *LoadRegister(std::vector<std::string>);
Instruction *LoadImmediate(std::vector<std::string>);

public:
LDInst();
Instruction * parse(std::vector<std::string>);
};
#endif
