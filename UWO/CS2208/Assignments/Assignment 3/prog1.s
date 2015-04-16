		AREA 	prog1, CODE, READWRITE
			
		;Registers usage
		;r0 - the contents of the UPC address are loaded here
		;r1 - used as a pointer to the odd integers of the UPC
		;r2 - used as a pointer to the even integers of the UPC
		;r3 - used to store the odd byte loaded from the UPC
		;r4 - used to store the even byte loaded from the UPC
		;r5 - used to store the sum of the odd integers from the UPC
		;r6 - used ot store the sum of the even
		
		ENTRY
		
		MOV		r1, #0				;load the value of zero into register one
		MOV		r2, #1				;load the value of one into register two
		LDR		r0, =UPC			;load the contents of memory address of UPC to register zero
		
		LDRB	r3, [r0, r1]		;loads a byte from memory location r0 at position of pointer r1 into register three
		SUB		r3, r3, #48			;change the ASCII value of the byte to an integer value
		ADD		r5, r5, r3			;add the odd integer to the odd sum in register five
		ADD		r1, r1, #2			;increment the pointer r1 by 2
		
Loop	LDRB	r3, [r0, r1]		;loads a byte from memory location r0 at position of pointer r1 into register three
		LDRB	r4, [r0, r2]		;loads a byte from memory location r0 at position of pointer r2 into register four
		
		SUB		r3, r3, #48			;change the ASCII value of the byte to an integer value
		SUB		r4, r4, #48			;change the ASCII valur of teh byte to an integer value
		
		ADD		r5, r5, r3			;add the odd integer to the odd sum in register five
		ADD		r6, r6, r4			;add the even integer to the even sum in register six
		
		ADD		r1, r1, #2			;increment the pointer r1 by 2
		ADD		r2, r2, #2			;increment the pointer r2 by 2
		
		CMP		r1, #12				;compares r1 and 12 to check if 12 integers have already been stored
		BNE		Loop				;branches back to Loop if CMP subtraction is not equal to zero

		LDRB	r4, [r0, r2]		;loads check digit byte to r4
		SUB		r4, r4, #48			;change the ASCII value of the byte to an integer value
										
		ADD		r5, r5, LSL #1		;multiply r5 total by 3 using logical shift left

		ADD		r1, r5, r6			;adds the odds(mult. by 3) and the evens together into register one
		SUB		r1, r1, #1			;subtract one from the total sum in register one
		MOV		r0, #0				;clears register zero before entering Mod10 loop
		B		Mod10				;branch to Mod10
		
Mod10	CMP		r1, #9				;compares r1 value with 9 to see if it is less than 10
		SUBGT	r1, r1, #10			;subtract 10 from r1 value if r1 is still greater than 9
		MOVLT	r0, #1				;give register zero a value of one if r1 is less than 10
		CMP 	r0, #1				;checks if r1 was less than 10
		BNE		Mod10				;branch back to Mod10 if r1 is still greater than 9

		RSB		r1, r1, #9			;subtract from 9 to have calculated check digit in r1
		CMP 	r1, r4				;compare to check if the final r1 value is equal to the check digit

		BEQ		Yes					;branch to Yes if the UPC is valid
		MOV		r0, #0				;if not valid, put a 0 in register 0
		BNE		No					;branch to No if the UPC is not  valid
		
Yes		MOV		r0, #1				;set the value of register zero to one for valid UPC

No		B		No					;infinite loop to retrieve data

UPC		DCB		"013800120738"		;UPC string

		END							;end of program
			
