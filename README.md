# ASM24 Assembler

DRAFT - Assembler is in Development.

ASM24 is an assembler written in basic C++ custom HomeBrew CPU design. 

What makes ASM24 different is the logic for each instruction is handled by the "Instruction Object" itself. This allows the mnemonics and opcodes to be changed to suit any architecture.

## Status

The code if working with a limited set of instructions defined so far. 

I have written a tool to speed up class creation and this will allow me to define all the instructions I want my CPU to process.

The inital build works but is still in development as I add more instructions to it. The code builds error free and produces a working assembler that will process .asm files.

## What is NOT working

* The code does not write the binary to a file, not a big effort is required but I have focused on parsing more complicate dinstructions first.
* The label processing is not completed
* Labels that are unresolved when encoutered is not yet completed.
