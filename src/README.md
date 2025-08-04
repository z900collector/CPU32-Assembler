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
