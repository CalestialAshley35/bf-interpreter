# Brainfuck Interpreter

This project is a sophisticated, high performance, highly efficient **Brainfuck Interpreter** implemented in C++ to execute programs written in the Brainfuck programming language. Designed with both performance and usability in mind, it features robust tape handling, a debugging environment, and optimized I/O operations. 

## Key Features

### 1. **Bidirectional Tape Support**
- Unlike traditional Brainfuck interpreters that operate on a one-dimensional, infinite-right tape, this interpreter features **bidirectional tape expansion**, allowing the pointer to move freely into negative positions. Memory is dynamically allocated as needed on both ends of the tape.

### 2. **Debugging Mode**
- The interpreter includes a **debug mode**, offering an interactive step-by-step execution environment. You can inspect program state, data pointer position, memory cell values, and even take specific actions during debugging:
  - View current and surrounding tape cells.
  - Print the data pointer value.
  - Continue or quit debugging at any time.

### 3. **Error Detection**
- Built-in **syntax validation** for unmatched brackets:
  - Errors like missing `[` or `]` are identified during preprocessing, saving time during execution.
  - Detailed error messages inform the exact position of the mismatch.

### 4. **Optimized Input and Output**
- Intelligent buffering for output (`.`) operations:
  - Uses an internal buffer to optimize performance by minimizing I/O operations.
- Terminal configuration for input (``,`):
  - Switches the terminal to non-canonical mode for smooth character-by-character input handling.

### 5. **Cross-Platform Compatibility**
- While optimized for **Unix-like operating systems**, this interpreter is portable and can be adapted to other platforms with minimal changes.

---

## Table of Contents
1. [Installation](#installation)
2. [Usage](#usage)
3. [Debugging Mode](#debugging-mode)
4. [Advanced Program Execution](#advanced-program-execution)
5. [Error Handling](#error-handling)
6. [Code Architecture](#code-architecture)
8. [Contributing](#contributing)
9. [License](#license)

---

## Installation

To get started, clone this repository and compile the project using the following commands:

```bash
# Clone the repository
git clone https://github.com/CalestialAshley35/bf-interpreter.git

# Navigate to the project directory
cd bf-interpreter

# Build the interpreter using make
make
```

---

## Usage

To execute a Brainfuck program, use the following syntax:

```bash
./interpreter bf run <filename>.bf
```

- Replace `<filename>.bf` with the path to your Brainfuck program file.
- The interpreter will execute the provided Brainfuck code and display the result.

### Example
Run a "Hello, World!" program:
```bash
./interpreter bf run hello_world.bf
```

---

## Debugging Mode

Debug mode allows you to step through each instruction, making it easier to debug Brainfuck programs. Use the following command to enable debug mode:

```bash
./interpreter bf debug <filename>.bf
```

### Interactive Debugging Commands
| Command   | Action                                                                 |
|-----------|------------------------------------------------------------------------|
| `(s)`     | Step through one instruction at a time.                                |
| `(c)`     | Continue execution without stopping at each instruction.               |
| `(p)`     | Print the values of cells around the data pointer for inspection.      |
| `(q)`     | Quit debug mode and terminate the program.                             |

---

## Advanced Program Execution

### Memory Layout
The program operates with two separate tape regions:
1. **Right Tape**: Handles positive data pointer values (`>` operations).
2. **Left Tape**: Handles negative data pointer values (`<` operations).

This implementation ensures that the interpreter never exceeds memory bounds by dynamically expanding the tape as needed.

### Bracket Matching
During preprocessing:
- All matching brackets (`[` and `]`) are stored in a `jump_map` for quick lookup.
- This significantly speeds up execution for programs with nested loops.

---

## Error Handling

### Common Errors
- **Unmatched `[`:**
  - Occurs when a `[` does not have a corresponding `]`.
  - Error message: `Error: Unmatched '[' at position <index>`
- **Unmatched `]`:**
  - Occurs when a `]` does not have a corresponding `[`.
  - Error message: `Error: Unmatched ']' at position <index>`

### Debugging Terminal Issues
If the terminal becomes unresponsive due to non-canonical mode, reset it by running:
```bash
reset
```

---

## Code Architecture

### Class Overview
- **`BrainfuckInterpreter`**: Core class responsible for loading, parsing, and executing Brainfuck code.
  - **Methods**:
    - `execute()`: Main execution loop.
    - `debugStep()`: Handles interactive debugging.
    - `accessCell()`: Safely accesses or modifies the current tape cell.
    - `configureTerminal() / restoreTerminal()`: Handles terminal modes for input operations.

### Key Components
| Component           | Description                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| **`loadFile`**      | Reads and filters Brainfuck code from a file.                              |
| **`preprocessJumps`** | Precomputes all jump positions for loop instructions (`[`, `]`).           |
| **`output_buffer`** | Buffers output for efficient writing.                                       |

## Debug Mode Example
To deeply understand the execution of a program, enable debug mode:
```bash
./interpreter bf debug fibonacci.bf
```

You can interactively step through each instruction, inspect tape cells, and visualize the operations being carried out on the memory.

---

## Troubleshooting

### Common Issues
1. **Unbalanced Brackets**:
   - If there is an error like "Unmatched '[' or ']'", verify that each `[` has a corresponding `]` in your Brainfuck code.

2. **Terminal Input Issues**:
   - For programs that rely on the `,` (input) command, ensure your terminal supports non-canonical input mode. If the terminal becomes unresponsive after execution, simply run:
     ```bash
     reset
     ```

### Optimizing Performance
- For large and complex Brainfuck programs, try running the interpreter without debug mode for maximum speed:
  ```bash
  ./interpreter bf run <filename>.bf
  ```

---

## Contributing

Contributions to improve the project are welcome! If you have ideas for new features, bug fixes, or optimizations:
- Fork the repository.
- Create a new branch for your changes.
- Submit a pull request with detailed explanations of your contributions.

Feel free to report any issues or suggestions via the repository's [Issue Tracker](https://github.com/CalestialAshley35/bf-interpreter/issues).

---

## License

This project is open-source and available under the **GNU General Public License v3.0**. See the `LICENSE` file for more information.

___

With this enhanced Brainfuck interpreter, you can unleash the full potential of the Brainfuck programming language. Whether you're an enthusiast, a student, or a developer exploring esolang execution, this tool empowers you to debug, analyze, and execute Brainfuck programs with precision and ease.

Enjoy exploring the intricate world of Brainfuck!