# ARM Assembly Machine Emulator

## Overview  
This project implements a simplified ARM assembly emulator in C++. It reads assembly instructions from an input file, parses them, and executes them by simulating a CPU register system and instruction set.

The emulator models key aspects of ARM architecture, including registers, arithmetic/logic operations, bitwise instructions, and condition flags.

---

## Features  
- Emulates ARM-style registers:
  - General-purpose registers (R0–R12)
  - Special registers (SP, LR, PC)
- Parses and executes assembly instructions from an input file  
- Supports multiple instruction types:
  - Data movement (MOV, MOVS)
  - Arithmetic (ADD, ADDS, SUB, SUBS)
  - Bitwise operations (AND, ORR, XOR)
  - Shift operations (LSL, LSR)
  - Bitwise NOT operations  
- Maintains and updates condition flags:
  - Negative (N)
  - Zero (Z)
  - Carry (C)
  - Overflow (V)
- Outputs register state and flags after each instruction  

---

## Technologies Used  
- C++  
- File I/O and string parsing  
- STL containers (`std::map`, `std::string`, streams)  
- Bitwise operations and low-level data manipulation  

---

## Key Concepts Demonstrated  
- Low-level system design and CPU simulation  
- Instruction parsing and execution pipelines  
- Register-based computation models  
- Bitwise logic and flag manipulation  
- Emulation of real-world architecture behavior  

---

## Example Input  
MOV R1, #0x72DF9901
MOV R2, #0x2E0B484A
ADDS R3, R1, R2
SUBS R4, R3, R2

---

## Example Output  
R0: 0x0 R1: 0x72df9901 R2: 0x2e0b484a ...
N = 0 Z = 0 C = 0 V = 0


---

## How It Works  
1. Reads instructions from an input file  
2. Parses opcodes, registers, and operands  
3. Executes instructions using a simulated machine state  
4. Updates registers and condition flags accordingly  
5. Prints the updated system state after each instruction  

---

## What I Learned  
- How low-level architectures execute instructions  
- How to simulate a CPU execution model in software  
- The role of registers and condition flags in computation  
- How parsing and execution layers interact in a system  
- How bitwise operations impact system-level behavior  

---

## Future Improvements  
- Support for additional ARM instructions (CMP, TST, branching)  
- Implement memory addressing and load/store operations  
- Add a program counter flow (branching and jumps)  
- Improve instruction parsing robustness  
- Build a simple UI or debugger-style step-through mode  

---

## Summary  
This project demonstrates a foundational understanding of computer architecture by simulating how an ARM processor interprets and executes instructions at a low level.
