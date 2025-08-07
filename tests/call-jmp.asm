;
; Call/Jump Test file
;
	.org 0

	call	function1
	call	function2
	call	f3			; invalid - should generate an error
	jmp	end

function1:
	nop
	ret

function2:
	push	r0
	pop	r1
	ret

end:
	nop
	halt
;
; End of file
