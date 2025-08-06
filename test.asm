;
; Test file
;
	.org 0

start:
	ldi	r1,255		; 0xff
	push	r0
	push	r1
	push	r7
	ldi	r2,512		; USES DBUS or RBUS in 32 bit
	ld		r3,r1			; uses RBUS
	xfer	r4,r1			; transfer into Latch 2 for logic operations.
	ldi	r5,0xff		; TEST hex values
keep_rotating:
	; INC reg using local ALU "C" and "Z" flags pushed to global flags reg
	dec	r1
	dec	r1
	inc	r1
	inc	r2
	inc	r3		
	jnz	keep_rotating
	jmp	finish

	.org	0x1000
table0:
; label cannot have a directive following it.
	.db	'Hello World'

	.org	0x4000
org1000:	xor	r1
	nop
	xor	(r1)		; test xoring a value at a memory lcoation
finish:
	nop
	halt

	.org	0x8000
table1:
	.db	aa5511
	.dw	0x3232
