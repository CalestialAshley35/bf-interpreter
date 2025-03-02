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

    ~BrainfuckInterpreter() {
        std::cout.write(output_buffer.data(), output_buffer.size());
        std::cout.flush();
    }

    void execute() {
        auto start = std::chrono::high_resolution_clock::now();
        int dp = 0;
        size_t ip = 0;
        std::vector<unsigned char> right_tape{ 0 };
        std::vector<unsigned char> left_tape;
        instructions_executed = 0;
        max_right_tape = right_tape.size();
        max_left_tape = left_tape.size();

        while (ip < code.size()) {
            size_t current_ip = ip;
            char current_instr = code[current_ip];
            instructions_executed++;

            switch (current_instr) {
            case '>':
                if (++dp >= 0) {
                    if (static_cast<size_t>(dp) >= right_tape.size()) {
                        right_tape.push_back(0);
                        max_right_tape = std::max(max_right_tape, right_tape.size());
                    }
                }
                break;
            case '<':
                if (--dp < 0) {
                    size_t index = -dp - 1;
                    if (index >= left_tape.size()) {
                        left_tape.push_back(0);
                        max_left_tape = std::max(max_left_tape, left_tape.size());
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
            std::cout << "Instructions Executed: " << instructions_executed << "\n";
            std::cout << "Memory Used: " << (max_left_tape + max_right_tape) << " cells\n";
            std::cout << "Performance: " << (instructions_executed / duration.count()) << " instructions/second\n";
        }
    }

    void benchmark() {
        benchmark_mode = true;
        execute();
    }

private:
    std::string code;
    std::vector<size_t> jump_map;
    std::string output_buffer;
    bool debug_mode;
    bool optimize_code;
    bool benchmark_mode = false;
    size_t ignored_chars = 0;
    size_t instructions_executed = 0;
    size_t max_right_tape = 0;
    size_t max_left_tape = 0;

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
        ignored_chars = raw_code.size() - filtered.size();
        return true;
    }

    void preprocessJumps() {
        std::stack<size_t> stack;
        jump_map.resize(code.size());
        for (size_t i = 0; i < code.size(); ++i) {
            if (code[i] == '[') {
                stack.push(i);
            }
            else if (code[i] == ']') {
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
        return _getch(); // Windows equivalent of non-buffered getchar()
    }

    void debugStep(size_t current_ip, char current_instr, size_t new_ip, int dp, const std::vector<unsigned char>& left_tape, const std::vector<unsigned char>& right_tape) {
        std::cout << "Debug: Executed '" << current_instr << "' at position " << current_ip << "\n";
        std::cout << "Next IP: " << new_ip << "\n";
        std::cout << "Data pointer: " << dp << "\n";
        std::cout << "Debug commands: (s)tep, (c)ontinue, (q)uit\n> ";
        std::string cmd;
        std::getline(std::cin, cmd);
        if (cmd.empty()) cmd = "s";
        if (cmd[0] == 'q') exit(0);
        if (cmd[0] == 'c') debug_mode = false;
    }

    void optimizeBrainfuckCode() {
        // Optimization logic placeholder
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3 || std::string(argv[1]) != "bf") {
        std::cerr << "Usage: " << argv[0] << " bf run|debug|benchmark <filename.bf> [-03]\n";
        return 1;
    }
    std::string command = argv[2];
    if (argc < 4) {
        std::cerr << "Error: Missing filename.\n";
        return 1;
    }
    std::string filename = argv[3];
    bool optimize = (argc > 4 && std::string(argv[4]) == "-03");
    bool debug_mode = (command == "debug");

    BrainfuckInterpreter interpreter(filename, debug_mode, optimize);

    if (command == "run" || command == "debug") {
        interpreter.execute();
    }
    else if (command == "benchmark") {
        interpreter.benchmark();
    }
    else {
        std::cerr << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
}