# Vole Machine Simulator

## Overview
The Vole Machine Simulator is a C++ program that emulates the functionality of a simple virtual machine called the "Vole Machine." It includes components such as registers, memory, an Arithmetic Logic Unit (ALU), and a Control Unit (CU) to execute a set of predefined instructions.

## Features
- **Memory**: 256 memory locations, each storing a 2-digit hexadecimal value.
- **Registers**: 16 general-purpose registers (R0 to R15), each storing a 2-digit hexadecimal value.
- **ALU**: Supports arithmetic, logical, and bitwise operations, including floating-point arithmetic.
- **Instruction Set**: Supports operations like load/store, arithmetic, logical, and control flow instructions.
- **Input/Output**: Instructions can be loaded from a file or entered manually via the console. Results are saved to `MemoryFile.txt` and `RegFile.txt`.

## Components
1. **Machine**: The main class that orchestrates the simulation, including fetching, decoding, and executing instructions.
2. **Register**: Manages the 16 registers.
3. **Memory**: Manages the 256 memory locations.
4. **ALU**: Handles arithmetic, logical, and conversion operations.
5. **CU (Control Unit)**: Executes instructions by delegating to specific operation classes.
6. **Instructions**: Loads and manages the instructions to be executed.

## Instruction Set
| Opcode | Description                                    |
|--------|------------------------------------------------|
| 1RXY   | Load register R with the value at memory address XY. |
| 2RXY   | Load register R with the value XY.             |
| 3RXY   | Store the value in register R at memory address XY. |
| 4R0S   | Copy the value in register R to register S.    |
| 5RST   | Add values in registers S and T, store the result in R. |
| 6RST   | Floating-point addition of values in registers S and T, store the result in R. |
| 7RST   | Bitwise OR of values in registers S and T, store the result in R. |
| 8RST   | Bitwise AND of values in registers S and T, store the result in R. |
| 9RST   | Bitwise XOR of values in registers S and T, store the result in R. |
| ARX0   | Right-rotate the value in register R by X bits. |
| BRXY   | Jump to address XY if the value in register R equals the value in R0. |
| DRXY   | Jump to address XY if the value in R0 is less than the value in register R. |
| C000   | Halt the program.                              |

## Usage
1. **Compilation**: Compile the program using a C++ compiler (e.g., g++).
   ```bash
   g++ VoleMachineSimulator.cpp -o vole_simulator
   ```
2. **Execution**: Run the compiled program.
   ```bash
   ./vole_simulator
   ```
3. **Input Options**:
   - Load instructions from a file.
   - Enter instructions manually via the console.
4. **Output**: The final state of memory and registers is saved to `MemoryFile.txt` and `RegFile.txt`.

## Example Input
```
1002 21A1 30FF
4002
5310
5421
5523
6601
7701
8820
9934
A00F
B01C
C000
```

## Output Files
- `MemoryFile.txt`: Contains the final state of all memory locations.
- `RegFile.txt`: Contains the final state of all registers.

## Dependencies
- C++11 or later.
- Standard C++ libraries (`<iostream>`, `<vector>`, `<string>`, `<cmath>`, etc.).

## Notes
- The simulator supports both hexadecimal and binary representations.
- Floating-point operations use a custom 12-bit floating-point format (1 sign bit, 3 exponent bits, 8 mantissa bits).
- Invalid instructions or operations will halt the program with an error message.
