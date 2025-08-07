#ifndef XOR_INST_H
#define XOR_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class XORInst : public Instruction
{
protected:
Instruction *XORRegister(std::vector<std::string>);

public:
XORInst();
Instruction * parse(std::vector<std::string>);
};
#endif
