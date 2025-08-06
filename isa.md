# Instruction Set Architecture

Currently I am building a 16 bit version of the TTL based CPU, so the instruction opcodes are 16 bits (Only the top 8 bits shown).

The design of the CPU uses the top 2 bits to define the instruction type for the four parallel instruction registers.

Source and Destination registers are 3 bits each (giving 8 registers) R0-R7.

R0-R3 are specialized registers with extended ALU capability (INC/DEC/SHL/ROL etc).

```
00------ Misc Instructions and Primary ALU Operations.
01------ Register Moves involving memory/Immediate values
10------ Transfer Register and Register specific ALU oPerations
11------ Jump/Call Instructions + HALT (all F's)
```
STATUS: Very Incomplete!

##Instruction mnemonic bit encoding

Below is the 8 bit value representing the ISA:

```
7654 3210
00-- ---- Type 0 Instruction - Miscellaneous/ALU 00-4f
01-- ---- Type 1 Instruction - Moves to/from memory 50-7f
10-- ---- Type 2 Instruction - Register operations 80-bf
11-- ---- Type 3 Instruction - Jumps/Calls (+halt) c0-ff
```
Bits 5-0 are available
## Type 0 Instructions

The type 0 instructions have a range of 00-4f
```
	NOP   = 0x00
	BSET  = 0x01
	BCLR  = 0x02
	BTST  = 0x03

	DEC   = 0x10
	DEC_R = 0x11 - Register
	DEC_M = 0x12 - Memory
	INC   = 0x20
	INC_R = 0x20 - Register
	INC_M = 0x21 - Memory
	XOR   = 0x30 
	XOR_R = 0x31 - Register
	XOR_RM= 0x32 - R+M
	XOR_M = 0x33 - Memory
```

## Type 1 Instructions

Type 1 Instruction 50-7f

```
	LD    = 0x70
	LDM   = 0x71 - From memory (16 bits)
	LDI   = 0x72 - Load Immediate (8 bits)
```

## Type 2 Instructions

Type 2 Instruction - Register operations 80-bf

```
	XFER	0x8000 - Reg -> Reg
```

## Type 3 Instruction

Type 3 Instruction - Jumps/Calls (+halt) c0-ff

```
	JMP   = 0xc1
	JR    = 0xc2
	JC    = 0xc3
	JNC   = 0xc4
	JZ    = 0xc5
	JNZ   = 0xc6
	CALL  = 0xd0
	HALT  = 0xff
```
