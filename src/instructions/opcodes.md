2026-02-02 Updates

To make initial instruction decoding simpler, the instruction set has been realigned to the first four bits where possible.
This has been done so a 4-16 line decoder can be used in the custom CPU hardware design.
While there are 64 bytes available per group, only about 16 or so are in use per group.



Program Counter (PC).

The program counter holds the 16-bit address of the current instruction being fetched from memory (State T0 and T1)
The PC is incremented on T2, this is after the Instruction is latched into the appropriate IR during T1.
A new PC value can be loaded into the DB_Latch and then Loaded into the PC.

The LDPC instruction is used to Load the PC -> Rd.

The STPC instruction is used to store Rs -> PC.


Stack Pointer (SP).

The stack pointer holds the 16-bit address of the current top of a stack located anywhere in external system RAM memory.
The external stack memory is organized as a last-in first-out (LIFO) file. Data can be pushed onto the stack from specific CPU registers or popped off of the stack to specific CPU registers through the execution of PUSH and POP instructions. The data popped from the stack is always the most recent data pushed onto it. The stack allows simple implementation of multiple level interrupts, unlimited subroutine nesting and simplification of many types of data manipulation.

In progress 

IE, DI, IN, OUT 
