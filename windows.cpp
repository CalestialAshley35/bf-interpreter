#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <chrono>
#include <sstream>

class BrainfuckInterpreter {
public:
    BrainfuckInterpreter(const std::string& filename, bool debug, bool optimize)
        : debug_mode(debug), optimize_code(optimize) {
        if (!loadFile(filename)) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            exit(1);
        }
        if (optimize_code) {
            optimizeBrainfuckCode();
        }
        preprocessJumps();
    }

    void execute() {
        auto start = std::chrono::high_resolution_clock::now();
        int dp = 0;
        size_t ip = 0;
        std::vector<unsigned char> right_tape{0};
        std::vector<unsigned char> left_tape;

        while (ip < code.size()) {
            size_t current_ip = ip;
            char current_instr = code[current_ip];
            switch (current_instr) {
                case '>':
                    if (++dp >= 0) {
                        if (static_cast<size_t>(dp) >= right_tape.size()) {
                            right_tape.push_back(0);
                        }
                    }
                    break;
                case '<':
                    if (--dp < 0) {
                        size_t index = -dp - 1;
                        if (index >= left_tape.size()) {
                            left_tape.push_back(0);
                        }
                    }
                    break;
                case '+':
                    accessCell(dp, right_tape, left_tape)++;
                    break;
                case '-':
                    accessCell(dp, right_tape, left_tape)--;
                    break;
                case '.':
                    output_buffer += accessCell(dp, right_tape, left_tape);
                    if (output_buffer.size() >= 8192) {
                        std::cout.write(output_buffer.data(), output_buffer.size());
                        output_buffer.clear();
                    }
                    break;
                case ',':
                    accessCell(dp, right_tape, left_tape) = readInput();
                    break;
                case '[':
                    if (!accessCell(dp, right_tape, left_tape)) {
                        ip = jump_map[current_ip];
                    }
                    break;
                case ']':
                    if (accessCell(dp, right_tape, left_tape)) {
                        ip = jump_map[current_ip];
                    }
                    break;
            }
            if (debug_mode) {
                debugStep(current_ip, current_instr, ip, dp, left_tape, right_tape);
            }
            ++ip;
        }

        if (benchmark_mode) {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            std::cout << "Execution Time: " << duration.count() << " seconds\n";
        }
    }

    void benchmark() {
        benchmark_mode = true;
        execute();
    }

    void formatCode() {
        std::string formatted_code;
        int indentation = 0;
        for (char c : code) {
            if (c == '[') {
                formatted_code += '\n' + std::string(indentation, ' ') + c;
                indentation += 2;
            } else if (c == ']') {
                indentation -= 2;
                formatted_code += '\n' + std::string(indentation, ' ') + c;
            } else {
                formatted_code += c;
            }
        }
        std::cout << formatted_code << std::endl;
    }

private:
    std::string code;
    std::vector<size_t> jump_map;
    std::string output_buffer;
    bool debug_mode;
    bool optimize_code;
    bool benchmark_mode = false;

    bool loadFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) return false;
        std::string raw_code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::string filtered;
        for (char c : raw_code) {
            if (std::string("><+-.,[]").find(c) != std::string::npos) {
                filtered += c;
            }
        }
        code = std::move(filtered);
        return true;
    }

    void preprocessJumps() {
        std::stack<size_t> stack;
        jump_map.resize(code.size());
        for (size_t i = 0; i < code.size(); ++i) {
            if (code[i] == '[') {
                stack.push(i);
            } else if (code[i] == ']') {
                if (stack.empty()) {
                    std::cerr << "Error: Unmatched ']' at position " << i << std::endl;
                    exit(1);
                }
                size_t start = stack.top();
                stack.pop();
                jump_map[start] = i;
                jump_map[i] = start;
            }
        }
        if (!stack.empty()) {
            std::cerr << "Error: Unmatched '[' at position " << stack.top() << std::endl;
            exit(1);
        }
    }

    unsigned char& accessCell(int dp, std::vector<unsigned char>& right, std::vector<unsigned char>& left) {
        return dp >= 0 ? right[dp] : left[-dp - 1];
    }

    unsigned char readInput() {
        return _kbhit() ? _getch() : 0;
    }

    void debugStep(size_t current_ip, char current_instr, size_t new_ip, int dp,
                   const std::vector<unsigned char>& left_tape, const std::vector<unsigned char>& right_tape) {
        std::cout << "Debug: Executed '" << current_instr << "' at position " << current_ip << "\n";
        std::cout << "Next IP: " << new_ip << "\n";
        std::cout << "Data pointer: " << dp << "\n";
        unsigned char cell_value = accessCell(dp, const_cast<std::vector<unsigned char>&>(right_tape),
                                              const_cast<std::vector<unsigned char>&>(left_tape));
        std::cout << "Current cell value: " << static_cast<int>(cell_value) << "\n";
    }

    void optimizeBrainfuckCode() {
        // Implement internal optimizations here
        std::string optimized_code;
        for (size_t i = 0; i < code.size(); ++i) {
            char c = code[i];
            if (c == '+' || c == '-') {
                size_t count = 1;
                while (i + 1 < code.size() && code[i + 1] == c) {
                    ++count;
                    ++i;
                }
                optimized_code += std::string(count, c);
            } else {
                optimized_code += c;
            }
        }
        code = std::move(optimized_code);
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3 || std::string(argv[1]) != "bf") {
        std::cerr << "Usage: " << argv[0] << " bf run|debug|benchmark|format <filename.bf> [-O3]\n";
        return 1;
    }
    bool debug_mode = (std::string(argv[2]) == "debug");
    bool optimize = (argc > 3 && std::string(argv[3]) == "-O3");
    std::string command = argv[2];

    BrainfuckInterpreter interpreter(argv[3], debug_mode, optimize);

    if (command == "run") {
        interpreter.execute();
    } else if (command == "benchmark") {
        interpreter.benchmark();
    } else if (command == "format") {
        interpreter.formatCode();
    }

    return 0;
}