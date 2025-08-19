/**
 * Created 2025-08-19
 * Header for the XFER Instruction
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef XFER_13_INST_H
#define XFER_13_INST_H

#include <string>
#include <vector>

#include "Instruction.h"
#include "Label.h"
#include "Logger.h"


class XFERInst : public Instruction
{
protected:
Logger *pLog;
Instruction *Process_XFER_Instruction(std::vector<std::string>);
Label *pLabel;

public:
XFERInst();
Instruction * parse(std::vector<std::string>);
};
#endif
