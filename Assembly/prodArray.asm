# "prodArray" in MIPS assembly
# Eric Bachmeier
# 250738776

	# Memory structures
	.data
A:	.word	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
n:	.word	16

	.text
	# Declare main as a global function
	.globl	main

main:
	la	 $a0, A				# Load in A from memory structures
	lw 	 $a1, n				# Load in n from memory structures
	jal	 prodArray			# prodArray(A, n)
	move $s0, $v0			# Store most significant bits in $s0
	move $s1, $v1			# Store least significant bits in $s1
	
	li	 $v0, 10			# System call code for exit (10)
	syscall

prodArray:
	addi $sp, $sp, -20		# Make room on the stack for 5 registers
	sw	 $ra, 16($sp)		# Save the return address on the stack
	sw	 $s3, 12($sp)		# Save n parameter on the stack
	sw	 $s2,  8($sp)		# Save A parameter on the stack
	sw	 $s1,  4($sp)		# Save $s1 on the stack to store left
	sw	 $s0,  0($sp)		# Save $s0 on the stack to store mid

	move $s2, $a0			# Store A in $s2
	move $s3, $a1			# Store n in $s3
	lw	 $t0, 0($s2)		# Store A[0] in $t0
	slti $t1, $s3, 2		# if n >= 2
	beq	 $t1, $zero, comp	# $t1 will be 0 and we branch to comp function
	move $v0, $zero			# if n < 2 return 0x0 in register for most significant bits
	
	beq	 $s3, $zero, done	# if !n branch to done else branch to fact

fact:
	move $v1, $t0			# Return A[0]
	j	 exit

done:
	move $v1, $zero			# Return 0
	j	 exit

comp:
	srl  $s0, $s3, 1		# Store n / 2 in mid
	move $a0, $s2			# Store argument A
	move $a1, $s0			# Store argument mid
	jal	 prodArray			# Recursive call prodArray(A, mid)
	move $s1, $v1			# Store prodArray(A, mid) in left
	sll	 $t2, $s0, 2		
	add	 $a0, $s2, $t2		# Store A + mid in $a0
	sub	 $a1, $s3, $s0		# Store n - mid in $a1
	jal	 prodArray			# Recursive call for right, prodArray(A + mid, n – mid)
	mult $s1, $v1			# Left * right
	mfhi $v0				# Return left * right value
	mflo $v1
	j 	 exit

exit:
	lw	 $s0, 0($sp)		# Restore mid value from stack
	lw	 $s1, 4($sp)		# Restore left value from stack
	lw	 $s2, 8($sp)		# Restore A value from stack
	lw	 $s3, 12($sp)		# Restore n value from stack
	lw	 $ra, 16($sp)		# Restore return address from stack
	addi $sp, $sp, 20		# Restore stack pointer
	jr	 $ra				# Return to routine caller
