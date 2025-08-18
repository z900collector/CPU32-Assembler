# Overview #

Currently I am building a 16 bit version of the TTL based CPU, so the instruction opcodes are 16 bits.

The design of the CPU uses the top 2 bits to define the instruction type for the four parallel instruction registers. This leaves 6 bits for the Instruction followed by 6 bits for the register indexing.

In a 16 bit design, the bit assignements are currently defined as:

```
FEDCBA98 76543210
TTiiiiii SSSDDD--
```

Where:

 "T" is a Type bit.
 "i" is an Instruction
 "S" is a Source Register
 "D" is a Destination Register.

For Instructions that do not use registers, the S & D bits are basically 0.

# Instruction Set Architecture (ISA)

The "T" bits are designated as follows:
```
00------ Misc Instructions and Primary ALU Operations.
01------ Register Moves involving memory/Immediate values.
10------ Transfer Register and Register specific ALU Operations.
11------ Jump/Call Instructions + (HALT -> all F's).
```
STATUS: Very Incomplete! As I build each functional unit I am adding and updateing this page.

# Registers

The current design should have 8 registers called R0 to R7. This allow for a 3-bit addressing scheme within an instruction.
Source and Destination registers are 3 bits each (giving 8 registers) R0-R7 but can be expanded to 16 registers each very easily.

R0-R3 are specialized registers with extended ALU capability (INC/DEC/SHL/ROL etc). It may be possible to extend this but R7 is slated as the results register for ALU maths operations
and R6 may be the PC value (still adddressed as "PC" in instructions but sitting in the register file. R5 may be used as the SP data value. i.e. Write PC+1 to R5 -> which automatically pushes it to the Stack Module on a "CALL" instruction.

## Instruction mnemonic bit encoding

Below is the 8 bit value representing the upper 8 bits of an instruction:

```
FEDC BA98
00-- ---- Type 0 Instruction - Miscellaneous/ALU 00-4f
01-- ---- Type 1 Instruction - Moves to/from memory 50-7f
10-- ---- Type 2 Instruction - Register operations 80-bf
11-- ---- Type 3 Instruction - Jumps/Calls (+halt) c0-ff
```
Bits 5-0 are available for use for the related instructions of that type. To facilitate instruction decoding logic, each instruction group, such as stack operations will be grouped so that decoding on a functional unit can be implemented (if feasable).

Using four separate Instuction decoding queues should allow different methods of instruction decoding, such as decoding on a functional unit rather than centralising the control signal generation and using lots of decoing EPROMs.


## Type 0 Instructions

The type 0 instructions have a range of 00-4f
```
	NOP   = 0x00
	BSET  = 0x01 - Register Only at this stage
	BCLR  = 0x02
	BTST  = 0x03
	Free 06-0f

	DEC   = 0x10
	DEC_R = 0x11 - Register
	DEC_M = 0x12 - Memory
	Free 12-1f
	
	INC   = 0x20
	INC_R = 0x20 - Register
	INC_M = 0x21 - Memory
	Free 22-2f
	
	XOR   = 0x30 
	XOR_R = 0x31 - Register
	XOR_RM= 0x32 - R+M
	XOR_M = 0x33 - Memory
	Free 34-3f

	PUSH  = 0x40 - Push Register <Rs>
	POP   = 0x41 - Pop into Register <Rd>
	RSP   = 0x42 - Reset Stack Pointer
	Free 40-4f
```

## Type 1 Instructions

Type 1 Instruction 50-7f

```
	LD    = 0x50
	LDM   = 0x51 - From memory (16 bits)
	LDI   = 0x52 - Load Immediate (8 bits) S bits are register to store to.
	STM   = 0x60 - Store R<s> to Memory
	MV    = 0x70 - Store R<s> to R<d> (Latch A in R<d>)
```

## Type 2 Instructions

Type 2 Instruction - Register operations 80-bf

```
	XFER  = 0x80 - Reg -> Reg (Writes to both Latch A and B)
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
