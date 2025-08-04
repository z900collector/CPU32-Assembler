# Overview

The "instructions" directory contains classes that represent assembly langauge Instructions and the code needed to parse a line of assembly from the given ASM file.

Rather than create a parser that must understand every instruction format, putting that logic into the Instruction Object seams like a novel way to process each line.

If an instruction has multiple formats, they could in placed into one file or you can create a file for each variation (that does tend to bloat the code).

## Expanding the Instruction Set

Adding a NEW instruction is as simple as:

* Creating a class file and header file in ./src/instructions
* Make sure the new instruction class has a base class of "Instruction"
* Adding the opcode into the InstSet.h file ./src/InstSet.h
* Add an include of the Instruction's header file in InstLoader.h
* And add a line in the load() method in "InstLoader.h" to push an instance of the Instruction into the list of available instructions.

## Debugging New Instructions
When developing new instrcutions, you can use the built in Logger class to write the internal operations of the new Instruction to the log file.
By tailing the log file, you can build a test asm file with the instruction in all it's variations and ensure the processing of the instruction is correct.

