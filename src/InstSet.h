/**
 * Below is the 16 bit version of the CPU, it will be 24 bits when complete.
 *
 * The design of the CPU uses the top 2 bits to define the instruction type for the four parallel instruction registers.
 * 00------ Misc Instructions and Primary ALU Operations.
 * 01------ Registrer Moves involving memory/Immediate values
 * 10------ Transfer Register and Register specific ALU oPerations
 * 11------ Jump/Call Instructions + HALT (all F's)
 */
#ifndef INSTRUCTION_CODES_HDR
#define INSTRUCTION_CODES_HDR

/**
 * Instruction mnemonic bit encoding
 * can be used in custom architecture
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

enum InstSet
{
	NOP   = 0x0000,
	BSET	= 0x0100,
	PUSH  = 0x0400,
	POP	= 0x0500,
	DEC   = 0x1000,
	DEC_R = 0x1100,
	DEC_M = 0x1200,
	INC   = 0x2000,
	INC_R = 0x2100,
	INC_M = 0x2200,
	XOR_R = 0x3000,
	XOR_RM= 0x3100,
	XOR_M = 0x3200,
	JMP   = 0xc100,
	JR    = 0xc200,
	JC    = 0xc300,
	JNC   = 0xc410,
	JZ    = 0xc500,
	JNZ   = 0xc600,
	LD    = 0x7000,
	LDM   = 0x7100,
	LDI   = 0x7200,
	BCLR	= 0x0200,
	BTST	= 0x0300,
	CALL	= 0xd000,
//NEXT_ENTRY
	HALT  = 0xff00
};
#endif
