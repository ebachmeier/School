		AREA 	prog2, CODE, READWRITE
		
		;Registers usage
		;r0 - will store the result of valid (1) or invalid (0)
		;r1 - stores the left hand pointer
		;r2 - stores the right hand pointer
		;r3 - stores the byte while moving the right pointer to end
		;r4 - stores the left byte from the palindrome string
		;r5 - stores the right byte from the palindrome string
		
		ENTRY
		
		MOV		r0, #0							;set r0 flag up for invalid palindrome
		LDR		r1, =STRING						;r1 points to start of string we are testing
		MOV		r2, r1							;copy left pointer to right pointer in r2
		
Loop	LDRB	r3, [r2], #1					;get character and update right pointer

		CMP		r3, #0							;repeat until end of string
		BNE 	Loop
		SUB 	r2, r2, #2						;right pointer fixed to point to end of string
		B		Pal								;branch to Pal routine
		
Pal		MOV		r0, #0							;set invalid flag for palindrome

Left	LDRB	r4, [r1], #1					;get left character
		CMP		r4, #0x40						;check if the loaded byte in r4 is greater than '@' symbol (0x40)
		BGT		UpL								;branch to check the upper limit if the byte is greater
		B		Left 							;branch to next character if byte is lower or equal
UpL		CMP		r4, #0x7B						;check if the loaded byte is less than to '{' symbol (0x7B)
		BLT		Upper							;branch to the upper case check if the byte is lower
		B		Left							;branch to next character if the byte is greater or equal
Upper	CMP		r4, #0x5B						;check if the loaded byte is an upper case leter
		BGE		Lower							;branch to lower case check if its not upper
		BLT		LCon							;branch to conversion if the byte is lower or equal
Lower	CMP		r4, #0x60						;check if the loaded byte is a lower case letter
		BLE		Left							;branch to next character if it is not a letter
		BGT		LCon							;branch to conversion if the byte is greater
LCon	CMP		r4, #0x5B						;compare the loaded byte with the '[' symbol
		ADDLT	r4, #0x20						;make it a lower case letter if its a capital
		
Right	LDRB	r5, [r2], #-1					;get right character
		CMP		r5, #0x40						;check if the loaded byte in r5 is greater than '@' symbol (0x40)
		BGT		UpR								;branch to check the upper limit if the byte is greater
		B		Right 							;branch to next character if byte is lower or equal
UpR		CMP		r5, #0x7B						;check if the loaded byte is less than to '{' symbol (0x7B)
		BLT		Up								;branch to the upper case check if the byte is lower
		B		Right							;branch to next character if the byte is greater or equal
Up		CMP		r5, #0x5B						;check if the loaded byte is an upper case leter
		BGE		Low								;branch to lower case check if its not upper
		BLT		RCon							;branch to conversion if the byte is lower or equal
Low		CMP		r5, #0x60						;check if the loaded byte is a lower case letter
		BLE		Right							;branch to next character if it is not a letter
		BGT		RCon							;branch to conversion if the byte is greater
RCon	CMP		r5, #0x5B						;compare the loaded byte with the '[' symbol
		ADDLT	r5, #0x20						;make it a lower case letter if its a capital
		
		CMP 	r4, r5							;compare the ends of the string
		BNE		No								;branch to No if they differ
		CMP		r1, r2							;if they are equal the palindrome has odd length
		BEQ		Yes								;if they are the same, branch to Yes	
		ADD		r3, r1, #1						;copy left pointer to r3 and add 1
		CMP		r3, r2							;even length palindrome
		BEQ		Yes								;if left pointer past right pointer then branch Yes
		B		Left							;repeat loop for Pal until branched out
		B		No

Yes		MOV		r0, #1							;set r0 for vaid palindrome

No		B		No								;infinite loop to retrieve data

STRING 	DCB 	"race.car?" 					;string

		END										;end of program
