.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

fact:
  li $t0, 1
  move $t1, $t0
  li $t2, 1
  move $t3, $t2
  sw $t1, -4($fp)
  addi $sp, $sp, -4
  sw $t3, -8($fp)
  addi $sp, $sp, -4
l1:
  lw $t1, -8($fp)
  lw $t3, 0($fp)
  sw $t1, -8($fp)
  sw $t3, 0($fp)
  ble $t1, $t3, l2
  j l3
l2:
  lw $t1, -4($fp)
  lw $t3, -8($fp)
  mul $t4, $t1, $t3
  move $t1, $t4
  li $t5, 1
  add $t6, $t3, $t5
  move $t3, $t6
  sw $t1, -4($fp)
  sw $t3, -8($fp)
  sw $t4, -12($fp)
  addi $sp, $sp, -4
  sw $t6, -16($fp)
  addi $sp, $sp, -4
  j l1
l3:
  lw $t1, -4($fp)
  move $v0, $t1
  jr $ra

main:
  move $fp, $sp
  addi $sp, $sp, -20
  sw $zero, 0($sp)
  sw $zero, -4($sp)
  sw $zero, -8($sp)
  sw $zero, -12($sp)
  sw $zero, -16($sp)
  li $t0, 0
  move $t1, $t0
  li $t2, 5
  move $t3, $t2
  sw $t1, -24($fp)
  addi $sp, $sp, -4
  sw $t3, -28($fp)
  addi $sp, $sp, -4
l4:
  lw $t1, -24($fp)
  lw $t3, -28($fp)
  sw $t1, -24($fp)
  sw $t3, -28($fp)
  blt $t1, $t3, l5
  j l6
l5:
  lw $t1, -24($fp)
  li $t3, 4
  mul $t4, $t1, $t3
  la $t5, -20($fp)
  add $t6, $t5, $t4
  li $t7, 2
  add $s0, $t1, $t7
  sw $s0, 0($t6)
  li $s1, 4
  mul $s2, $t1, $s1
  la $s3, -20($fp)
  add $s4, $s3, $s2
  lw $s5, 0($s4)
  sw $t1, -24($fp)
  sw $t4, -32($fp)
  addi $sp, $sp, -4
  sw $t5, -36($fp)
  addi $sp, $sp, -4
  sw $t6, -40($fp)
  addi $sp, $sp, -4
  sw $s0, -44($fp)
  addi $sp, $sp, -4
  sw $s2, -48($fp)
  addi $sp, $sp, -4
  sw $s3, -52($fp)
  addi $sp, $sp, -4
  sw $s4, -56($fp)
  addi $sp, $sp, -4
  sw $s5, -60($fp)
  addi $sp, $sp, -4
  sw $fp, -64($fp)
  addi $sp, $sp, -4
  sw $ra, -68($fp)
  addi $sp, $sp, -4
  lw $t1, -60($fp)
  sw $t1, -72($fp)
  addi $sp, $sp, -4
  move $fp, $sp
  jal fact
  move $sp, $fp
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  lw $fp, 4($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 4
  lw $t1, -24($fp)
  lw $t4, -32($fp)
  lw $t5, -36($fp)
  lw $t6, -40($fp)
  lw $s0, -44($fp)
  lw $s2, -48($fp)
  lw $s3, -52($fp)
  lw $s4, -56($fp)
  lw $s5, -60($fp)
  move $s6, $v0
  move $a0, $s6
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  li $s7, 1
  add $t8, $t1, $s7
  move $t1, $t8
  sw $t1, -24($fp)
  sw $t4, -32($fp)
  sw $t5, -36($fp)
  sw $t6, -40($fp)
  sw $s0, -44($fp)
  sw $s2, -48($fp)
  sw $s3, -52($fp)
  sw $s4, -56($fp)
  sw $s5, -60($fp)
  sw $s6, -64($fp)
  addi $sp, $sp, -4
  sw $t8, -68($fp)
  addi $sp, $sp, -4
  j l4
l6:
  li $t1, 0
  move $v0, $t1
  jr $ra
