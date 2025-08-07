#ifndef XFER_INST_H
#define XFER_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class XFERInst : public Instruction
{
protected:
Instruction *XferToRegister(std::vector<std::string>);

public:
XFERInst();
Instruction * parse(std::vector<std::string>);
};
#endif
