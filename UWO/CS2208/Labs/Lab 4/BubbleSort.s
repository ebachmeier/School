			AREA bubbleSort, CODE, READONLY
			ENTRY
;----------------------------------------------------
true		EQU 1				;boolean
false		EQU 0

			ADR	r12, regis		;set up register stack
			ADR	SP, stack		;set up stack pointer
			ADR	FP, stack		;set up frame pointer
			B main				;jump to the main function 


main		ADR r0, a			;r0 is a pointer to array a
			ADR r1, endOfArray 	;address at the end of the array
			SUB r1, r1, r0		;number of the array bytes
			ASR r1, #2			;r1: length of the array,i.e., n

			ADD	SP, SP, #4		;create stack frame: move SP down
			STR	FP, [SP]		;push the frame pointer on the stack
			MOV	FP, SP			;the frame pointer points at the base

			MOV r2, #0			;r2: outer loop counter,i.e., i
			SUB r4, r1, #1		;r4 is (n - 1)

startOuter	CMP r2, r4			;compare i with (n - 1) 
			BGE endOuter		;if i >= (n - 1), then exit the outer loop
			MOV r3, #0			;r3 is the inner loop counter, i.e., j
			MOV r8, #false		;r8: swap flag
			SUB r5, r4, r2		;r5 is (n - 1 - i)

startInner	CMP r3, r5			;compare j with (n - 1 - j)
			BLT continue		; IF j < (n - 1 - j), continue
			CMPGE r8, #true		; ELSE, is swap flag true
			BEQ	endInner		;  IF swap flag is true, exit inner loop
			BNE endOuter		;  ELSE, exit the outer loop
			
continue	ADD r6, r0, r3,LSL#2;r6 is a pointer to a[j]
			ADD r7, r6, #4		;r7 is a pointer to a[j+1]
			
			STR	r7, [SP, #4]!	;put *a[j+1]in stack frame
			STR	r6, [SP, #4]!	;put *a[j] in stack frame
			BL sortTwo			;call sortTwo(*a[j],*a[j+1])
			MOV	SP, FP			;collapse frame: restore SP
			
			ADD r3,	r3,	#1		;increment inner counter j
			MOVMI r8, #true		;IF we swapped, set swap flag to true
			B startInner		;loop again (inner loop)

endInner	ADD r2,	r2	,#1		;increment outer counter i
			B startOuter		;loop again (outer loop)

endOuter	LDR	FP, [FP]		;restore old frame pointer from stack
			SUB SP, SP, #4		;move stack pointer down 4 bytes

endMain		B endMain

sortTwo		STMEA r12!,{r0-r3}	;store contents of registers we use (r0-r3) on the stack
			ADD	SP, SP, #4		;create stack frame: increment SP
			STR	FP, [SP]		;push the frame pointer on the stack
			MOV	FP, SP			;the frame pointer points at the base
			ADD	SP, SP, #4		;move SP down 4 bytes for temp

			LDR	r0, [FP, #-4]	;get address of parameter x
			LDR	r1, [r0]		;get value of parameter x

			LDR	r2, [FP, #-8]	;get address of parameter y
			LDR	r3, [r2]		;get value of parameter y
			
			CMP r3, r1			;compare *y and *x
								;IF *y < *x
swap		STRMI r1, [FP, #4]	; store parameter x in temp in stack frame
			STRMI r3, [r0]		; store parameter y in parameter x
			LDRMI r3, [FP, #4]	; get temp
			STRMI r3, [r2]		; store temp in y
			
			MOV	SP, FP			;collapse stack frame: restore SP
			LDR	FP, [FP]		;restore old frame pointer from stack
			SUB	SP, SP, #4		;move stack pointer up 4 bytes
			LDMEA r12!, {r0-r3}	;restore registers to original values from stack
			MOV PC, LR			;copy link register into PC and return

;----------------------------------------------------
			AREA bubbleSort, DATA, READWRITE

a			DCD 44, -56, 3, 65, -8, 32, 6, -87, 54, 65, 87, 32, 65
;a			DCD 1, 2, 3, 4, 5, 6, 7, 8
endOfArray	SPACE 1
			ALIGN
regis		SPACE 16
stack		SPACE 1024
;----------------------------------------------------

			END
 
