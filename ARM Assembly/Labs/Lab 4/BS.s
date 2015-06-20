			AREA bubbleSort, CODE, READONLY
			ENTRY
;----------------------------------------------------

main		ADR SP, regis		;get pointer to register stack
			ADR r0,a  			;r0 is a pointer to array a
			ADR r1,endOfArray ;address at the end of the array
			SUB r1,r1,r0      ;number of the array bytes
			ASR r1,#2         ;r1: length of the array,i.e., n

			MOV r2,#0         ;r2: outer loop counter,i.e., i
			SUB r4,r1,#1      ;r4 is (n - 1)
startOuter	CMP r2,r4         ;compare i with (n - 1) 
			BGE endOuter      ;if i >= (n - 1), then exit the outer loop
			MOV r3,#0         ;r3 is the inner loop counter, i.e., j
			SUB r5,r4,r2      ;r5 is (n - 1 - i)
startInner	CMP r3,r5         ;compare j with (n - 1 - j) 
			BGE endInner      ;if j >= (n - 1 -j), then exit the inner loop
			ADD r6,r0,r3,LSL#2;r6 is a pointer to a[j]
			ADD r7,r6,#4      ;r7 is a pointer to a[j+1]
			BL  sortTwo       ;call sortTwo(*a[j],*a[j+1])
			ADD r3,r3,#1      ;increment inner counter j
			B   startInner    ;loop again (inner loop)
endInner	ADD r2,r2,#1      ;increment outer counter i
			B   startOuter    ;loop again (outer loop)
endOuter	B endOuter

sortTwo		STMFA SP!,{r0-r4,r6,r7,LR} ;store the registers we use on the stack
			LDR r0, [SP, #-4]		 ;get address to y
			LDR r1, [r0]			 ;get y
			LDR r2, [SP, #-8]		 ;get address to x
			LDR r3, [r2]			 ;get x
			CMP r1, r3				 ;compare y and x
swap		MOVMI r4, r3			 ;IF y < x, store x in temp
			STRMI r1, [r2]			 ; store y in x's place in memory
			STRMI r4, [r0]			 ; store temp in y's place in memory
			LDMFA SP!,{r0-r4,r6,r7,PC} ;load back the registers from stack

;----------------------------------------------------
			AREA bubbleSort, DATA, READWRITE

a         	DCD 44,-56,3,65,-8,32,6,-87,54,65,87,32,65
endOfArray	SPACE 1
			ALIGN
regis		SPACE 128
;----------------------------------------------------

			END