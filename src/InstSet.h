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
 * can be used in custom architectures
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

enum InstSet
{
// Type 0  0x00 - 0x3f
	NOP   = 0x0000,
// 0000 0001 0sss 0BBB = bset Rx, 0
	BSET	= 0x0100,
	BSET_R0	= 0x0100,
	BSET_R1	= 0x0110,
	BSET_R2	= 0x0120,
	BSET_R3	= 0x0130,
	BSET_R4	= 0x0140,
	BSET_R5	= 0x0150,
	BSET_R6	= 0x0160,
	BSET_R7	= 0x0170,
// 0000 0010 0sss 0BBB R0, 0
	BCLR	= 0x0200,
	BCLR_R0	= 0x0200,
	BCLR_R1	= 0x0210,
	BCLR_R2	= 0x0220,
	BCLR_R3	= 0x0230,
	BCLR_R4	= 0x0240,
	BCLR_R5	= 0x0250,
	BCLR_R6	= 0x0260,
	BCLR_R7	= 0x0270,
// 0000 0011 0sss 0BBB R0, 0
	BTST	= 0x0300,
	BTST_R0	= 0x0300,
	BTST_R1	= 0x0310,
	BTST_R2	= 0x0320,
	BTST_R3	= 0x0330,
	BTST_R4	= 0x0340,
	BTST_R5	= 0x0350,
	BTST_R6	= 0x0360,
	BTST_R7	= 0x0370,

// 0000 0011 1000 0000
	RSP	= 0x0380,
	// 0x0390 03A0 03B0 03C0 03D0 03E0 03F0

// 00ii iiii 0sss 0000
	PUSH  = 0x0400,
	PUSH_R0  = 0x0400,
	PUSH_R1  = 0x0410,
	PUSH_R2  = 0x0420,
	PUSH_R3  = 0x0430,
	PUSH_R4  = 0x0440,
	PUSH_R5  = 0x0450,
	PUSH_R6  = 0x0460,
	PUSH_R7  = 0x0470,
	// 0x0480 0490 04A0 04B0 04C0 04D0 04E0 04F0
	POP	= 0x0500,
	POP_R0	= 0x0500,
	POP_R1	= 0x0510,
	POP_R2	= 0x0520,
	POP_R3	= 0x0530,
	POP_R4	= 0x0540,
	POP_R5	= 0x0550,
	POP_R6	= 0x0560,
	POP_R7	= 0x0570,
	DEC   = 0x0600,
	DEC_R = 0x0600,
	DEC_R0 = 0x0600,
	DEC_R1 = 0x0610,
	DEC_R2 = 0x0620,
	DEC_R3 = 0x0630,
	DEC_R4 = 0x0640,
	DEC_R5 = 0x0650,
	DEC_R6 = 0x0660,
	DEC_R7 = 0x0670,

	INC   = 0x0700,
	INC_R = 0x0700,
	INC_R0 = 0x0700,
	INC_R1 = 0x0710,
	INC_R2 = 0x0720,
	INC_R3 = 0x0730,
	INC_R4 = 0x0740,
	INC_R5 = 0x0750,
	INC_R6 = 0x0760,
	INC_R7 = 0x0770,

	INC_M = 0x2200,
	XOR_R = 0x3000,
	XOR_RM= 0x3100,
	XOR_M = 0x3200,
	DEC_M = 0x3f00,	// Decrement memory ?

//NEXT_T0_ENTRY
	LD    = 0x5000,
	LDM   = 0x5100,
	LDI   = 0x5200,
//NEXT_T1_ENTRY
	XFER	= 0x8000,
//NEXT_T2_ENTRY
	JMP   = 0xc100,
	JR    = 0xc200,
	JC    = 0xc300,
	JNC   = 0xc410,
	JZ    = 0xc500,
	JNZ   = 0xc600,
	CALL	= 0xd000,
	RET	= 0xd100,
//NEXT_T3_ENTRY
//NEXT_ENTRY
	HALT  = 0xff00
};
#endif
