# mini-mips
A Small MIPS Simulator

This is a small MIPS Simulator, which displays(simulates) the status of registers, and memory after execution of insructions.

INPUT:
  Syntactically correct .asm files excluding commas.
  Ex: lw $s0 0($t0)
  
OUTPUT:
  Displays the values in registers and memory
  
HOW TO USE:
  Copy or download reader3.cpp file, write a .asm file and keep it in the same directory and compile and run the reader3.cpp file.
  A small asm code(bubble sort) is present as text.asm.
  Command: g++ -o reader3.cpp reader3.out
  Run: reader3.out
  
COMMANDS IMPLEMENTED:
  lui, lw, sw, add, li, addi, slt, j, beq, bne, la, sll.
  
# Contributors:
Vaishnavi- cs18b028<br/>
Darahas- cs18b007<br/>
  
