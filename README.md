# Advanced Brainfuck Interpreter

## Overview

This is an advanced implementation of a **Brainfuck Interpreter** written in modern C++. It processes and executes Brainfuck programs from a file. The interpreter includes input/output functionalities, efficient memory management, and a robust error-checking mechanism.

Brainfuck is an esoteric programming language consisting of only eight commands (`>`, `<`, `+`, `-`, `.`, `,`, `[`, `]`) operating on an array of memory cells. This project executes programs written in Brainfuck with efficient terminal configuration.

## Features

- **Memory Management**: Dynamically adjusts the memory tape size during runtime.
- **Jump Preprocessing**: Efficient mapping of `[` and `]` ensures fast program execution.
- **Terminal Handling**: Configures the terminal for seamless input when needed.
- **Robust Error Handling**:
  - Ensures unmatched brackets `[` or `]` are detected during preprocessing.
  - Provides meaningful error messages for debugging purposes.
- **File-Based Execution**: Reads Brainfuck code from a file, ensuring easy integration.

---

## Installation

### Prerequisites
- **C++ Compiler a compiler that supports C++11 or later.
- **Make**: For building the project from source.

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/CalestialAshley35/bf-interpreter.git
   cd bf-interpreter
   ```
2. Build the project:
   ```bash
   make
   ```
3. Run the interpreter with a Brainfuck program:
   ```bash
   ./interpreter bf run <filename>.bf
   ```

---

## Usage

The interpreter accepts Brainfuck code files as input. Ensure you provide a valid `.bf` file to run.

### Command Syntax
```bash
./interpreter bf run <filename.bf>
```

### Example
1. Create a file called `hello.bf` containing the classic Brainfuck "Hello World!" program:
   ```brainfuck
   +++++ [> +++++++ < -] > +++++ ++++. .+++ +++++. > +++++.<
   ```
2. Run the interpreter:
   ```bash
   ./interpreter bf run hello.bf
   ```
3. Output:
   ```
   Hello World!
   ```

---

## Code Structure

### Main Components
1. **Class `BrainfuckInterpreter`**
   - **Constructor**: Handles file loading and terminal configuration.
   - **Destructor**: Restores the terminal settings.
   - **execute()**: Executes the Brainfuck program using a virtual tape.
2. **Private Methods**:
   - `loadFile()`: Reads and validates the input file.
   - `preprocessJumps()`: Prepares the jump map for `[` and `]`.
   - `configureTerminal()`: Configures terminal for non-canonical input.
   - `restoreTerminal()`: Restores original terminal settings.

### Key Algorithmic Details
- **Dynamic Tape Expansion**: Automatically extends the memory tape when needed.
- **Bracket Matching**: Uses a stack to map matching `[` and `]` for efficient looping.
- **Error Handling**: Detects unmatched brackets and gracefully exits with meaningful error messages.

---

## Error Handling

- **File Loading Errors**: 
  - Displays an error if the `.bf` file cannot be opened.
- **Syntax Errors**: 
  - Detects unmatched `[` or `]` and terminates execution with an error message.

---

## Notes and Limitations

- **TTY Detection**: The interpreter configures the terminal only if input is from a TTY and a `,` command is present.
- **Non-Standard Behavior**: Reading input (`getchar`) assumes EOF as `0`. This behavior may vary on different platforms.
- **Performance**: Optimized for small Brainfuck programs. Larger programs may require additional optimization.

---

## Contributing

Feel free to contribute to this project by submitting pull requests. Ensure your code adheres to modern C++ standards and includes comprehensive comments.

1. Fork the repository.
2. Make changes.
3. Submit a pull request!

---

## License

This project is licensed under the GNU General Public License v3.0. Feel free to use, modify, and distribute it as per the license terms.