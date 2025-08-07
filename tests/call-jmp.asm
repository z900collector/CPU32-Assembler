;
; Call/Jump Test file
;
	.org 0

start:
	call func1
	call func2
	jump	end

	.org	0x1000
function1:
	nop
	ret

	.org	0x2000
function2:
	push	r0
	pop	r1
	ret

	.org	0x3000
end:
	nop
	halt
;
; End of file
