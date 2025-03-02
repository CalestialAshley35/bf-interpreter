# Brainfuck Interpreter Tutorial

This guide provides detailed instructions for using the Brainfuck interpreter/development tool. The tool supports execution, debugging, benchmarking, code formatting, and includes memory optimization features.

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Installation](#installation)
3. [Basic Usage](#basic-usage)
4. [Features](#features)  
   a. [Running Programs](#running-programs)  
   b. [Debug Mode](#debug-mode)  
   c. [Benchmarking](#benchmarking)  
   d. [Code Formatting](#code-formatting)  
   e. [Warnings](#warnings)  
5. [Optimization](#optimization)
6. [Debugger Commands](#debugger-commands)
7. [Input Handling](#input-handling)
8. [Examples](#examples)

## Prerequisites
- C++17 compatible compiler
- Linux/macOS terminal (Windows requires WSL or similar)
- Basic Brainfuck knowledge

## Installation
1. Save code as `bf_interpreter.cpp`
2. Compile with:
```bash
g++ -O3 -o bfint interpreter.cpp
```

## Basic Usage
```bash
./bfint bf [command] [filename.bf] [options]
```
Available commands:
- `run`: Execute program
- `debug`: Step-through debugger
- `benchmark`: Performance metrics
- `format`: Pretty-print code
- `warning`: Show ignored characters

## Features

### Running Programs
Execute a Brainfuck file:
```bash
./bfint bf run hello.bf
```
Output buffered in 8KB chunks for efficiency.

### Debug Mode
Interactive debugging:
```bash
./bfint bf debug maze.bf
```
Features:
- Instruction-level stepping
- Data pointer tracking
- Cell value inspection
- Memory visualization

### Benchmarking
Get performance stats:
```bash
./bfint bf benchmark mandelbrot.bf
```
Metrics include:
- Execution time
- Instructions processed
- Memory cells used
- Instructions/second rate

### Code Formatting
Structure code with indentation:
```bash
./bfint bf format unformatted.bf
```
Input:
```
++[>+[<->-]>]
```
Output:
```
++
[
  >+
  [
    <->-
  ]
  >
]
```

### Warnings
View ignored characters:
```bash
./bfint bf warning dirty_code.bf
```
Output:
```
Warning: 15 non-Brainfuck characters were ignored.
```

## Optimization
Enable with `-03` flag:
```bash
./bfint bf run optimized.bf -03
```
Current optimizations (placeholder):
- Filter valid Brainfuck commands
- Preprocess jump locations
- Memory-efficient tape storage

## Debugger Commands
During debugging:
```
(s)tep - Execute next instruction
(c)ontinue - Run without breaking
(p)rint - Show nearby memory cells
(q)uit - Terminate program
```

## Input Handling
- Single-character input with immediate processing
- Non-blocking I/O for ',' operator
- EOF returns 0 (per Brainfuck spec)

## Examples

### Hello World
`hello.bf`:
```brainfuck
++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.
```
Execution:
```bash
./bfint bf run hello.bf
Hello World!
```

### Debug Session Example
```
Debug: Executed '+' at position 0
Next IP: 1 (next instruction after increment: 2)
Data pointer: 0
Current cell value: 1
Debug commands: (s)tep, (c)ontinue, (p)rint, (q)uit
> p

Cells around dp (0):
[-2] [-1] [0] 1 2 
[0] [0] [1] 0 0
```

## Notes
- Tape grows dynamically in both directions
- Left tape stores negative pointer positions
- Right tape stores positive positions
- Maximum memory usage reported in benchmarks

Use this tool to develop, optimize, and debug Brainfuck programs with professional-grade instrumentation.