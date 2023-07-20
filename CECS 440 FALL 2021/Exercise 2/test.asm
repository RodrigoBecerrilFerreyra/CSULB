.data
    D: .word 0, 0, 0, 0, 0, 0, 0, 0

.text
.globl main
main:

    li $s0, 10 # a
    li $s1, 10 # b
    la $s2, D

    add $t0, $zero, $zero # i = 0
    
    iloop:
        add $t1, $zero, $zero # j = 0

        jloop:
            sll $t2, $t1, 4       # t2 = (j * 4) * 4
            add $t3, $s2, $t2     # t3 holds the adjusted address of D
            
            add $t4, $t0, $t1     # t4 = i + j
            sw $t4, 0($t3)        # D[j * 4] = i + j
            
            addi $t1, $t1, 1      # j++
            slt $t5, $t1, $s1     # check for jloop
            bne $t5, $zero, jloop
        
        addi $t0, $t0, 1  # i++
        slt $t5, $t0, $s0 # check for iloop
        bne $t5, $zero, iloop
    
    # exit
    addi $v0, $zero, 10
    syscall
