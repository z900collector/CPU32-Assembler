**Packages Required**

Built with gcc 11 on RHEL 8 - any gcc compiler above 8.4 should work.

Requries 'make' and it's associated dependencies.


**Building**

In the base directory, simple run "make", all files will compile and built in the "build" directory. Object files will be created in ./build/src and ./build/src/instructions

    $ make

An "asm" symlink will be created linked to ./build/asm

**Clean Up**

Run:

    $ make clean


Running the assembler. You need to specify an ASM file to assemble, failure to do so will yield an error message.
```
$ ./asm
ERROR - file not found - Unable to open file!
$
```

To assemble a suitable assembly file:
```
$ ./asm test.asm
LDI [0255] -> [R1]
D  [00010000]
OP [8c0100ff]
LDI [0512] -> [R2]
D  [00020000]
OP [8c020200]
LD [R1] -> [R3]
LDI [0XFF] -> [R5]
D  [00050000]
OP [8c0500ff]
Token Processing: (R1)
XOR Memory[]
$
```

**Sample Test File**

```;
; Test file
;
        .org 0

start:
        ldi     r1,255          ; 0xff
        ldi     r2,512          ; USES DBUS or RBUS in 32 bit
        ld              r3,r1                   ; uses RBUS
        xfer            r4,r1           ; transfer into Latch 2 for logic operations.
        ldi     r5,0xff         ; TEST hex values
keep_rotating:
        ; INC reg using local ALU "C" and "Z" flags pushed to global flags reg
        dec     r1
        dec     r1
        inc     r1
        inc     r2
        inc     r3
        jnz     keep_rotating
        jmp     finish

        .org    0x1000
        .db     'Hello World'

        .org    0x4000
org1000:        xor     r1
        nop
        xor     (r1)
finish:
        nop
        halt

        .org    0x8000
        .db     aa550011
        .dw     0x32323232      // 32bit word
```

**Log File**
The assmbler will create a log file in a directory called /logs/
It will log the operation of the assembler, very handy as you develop your Instruction Set Architecture (ISA).

***Sample Output***

```cat /logs/assembler-debug-2025-07-04.log
2025-07-04|11:14:19|S|=============================================
2025-07-04|11:14:19|START
2025-07-04|11:14:19|OK|Create Parser - parse CLI
2025-07-04|11:14:19|OK|Source file []
2025-07-04|11:14:19|OK|  Output to []
2025-07-04|11:14:19|OK|ERROR - File Not Found.
2025-07-04|11:14:19|END
2025-07-04|11:14:19|E|=============================================
2025-07-04|11:14:41|S|=============================================
2025-07-04|11:14:41|START
2025-07-04|11:14:41|OK|Create Parser - parse CLI
2025-07-04|11:14:41|OK|Source file [test.asm]
2025-07-04|11:14:41|OK|  Output to []
2025-07-04|11:14:41|OK|File opened.
2025-07-04|11:14:41|FUNC|Parser::parse()
2025-07-04|11:14:41|OK|Instruction Set Loaded - 5 instruction groups loaded.
2025-07-04|11:14:41|OK|Read File.
2025-07-04|11:14:41|FUNC|Parser::CheckForDirective()
2025-07-04|11:14:41|OK|.org Directive 0x0
2025-07-04|11:14:41|FUNC|Parser::CheckForLabel()
2025-07-04|11:14:41|OK|Hit a label line - content is: [start:]
2025-07-04|11:14:41|OK|Component Count: [1]
2025-07-04|11:14:41|OK|00000001 OP: LDI 8c0100ff
2025-07-04|11:14:41|OK|00000002 OP: LDI 8c020200
2025-07-04|11:14:41|OK|00000003 OP: LD 1b130000
2025-07-04|11:14:41|OK|00000004 OP: LDI 8c0500ff
2025-07-04|11:14:41|FUNC|Parser::CheckForLabel()
2025-07-04|11:14:41|OK|Hit a label line - content is: [keep_rotating:]
2025-07-04|11:14:41|OK|Component Count: [1]
2025-07-04|11:14:41|OK|00000005 OP: DEC 1d010000
2025-07-04|11:14:41|OK|00000006 OP: DEC 1d010000
2025-07-04|11:14:41|OK|00000007 OP: INC 1e010000
2025-07-04|11:14:41|OK|00000008 OP: INC 1e020000
2025-07-04|11:14:41|OK|00000009 OP: INC 1e030000
2025-07-04|11:14:41|FUNC|Parser::CheckForDirective()
2025-07-04|11:14:41|OK|.org Directive 0x1000
2025-07-04|11:14:41|FUNC|Parser::CheckForDirective()
2025-07-04|11:14:41|OK|.db Directive 'HELLO
2025-07-04|11:14:41|FUNC|Parser::CheckForDirective()
2025-07-04|11:14:41|OK|.org Directive 0x4000
2025-07-04|11:14:41|FUNC|Parser::CheckForLabel()
2025-07-04|11:14:41|OK|Hit a label line - content is: [org1000: xor     r1]
2025-07-04|11:14:41|OK|Component Count: [3]
2025-07-04|11:14:41|OK|Rebuild LINE
2025-07-04|11:14:41|OK|LINE: [xor       ]
2025-07-04|11:14:41|OK|LINE: [xor       r1      ]
2025-07-04|11:14:41|OK|LINE: [xor       r1      0XFF    ]
2025-07-04|11:14:41|OK|00004001 OP: XOR fc1000ff
2025-07-04|11:14:41|OK|00004002 OP: NOP 00000000
2025-07-04|11:14:41|OK|00004003 OP: XOR fd1000ff
2025-07-04|11:14:41|FUNC|Parser::CheckForLabel()
2025-07-04|11:14:41|OK|Hit a label line - content is: [finish:]
2025-07-04|11:14:41|OK|Component Count: [1]
2025-07-04|11:14:41|OK|00004004 OP: NOP 00000000
2025-07-04|11:14:41|OK|00004005 OP: HALT ff0000ff
2025-07-04|11:14:41|FUNC|Parser::CheckForDirective()
2025-07-04|11:14:41|OK|.org Directive 0x8000
2025-07-04|11:14:41|FUNC|Parser::CheckForDirective()
2025-07-04|11:14:41|OK|.db Directive AA550011
2025-07-04|11:14:41|FUNC|Parser::CheckForDirective()
2025-07-04|11:14:41|OK|Close File.
2025-07-04|11:14:41|END
2025-07-04|11:14:41|E|=============================================
```

