;
; Test Push/Pop code
; 2024-08-07
; Hex dump should be
; 16 bytes - PUSH
;  8 bytes - NOP
; 16 bytes - POP
;  2 bytes - NOP
;  2 bytes - HALT
; TODO - build a workflow that tests hexdump against running sample.


	.org 0

start:
	push	r0
	push	r1
	push	r2
	push	r3
	push	r4
	push	r5
	push	r6
	push	r7
	nop
	nop
	nop
	nop
	pop	r0
	pop	r1
	pop	r3
	pop	r4
	pop	r4
	pop	r5
	pop	r6
	pop	r7
	nop
	halt
; end of file
