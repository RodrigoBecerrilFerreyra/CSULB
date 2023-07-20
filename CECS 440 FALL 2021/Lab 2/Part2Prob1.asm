# Project name: Lab 2
# Author      : Rodrigo Becerril Ferreyra
# Date written: 30 September 2021

.text
.globl main

main:

    # var1 = s0
    # var2 = s1
    # result = s2

    # var1 = 30
    addi $s0, $zero, 30

    # var2 = 210
    addi $s1, $zero, 210

    # function call and usage of return value
    add $a0, $zero, $s0
    add $a1, $zero, $s1
    jal distance
    add $s2, $zero, $v0

    # exit
    addi $v0, $zero, 10
    syscall

distance:
    # a0 = a, a1 = b

    # if b > a then swap
    slt $t0, $a0, $a1        # 1 if a < b, 0 if a >= b
    beq $t0, $zero, skipswap # skip if 0

    add $t0, $zero, $a0
    add $a0, $zero, $a1
    add $a1, $zero, $t0

    skipswap: sub $v0, $a0, $a1
    jr $ra
