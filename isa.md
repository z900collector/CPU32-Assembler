# Overview #

Currently I am building a 16 bit version of the TTL based CPU, so the instruction word is fixed at 16 bits. This has been influenced by various RISC CPU designs.

The design of the CPU uses the top 2 bits to define the instruction type for the four parallel instruction registers. This leaves 6 bits for the Instruction followed by 6 bits for the register indexing with two spare bits.

For Instructions that do not use registers, the S & D bits are basically 0 unless they are used for an 8-bit immediate value.

In a 16 bit design, the bit assignements are currently defined as:

```
FEDCBA98 76543210
TTiiiiii -SSS-DDD
```

Where:

 "TT" is a Type bit.
 "iiiiii" is an Instruction.
 "SSS" is a Source Register
 "DDD" is a Destination Register.
 "-" Not defined (zero)
Note: If there are 16 registers then the format for Rs & Rd is SSSS DDDD


# Instruction Set Architecture (ISA)

The "T" bits are designated as follows:
```
00------ Misc Instructions and Primary ALU Operations.
01------ Register Moves involving memory/Immediate values.
10------ Transfer Register and Register specific ALU Operations.
11------ Jump/Call Instructions + (HALT -> all F's).
```
STATUS: Very Incomplete! As I build each functional unit I am adding and updating this page.

Refer to InsetSet.h for a full list of currently defined instructions (but not necessarily completed instruction classes).

# Registers

The current design should have 8 registers called R0 to R7. This allow for a 3-bit addressing scheme within an instruction.
Source and Destination registers that are 3 bits each (giving 8 registers) R0-R7 but can be expanded to 16 registers each very easily.

R0-R3 are specialized registers with extended ALU capability (INC/DEC/SHL/ROL etc). It may be possible to extend this but R7 is slated as the results register for ALU maths operations.
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
Bits 5-0 are available for use for the related instructions of that type. To facilitate instruction decoding logic, each instruction group, such as stack operations will be grouped so that decoding on a functional unit can be implemented (if feasable) using discrete logic rather than EPROMS.

Using four separate Instuction decoding queues should allow different methods of instruction decoding, such as decoding on a functional unit rather than centralising the control signal generation and using lots of decoding EPROMs (Still in design phase so this can/will change).


## Type 0 Instructions

The type 0 instructions have a range of 00-4f
```
	NOP                ; No Operation Instruction
	RSP                ; Reset Stack Pointer
	SC                 ; Set Carry Bit
	CC                 ; Clear Carry Bit
	EI                 ; Enable Interupts - Making Instruction available but no interupts in design yet
	DI                 ; Disable Interupts

	ADD Rs1,Rs2        ; ADD value in Rs1 and Rs2 and write back to results register with C/Z flags set.
	SUB Rs1,Rs2        ; Subtract Rs1 from Rs2
	DIV Rs1,Rs2        ; Divide Rs1 with Rs2
	MUL Rs1,Rs2        ; Multiple Rs1 with Rs2
```

## Type 1 Instructions

Type 1 Instruction 50-7f

```
	LD  Rd,Rs          ; Load Rd with the value from Rs
	LDI Rd,#1234       ; Load Rd with the 16bit word 0x1234 stored in PC+1
	LDI Rd,0x52        ; Load Rd with the Immediate (8 bits)value stored in the instruction (single fetch)
	
	ST  RD,#1234       ; store Register into memory location 0x1234 (16 bits)
	LD  Rd,0x52        ; Load Rd with the Immediate (8 bits)value stored in the instruction (single fetch)


	<todo>
	STM   = 0x60 - Store R<s> to Memory
	MV    = 0x70 - Store R<s> to R<d> (Latch A in R<d>)
```

## Type 2 Instructions

Type 2 Instruction - Register operations 80-bf

Notes: SP always points to the last value written. I.e PUSH or return address.
```
	PUSH Rn            ; Dec SP and then PUSH the Register Rn onto the stack
	POP Rn             ; POP stack into Register Rn and Inc SP.
	BSET Rn, B         ; Set bit "B" in Register "Rn"
	BCLR Rn, B         ; Clear (set to zero) bit "B" in Register "Rn"
	BTST Rn, B         ; Test bit "B" in Register "Rn" and set/clear "Z" Flag
	DEC (Rn)           ; Decrement Memory location addressed by "Rn" set/clear "C/Z" Flags
	INC (Rn)           ; Increment Memory location addressed by "Rn" set/clear "C/Z" Flags
	DEC Rn             ; Decrement Register "Rn" set/clear "C/Z" Flags
	INC Rn             ; Increment Register "Rn" set/clear "C/Z" Flags
	AND Rn             ; bitwise AND Register Latch A with Latch B set/clear "Z" Flag
	OR  Rn             ; bitwise OR Register Latch A with Latch B set/clear "Z" Flag
	XOR Rn             ; bitwise XOR Register Latch A with Latch B set/clear "Z" Flag 
   SL Rn              ; Shift Left Register "Rn" bit 15 dropped, bit 0 set to 0
	SR Rn              ; As per SL but right shift
	SLC Rn             ; Shift Left through Bit 15 into carry, bit 0 set to 0
	SRC Rn             ; Shift Right, Carry pushed into Bit 15, bit 0 dropped
	XFER Rs, Rd        ; Trasnfer Rs to Rd but writes to both Latch A and B.
```

## Type 3 Instruction

Type 3 Instruction - Jumps/Calls (+halt) c0-ff

```
	JMP label
	JR +/-127         ; jump within a 127 word location.
	JC  label         ; Jump if Carry is set (C=1)
	JNC label         ; Jump if Carry is NOT set (C=0)
	JZ  label         ; Jump if Z Flag is set (Z=1)
	JNZ label         ; Jump if Z Flag is clear (Z=0)
	CALL label        ; Call code at location defined by "label", SP=SP+1, return address pushed to SP
	RET               ; Return to location on SP and SP=SP-1
	HALT              ; Turn off system clock (Basically stop with PC set to location of HALT
```
