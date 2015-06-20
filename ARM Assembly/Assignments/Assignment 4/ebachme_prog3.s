		AREA 	prog3, CODE, READONLY

		ENTRY									;registers usage
												;r0 - the value "x"
												;r1 - stores the memory address of the values for variables
												;r2 - the value "a"
												;r3 - the value "b"
												;r4 - the value "c"
												;r5 - the value "d"
	
		MOV		r0, #3							;move integer 3 to register zero
		BL		SUBR							;branch with linked register to sub routine SUBR
		MOV		r1, r0, LSL #1					;double the value stored in register zero
		
INFIN	B		INFIN							;infinite loop for end of program after sub routine call

SUBR	ADR		SP, S							;create a stack from the saved space
		STMEA	SP!, {r1, r2, r3, r4, r5, LR}	;store the registers and linked register in this stack
		ADR		r1, VALS						;load the memory address of the values of a, b, c, and d to register one
		LDMFD	r1!, {r2, r3, r4, r5}			;load the values into registers two, three, four, and five, respectfully
												; "!" needed to increment pointer position
		MLA 	r3, r0, r3, r4					;b = r0 integer * b + c
		MUL		r4, r0, r0						;c = r0 integer squared
		MLA		r0, r2, r4, r3					;store the product of a and c added to b in register zero
		SUB		r0, r0, r5						;subtract d from r0 integer and store the value in register zero
		TEQ		r0, #0							;test if the value in register zero is less than d, setting flags
		MOVGE	r0, r5							;place the value of d in register zero if the result in register zero is not null
		ADDLT	r0, r0, r5						;if the result is less than a null value 0, add r0 integer result left + d
		LDMEA	SP!, {r1, r2, r3, r4, r5, PC}	;load all registers from the stack and set the pc from linked registers value
		
		AREA 	prog3, DATA, READWRITE	

VALS	DCD		-5, 6, 7, 10
		space 	16
S 		space 	16								;space for r1
	
		END