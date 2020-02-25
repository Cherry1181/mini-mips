.data 
size:
.word 11
array:
.word 5 6 3 2 9 12 11 4 7 10 0
newline:
    .asciiz "\n"
.text
.globl main
main:
     la $s0 array
     la $t0 size
     addi $k0 $0 0
     lw $t0 0($t0)
     whilei: beq $k0 $t0 exiti
             addi $k1 $0 0
             addi $s8 $k0 1
             sub $s8 $t0 $s8
             whilej: beq $k1 $s8 exitj
                     sll $t8 $k1 2
                     addi $t9 $t8 4
                     add $t8 $t8 $s0
                     add $t9 $t9 $s0
                     lw $s1 0($t8)
                     lw $s2 0($t9)
                     slt $t1 $s1 $s2
                     beq $t1 $0 swap
                     bne $t1 $0 addj
                     swap: sw $s1 0($t9)
                           sw $s2 0($t8)  
                     addj: addi $k1 $k1 1
                           j whilej
             exitj:  addi $k0 $k0 1
                     j whilei
             exiti: addi $s7 $0 0
                    print: beq $s7 $t0 exit
                           sll $s6 $s7 2
                           add $s6 $s0 $s6
                           li $v0 1
                           lw $a0 0($s6)
                           syscall
                           addi $s7 $s7 1
                           j print
                     exit: 
             exiti: jr $ra
