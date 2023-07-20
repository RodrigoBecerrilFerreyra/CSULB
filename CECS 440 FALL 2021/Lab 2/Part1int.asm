# Project name: Lab 2
# Author      : Rodrigo Becerril Ferreyra
# Date written: 30 September 2021

.data

    var1:   .word 0, 0, 0, 0
    var2:   .word 0, 0, 0, 0
    result: .word 0, 0, 0, 0

.text
.globl main

main:

    # int var1[4] = {7, 18, 11, 3};
    la $s0, var1

    addi $t0, $zero, 7
    sw $t0, 0($s0)
    addi $t0, $zero, 18
    sw $t0, 16($s0)
    addi $t0, $zero, 11
    sw $t0, 32($s0)
    addi $t0, $zero, 3
    sw $t0, 64($s0)

    # int var2[4] = {12, 14, 7, 18};
    la $s1, var2

    addi $t0, $zero, 12
    sw $t0, 0($s1)
    addi $t0, $zero, 14
    sw $t0, 4($s1)
    addi $t0, $zero, 7
    sw $t0, 8($s1)
    addi $t0, $zero, 18
    sw $t0, 12($s1)

    # int result
    la $s2, result

    # from this point on:
    # t0 = i
    # t1 can be (i * 4) or can be (i < 4)
    # t2 = address of var1[i * 4]
    # t3 = address of var2[i * 4]
    # t4 = address of var3[i * 4]
    # t5 = value of *t2
    # t6 = value of *t3
    # t7 = t5 + t6

    # s0 = address of var1
    # s1 = address of var2
    # s2 = address of result

    # int i = 0
    add $t0, $zero, $zero

    loop:
        # loop body

        sll $t1, $t0, 2      # t1 = i * 4

        add $t2, $t1, $s0    # addr of var1[i * 4]
        lw $t5, 0($t2)

        add $t3, $t1, $s1    # addr of var2[i * 4]
        lw $t6, 0($t3)

        add $t4, $t1, $s2    # addr of result[i * 4]

        sub $t7, $t5, $t6    # result[i*4] = var1[i*4] - var2[i*4];
        sw $t7, 0($t4)

        addi $t0, $t0, 1     # i = i + 1

        slti $t1, $t0, 4     # 1 if i < 4
        bne $zero, $t1, loop # branch if (i < 4) is false

    # exit
    addi $v0, $zero, 10
    syscall
