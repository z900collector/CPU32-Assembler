/**
 * Represents the Program Counter in memory
 *
 * Initially 0, gets set via a '.org xxxxh' statement
 *
 * Increments by "n" bytes each time an instruction class
 * processes a valid instruction. So PC will always point
 * to next available location.
 *
 * Each time we encounter a label, grab the PC value.
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */

#ifndef ProgramCounter_Header
#define ProgramCounter_Header

#include <string>


class ProgramCounter
{
private:
unsigned int pc;

public:
ProgramCounter();
void incPC(unsigned int v);
void setPC(unsigned int v);
unsigned int getPC() const;
std::string DisplayAsHex();
};

#endif
