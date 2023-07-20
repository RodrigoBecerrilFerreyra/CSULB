# Simple input/output in MIIPS assembly


	# Start .text segment (program code)
	.text
	
	.globl	main
main:
	# Print string msg1
	li	$v0,4		# print_string syscall code = 4
	la	$a0, msg1	# load the address of msg
	syscall

	# Get input A from user and save
	li	$v0,5		# read_int syscall code = 5
	syscall	
	move	$t0,$v0		# syscall results returned in $v0

	# Print string msg2
	li	$v0,4		# print_string syscall code = 4
	la	$a0, msg2	# load the address of msg2
	syscall

	# Get input B from user and save
	li	$v0,5		# read_int syscall code = 5
	syscall	
	move	$t1,$v0		# syscall results returned in $v0

    # --------------------------------------------------

	# Math!
	add	$t3, $t0, $t1	# A = A + B

	# Print string msg3
	li	$v0, 4
	la	$a0, msg3
	syscall

	# Print sum
	li	$v0,1		# print_int syscall code = 1
	move	$a0, $t3	# int to print must be loaded into $a0
	syscall
    
    # --------------------------------------------------
    
    or $t3, $t0, $t1
    
    # Print string msg4
	li	$v0, 4
	la	$a0, msg4
	syscall

	# Print sum
	li	$v0,1		# print_int syscall code = 1
	move	$a0, $t3	# int to print must be loaded into $a0
	syscall
    
    # --------------------------------------------------
    
    and $t3, $t0, $t1
    
    # Print string msg5
	li	$v0, 4
	la	$a0, msg5
	syscall

	# Print sum
	li	$v0,1		# print_int syscall code = 1
	move	$a0, $t3	# int to print must be loaded into $a0
	syscall

	li	$v0,10		# exit
	syscall

	# Start .data segment (data!)
	.data
msg1:	.asciiz	"Enter A: "
msg2:	.asciiz	"Enter B: "
msg3:	.asciiz	"\nA + B = "
msg4:   .asciiz "\nA | B = "
msg5:   .asciiz "\nA & B = "
