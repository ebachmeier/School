		AREA 	prog1, CODE, READONLY
			
		ENTRY
		
TRUE	EQU		0xFFFFFFFF			;value for r2 if the program finds x in the list
FALSE	EQU		0xF0F0F0F0			;value for r2 if the program failed to find x
		
		ADR		r0, x				;load the memory address of data x
		LDR		r0, [r0]			;load the data value into r0
		ADR 	r3, List			;load the memory address of the beginning of the linked list to r3
		MOV		r2, #0				;set r2 to the null character to find the end of the list
		
LOOP	LDR		r1, [r3, #4]		;load the current value of the list into r1
		TEQ		r1, r0				;test if the current value is equal to x
		LDREQ	r2, =TRUE			;if equal, set r2 to the TRUE value and branch to the end loop
		BEQ		INFIN
		LDR		r3, [r3]			;load the next linked element from the address of the previous
		TEQ		r2, r3				;check if it is the end of the linked list
		BNE		LOOP				;continue to next element if not at end of list
		LDR		r2, =FALSE			;if we reach the end of the list, we failed to find x
									;move TRUE value to r2
INFIN	B		INFIN				;end of program infinnite loop

		AREA	prog1, DATA, READWRITE
			
List  	DCD 	Item5, 0x12341111
Item2 	DCD 	Item3, 0x12342222 
Item3 	DCD 	Item4, 0x12343333 
Item4 	DCD 	Item6, 0x12344444
Item5 	DCD 	Item2, 0x12345555 
Item6 	DCD 	Item7, 0x12346666 
Item7 	DCD 	0x00,  0x12347777 	;terminator
x		DCD		0x12345555			;value to search linked list for
	
		END