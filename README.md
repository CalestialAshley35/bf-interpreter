# Brainfuck Interpreter for Linux

Welcome to the **Brainfuck Interpreter**! This interpreter allows you to run, debug, benchmark, and format Brainfuck programs on Linux. It comes with performance optimizations and code formatting features.

## Features

- **Bidirectional Tape Support**: Unlike traditional Brainfuck interpreters that operate on a one-dimensional, infinite-right tape, this interpreter features **bidirectional tape expansion**, allowing the pointer to move freely into negative positions. Memory is dynamically allocated as needed on both ends of the tape.
- **Code Optimization** (`-O3` flag): Experimental optimizations for faster execution.
- **Buffered I/O**: 
  - 8KB output buffer for high-performance printing.
  - Raw terminal input mode for single-character reads.
- **Preprocessing**:
  - Jump table pre-calculation for loops.
  - Syntax validation (unmatched bracket detection).
- **Filtered Input**: Ignores non-Brainfuck characters from source files.
- **Run Brainfuck Programs**: Execute Brainfuck code with optimized performance.
- **Debug Mode**: Step through the Brainfuck code with detailed debug information.
- **Benchmark Mode**: Measure the execution time of Brainfuck programs.
- **Code Formatting**: Format Brainfuck code for better readability.

## Installation Instructions

To install the Brainfuck Interpreter, please follow the commands below:

### **Linux/MacOS:**
```bash
wget https://github.com/CalestialAshley35/bf-interpreter/raw/main/interpreter.cpp
g++ interpreter.cpp -o interpreter
```

### **Windows:**
1. Download the Windows-Specific File from [Interpreter for Windows](https://github.com/CalestialAshley35/bf-interpreter/blob/main/windows.cpp).
2. Run it using MinGW or Visual Studio C++.

## Version Banner

You can use the Version Banner for seeing what version your using 
To install the Brainfuck Interpreter with the version banner, follow these steps:

```bash
wget https://github.com/CalestialAshley35/bf-interpreter/raw/main/bfint.deb
apt install bfint.deb
```

When you run the `bfint` command, you'll see the following version banner:

```bash
~ $ bfint
Brainfuck Interpreter 2.5.4 (March 2 2025) [Repository: https://github.com/CalestialAshley35/bf-interpreter] on Linux
Type "help", "creator", "exit", "install" or "license" for more information.
>>> 
```

Certainly! Here’s a more polished and professional version of your text:

## Brainfuck Shell

Introducing a powerful shell that supports typing Brainfuck code within a REPL environment. To install, follow these steps:
1. Download the shell script:
    ```bash
    wget https://github.com/CalestialAshley35/bf-interpreter/raw/main/shell.cpp
    ```
2. Compile the script using g++:
    ```bash
    g++ shell.cpp -o shell
    ```
3. Run the shell:
    ```bash
    ./shell
    ```

Upon execution, you will see the following prompt:
```bash
Enter Brainfuck code (Ctrl+C to exit):
```

## Run Mode

To execute a Brainfuck program, use the `run` command followed by the filename:

```bash
./interpreter bf run <filename>.bf
```

## Code Optimization 

To execute a Brainfuck Program with fast execution, use the `-03` flag:

```bash
./interpreter bf run <filename>.bf -03
```

## Debug Mode

To debug a Brainfuck program, use the `debug` command:

```bash
./interpreter bf debug <filename>.bf
```

## Benchmark Mode

To benchmark a Brainfuck program, use the `benchmark` command:

```bash
./interpreter bf benchmark <filename>.bf
```

## Code Formatting

To format a Brainfuck program for better readability, use the `format` command:

```bash
./interpreter bf format <filename>.bf
```

## Warning Mode

To get warnings for a Brainfuck program, use the `warning` command:

```bash
./interpreter bf warning <filename>.bf
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
./interpreter bf run example.bf -03

# Debug a Brainfuck program
./interpreter bf debug example.bf

# Benchmark a Brainfuck program
./interpreter bf benchmark example.bf

# Format a Brainfuck program
./interpreter bf format example.bf

# Get warnings for a Brainfuck program
./interpreter bf warning hello.bf
```

## Latest Version

The latest version of the Brainfuck Interpreter is **v2.7.4**, which includes the following updates:

- Added Brainfuck Shell
- Added Version Banner

## Contribution

Feel free to fork this project, submit issues, or create pull requests. Contributions are always welcome! 