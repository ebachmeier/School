		AREA 	prog2, CODE, READONLY
				
		ENTRY						;memory map result - 0x000000C0

X		EQU		2
N   	EQU 	5
		
		ADR   	SP, stack      		;define the stack from memory space
		MOV   	r0, #X        		;prepare the parameter X
		MOV		r1, #N				;prepare parameter N
		
		STR   	r1, [SP,#-4]! 		;push the parameter N to the stack
		STR		r0, [SP,#-4]!		;push the parameter X to the stack
		SUB   	SP, #4      		;reserve a place in the stack for the return value
		BL    	POWER         		;branch with link to the subroutine

		LDR  	r0, [SP], #4 	  	;load result back to r0, popping from stack
		ADD		SP, #4              ;remove the parameter from the stack memory
		ADR   	r1, result     		;get the memory address of the result variable
		STR   	r0, [r1]       		;store the final answer in the result variable

INFIN 	B     	INFIN          		;infinite loop for end of program

POWER 	STMFD 	SP!,{r0-r3,FP,LR}	;push general use registers, frame pointer, and linked register to the stack
		MOV   	FP,SP         		;set the frame pointer for the current function call
			
		LDR   	r0, [FP,#0] 		;get the parameter X from the stack
		LDR		r1, [FP,#4]         ;get the parameter N from the stack

		CMP   	r1, #0         		;if (n == 0) {
		BNE		ONE					;if not zero, branch to check one
		MOV		r2, #1				;prepare the value to be returned
		STR		r2, [FP,#24]		;store the return value to the stack
		B		RET					;branch to the return section of the subroutine
                                    ;}
ONE		CMP		r1, #1				
		BNE		EVEN
		MOV		r2, r0				;make the result x if n is down to 1
		STR		r2, [FP,#24]		;store the return value to the stack
		B		RET					;branch to return section
		
EVEN	TST		r1, #1				;if (n & 1) {
		BNE		ODD					;branch to ODD check if number is odd
		MOV		r1, r1, LSR#1		;divide N by 2 with a logical right shift
		STR		r0, [SP,#-4]!		;store the updated X value to the top of the stack
		STR		r1, [SP,#-4]!		;store the updated N value to the top of the stack
		SUB		SP, #4				;reserve room for the return value in return frame
		BL 		POWER				;make a recursive call with X and N as parameters
		LDR		r2, [SP], #4		;load the result and pop it from the stack
		MOV		r3, r2				;store the return value in temporary register location
		MUL		r2, r3, r2			;square the return value
		STR		r2, [FP,#24]		;store the return value to the stack
		B		RET					;branch to return section
                                    ;}

                                    ;else {
ODD		SUB		r1, r1, #1			;subtract one from N param
		STR		r0, [SP,#-4]!		;store the updated X value to the top of the stack
		STR		r1, [SP,#-4]!		;store the updated N value to the top of the stack
		SUB		SP, #4				;reserve room for the return value
		BL 		POWER				;make a recursive call with x and n - 1 as parameters
		LDR		r2, [SP], #4		;load the result and pop it from the stack
		MUL		r2, r0, r2			;multiply the resulting value with x
		STR		r2, [FP,#24]		;store the return value to the stack
                                    ;}

RET  	MOV   	SP,FP         		;collapse all parts of the working stack
		LDMFD 	SP!,{r0-r3,FP,PC}   ;load all saved registers back and return to last program counter position

		AREA 	prog2, DATA, READWRITE
		 
result 	DCD   	0x00        		;the final result memory location
		SPACE 	0xFF       			;declare space for stack
stack  	DCD   	0x00        		;initial stack position

		END