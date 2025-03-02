# Brainfuck Interpreter for Linux

Welcome to the **Brainfuck Interpreter**! This interpreter allows you to run, debug, and benchmark Brainfuck programs on Linux. It comes with performance optimizations and code formatting features.

## Features

- **Bidirectional Tape Support**: Unlike traditional Brainfuck interpreters that operate on a one-dimensional, infinite-right tape, this interpreter features **bidirectional tape expansion**, allowing the pointer to move freely into negative positions. Memory is dynamically allocated as needed on both ends of the tape.
- **Code Optimization** (`-O3` flag): Experimental optimizations for faster execution
- **Buffered I/O**: 
  - 8KB output buffer for high-performance printing
  - Raw terminal input mode for single-character reads
- **Preprocessing**:
  - Jump table pre-calculation for loops
  - Syntax validation (unmatched bracket detection)
- **Filtered Input**: Ignores non-Brainfuck characters from source files
- **Run Brainfuck Programs:** Execute Brainfuck code with optimized performance.
- **Debug Mode:** Step through the Brainfuck code with detailed debug information.
- **Benchmark Mode:** Measure the execution time of Brainfuck programs.
- **Code Formatting:** Format Brainfuck code for better readability.

## Installation Instructions

To install the Brainfuck Interpreter, please follow the commands below:

### **Linux/MacOS:**
```bash
wget https://github.com/CalestialAshley35/bf-interpreter/raw/main/interpreter.cpp
g++ interpreter.cpp -o interpreter
```

### **Windows:**
1. Download the file from [Interpreter for Windows](https://github.com/CalestialAshley35/bf-interpreter/blob/main/windows.cpp).
2. Run it using MinGW or Visual Studio C++.

### Run Mode

To execute a Brainfuck program, use the `run` command followed by the filename:

```bash
./interpreter bf run <filename>.bf
```

### Code Optimization 
To execute a Brainfuck Program with fast execution, use the -03 flag by following command:
```bash
./interpreter bf run <filename>.bf -03
```

### Debug Mode

To debug a Brainfuck program, use the `debug` command:

```bash
./interpreter bf debug <filename.bf>
```

### Benchmark Mode

To benchmark a Brainfuck program, use the `benchmark` command:

```bash
./interpreter bf benchmark <filename.bf>
```

### Code Formatting

To format a Brainfuck program for better readability, use the `format` command:

```bash
./interpreter bf format <filename.bf>
```

## Example

Here is an example of how to use the Brainfuck Interpreter:

```bash
# Download the interpreter
wget https://github.com/CalestialAshley35/bf-interpreter/raw/main/interpreter.cpp

# Compile the interpreter
g++ interpreter.cpp -o interpreter

# Run a Brainfuck program
./interpreter bf run example.bf

# Run a Brainfuck program with fast optimization 
./interpreter bf run example.sh -03

# Debug a Brainfuck program
./interpreter bf debug example.bf

# Benchmark a Brainfuck program
./interpreter bf benchmark example.bf

# Format a Brainfuck program
./interpreter bf format example.bf
```

## Latest Version

The latest version of the Brainfuck Interpreter is **v2.3.0**, which includes the following updates:

- Added benchmark mode
- Added performance optimization (-03)
- Added code formatting feature

## Contribution

Feel free to fork this project, submit issues, or create pull requests. Contributions are always welcome! red