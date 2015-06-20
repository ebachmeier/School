;--------------------------------------------------------------------------------
     AREA factorial, CODE, READONLY
n    EQU 3
     ENTRY
Main ADR   sp,stack      ;define the stack

     MOV   r0, #n        ;prepare the parameter
     STR   r0,[sp,#-4]!  ;push the parameter on the stack

     SUB   sp,sp,#4      ;reserve a place in the stack for the return value

     BL    Fact          ;call the Fact subroutine

     LDR   r0,[sp],#4    ;load the result in r0 and pop it from the stack
     ADD   sp,sp,#4      ;also remove the parameter from the stack

     ADR   r1,result     ;get the address of the result variable
     STR   r0,[r1]       ;store the final result in the result variable

Loop B     Loop          ;infinite loop
;--------------------------------------------------------------------------------
     AREA factorial, CODE, READONLY
Fact STMFD sp!,{r0,r1,r2,fp,lr} ;push general registers, as well as fp and lr
     MOV   fp,sp         ;set the fp for this call
     SUB   sp,sp,#8      ;create space for the x and y local variables

     LDR   r0,[fp,#0x18] ;get the parameter from the stack

     ADD   r1,r0,#10     ;calculate the x value
     STR   r1,[fp,#-0x8] ;update the value of the local variable x

     SUB   r1,r0,#10     ;calculate the y value
     STR   r1,[fp,#-0x4] ;update the value of the local variable y

     CMP   r0,#1         ;if (n <= 1)
     MOVLE r0,#1         ;{ prepare the value to be returned
     STRLE r0,[fp,0x14]  ;  store the returned value in the stack
     BLE   ret           ;  branch to the return section 
                         ;}

     SUB   r1,r0,#1      ;{ prepare the new parameter value
     STR   r1,[sp,#-4]!  ;  push the parameter on the stack

     SUB   sp,sp,#4      ;  reserve a place in the stack for the return value

     BL    Fact          ;  call the Fact subroutine     	 

     LDR r1,[sp],#4      ;  load the result in r0 and pop it from the stack
     ADD sp,sp,#4        ;  remove also the parameter from the stack

     MUL   r2,r0,r1      ;  prepare the value to be returned
     STR   r2,[fp,#0x14] ;  store the returned value in the stack
                         ;}

ret  MOV   sp,fp         ;collapse all working spaces for this function call
     LDMFD sp!,{r0,r1,r2,fp,pc} ;load all registers and return to the caller
;--------------------------------------------------------------------------------
     AREA factorial, DATA, READWRITE
result DCD   0x00        ;the final result
       SPACE 0xB4       ;declare the space for stack
stack  DCD   0x00        ;initial stack position (FD model)
;--------------------------------------------------------------------------------
       END