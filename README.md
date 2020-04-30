# Mini-Mips
A Small MIPS Simulator

This is a small MIPS Simulator, which displays(simulates) the status of registers, and memory after execution of insructions.

INPUT:<br/>
  Syntactically correct .asm files excluding commas.<br/>
  Ex: lw $s0 0($t0)
  
OUTPUT:<br/>
  Displays the values of registers, memory, no. of latches, clock cycles taken to complete.
  
HOW TO USE:<br/>
  Copy or download reader.cpp file, write a .asm file and keep it in the same directory and compile and run the reader1.cpp file.<br/>
  A small asm code(bubble sort) is present as text.asm.<br/>
  Command: g++ -o reader1.cpp reader1.out<br/>
  Run: reader1.out
  
COMMANDS IMPLEMENTED:<br/>
  lui, lw, sw, add, li, addi, slt, j, beq, bne, la, sll.<br/>

# Extra feature added:
Data-Forwarding, No of latches, Pipelining.
  
# Contributors:
Vaishnavi- cs18b028<br/>
Darahas- cs18b007<br/>