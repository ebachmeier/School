		AREA 	prog1, CODE, READONLY
										;memory map - 0x00000068, 0x00000088
		ENTRY							;registers usage
										;r0 - the memory location of the input string data
										;r1 - the memory location of the concatenated strings
										;r2 - temporary storage location for the current loaded byte

		ADR 	r0, STRING1				;load the pointer to memory location of STRING1 to register zero
		ADR 	r1, STRING3				;load the pointer to memory location of ouput STRING3 to register one

LOOP	LDRB 	r2, [r0], #1			;load the first byte from STRING1 to register two and increment the position index
		TEQ		r2, #0					;test if the loaded byte is null and update flags
		BEQ		FINISH 					;branch to end of program if the byte is null
		STRB 	r2, [r1], #1			;store the temporary loaded byte in register two to STRING3 memory location
		B		LOOP					;repeat from beginning again until loaded byte is null

FINISH	MOV		r0, #0					;move a null value into register zero when the string is empty
		STRB	r0, [r1], #1			;store a null value at the end of the concatenated string

INFIN	B		INFIN					;infinite loop for end of program

		AREA 	prog1, DATA, READWRITE

STRING1 DCB "This is a test string1"	;String1
STRING2 DCB "This is a test string2" 	;String2
		space 	64
STRING3 space 	64

		END