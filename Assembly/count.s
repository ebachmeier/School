		AREA 	prog2, CODE, READONLY
										;memory map - 0x000000C0, 0x000000E0
		ENTRY							;registers usage
										;r0 - stores the input string from data
										;r1 - stores the memory location of the output string
										;r2 - stores the array of letter values in hex
										;r3 - stores the current byte from the STRING1
										;r4 - counter for the position in the string 
										;r5 - counter for position in the letter values array VALS

		ADR 	r0, STRING1				;load STRING1 into register zero
		ADR 	r1, STRING2				;load memory location of the output string into register one
		ADR 	r2, VALS				;load the memory location of the array of letter values for "the" to register two
		B 		LOOP					;branch to main body of program
		
BACK	SUB		r1, r1, #1				;decrement the string pointer back one spot to remove the successfully stored "t"
LOOP	LDRB 	r3, [r0], #1			;load the first byte from STRING1 to register three, and increment the position index
		TEQ		r3, #0					;test if the current byte is null, set flags
		BEQ		FINISH					;branch to the end of the program if the byte is null
		STRB 	r3, [r1], #1			;store the byte in the new string memory location, and increment the position index
		TEQ		r3, #116				;test if the byte is a letter "t"
		BNE		LOOP					;branch back to repeat LOOP if it is not

		MOV		r4, #0					;set the string position index to zero
		MOV		r5, #4					;setting array counter to the next element, four bytes after
CHK		TEQ		r4, #3					;test if counter has reached three ("the" has been found)
		ADDEQ	r0, r0, #3				;increment string counter by three to skip over the occurence of the word
		BEQ		BACK					;branch back to loop if word found
		LDRB 	r3, [r0, r4]			;load the next byte from the string to register three
		LDR		r6, [r2, r5]			;load the next letter value from the VALS array to register six
		TEQ		r3, #0					;test if the current byte is a null, set flags
		SUBEQ	r1, r1, #1				;decrement the string pointer by one to get rid of the stored "t"
		BEQ		LAST					;if it is, branch to end of program
		TEQ		r3, r6					;test if the letters are the same
		BNE		LOOP					;if they are not, branch back to LOOP to continue search
		ADD		r4, #1					;increment the string position by one
		ADD		r5, #4					;increment to the next letter of the VALS array
		B		CHK						;branch back CHK to check next byte
		B		FINISH
		
LAST	TEQ		r6, #32
		ADDNE	r1, r1, #1
		BNE		LOOP

FINISH	STRB	r3, [r1]				;store the last byte in the STRING2 memory location
		
INFIN	B		INFIN					;infinite loop for end of program

		AREA 	prog2, DATA, READWRITE

STRING1 DCB 	"they all the abc th the"
		space 	32
VALS	DCD		116, 104, 101, 32		;values of "t", "h", "e", and a space in sequence
		space 	16
STRING2 space 	32

		END