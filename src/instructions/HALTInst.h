#ifndef HALT_INST_H
#define HALT_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class HALTInst : public Instruction
{
protected:
Logger *pLog;


public:
HALTInst();
Instruction * parse(std::vector<std::string>);
};
#endif
