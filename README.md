# CPU32-Assembler

DRAFT - Assembler is in Development.

[![C++ Build](https://github.com/z900collector/CPU32-Assembler/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/z900collector/CPU32-Assembler/actions/workflows/c-cpp.yml)

This assembler is written in basic C++ for a custom HomeBrew CPU design that has evolved from an 8 bit design idea into something much larger. 

It is referred to as ASM24 in much of the code as the target environment is going to be 24bits. Initially the code is working on a 16bit architecture but can easily be changed to any bit size (from 8 bits up).

What makes ASM24 different, is the logic for each instruction is handled by the "Instruction Object" itself. This allows the mnemonics and opcodes to be changed to suit any architecture without needing to have a single complex parser. Where the parsing is common, it's been moved to the base class of the instruction or a Utility class for code re-use.

Another feature is the one-pass design where labels, directives and instructions are processed as found and label references are dealt with at the end of the run.


## Status

The code is working with a limited set of instructions defined so far. The code requires a minimal tool chain, just g++/gcc and make.

The inital build works but is still in development as I add more instructions to it. The code builds error free and produces a working assembler that will process .asm files.


## Support Tools

I have written a BASH shell script (located in the tools folder) to speed up Instruction class creation and this will allow me to define all the instructions I want my CPU to process. The script only requires the mnemonic name and the OPCODE hex value,it wil lthen create an empty shell for the instruction, add it to the Instruction set list and the Class Loader. After that, the code should compile error free.


## What is NOT working

* The code does not write the binary data to a file, not a big effort is required but I have focused on parsing more complicate dinstructions first.
* The label processing is not completed.
* .DB .DW directives are not yet handled 
* Only a limited number of instructions have been created so far.
* A usage guide needs to be produced

## Debugging

The executable will automatically write a daily log file to /logs. This has proven to be increadibly usefull when developing new Instructions and debugging code in real-time as needed.

# Usage

The basic usage to see if a file will assemble is:
```
asm test.asm
```

Write output of assembly run to a hexadecimal (binary) file:
NOTE: This functionality is not yet completed.

```
asm test.asm -o output.hex
```

Dump source file with line numbers during processing of file:
```
asm -n test.asm
```

Dump object data to stdout and log file.
```
./asm -d tests/push.asm -o h.bin
```

# TODO

This is an active project as of 2025-08-01.

The following is a partial TODO list of additional functionality that is not yet completed.

* Complete binary file output code.
* Add option for object debug dump.
* Add option to dump pretty ASCII listing of code to stdout and file.
* Add remaining instructions for CPU24 / CPU32 Home brew project.



## Future Wishliat

* Support multiple CPU's such as z80, 6502 etc.

