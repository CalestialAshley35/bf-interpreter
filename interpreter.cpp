#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <algorithm>

class BrainfuckInterpreter {
public:
    BrainfuckInterpreter(const std::string& filename, bool debug) : debug_mode(debug) {
        if (!loadFile(filename)) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            exit(1);
        }
        preprocessJumps();
        configureTerminal();
    }

    ~BrainfuckInterpreter() {
        restoreTerminal();
        std::cout.write(output_buffer.data(), output_buffer.size());
        std::cout.flush();
    }

    void execute() {
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
    }

private:
    std::string code;
    std::vector<size_t> jump_map;
    struct termios original_termios;
    std::string output_buffer;
    bool terminal_configured = false;
    bool debug_mode;

    bool loadFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) return false;
        std::string raw_code((std::istreambuf_iterator<char>(file)), filtered;
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

    void configureTerminal() {
        if (!isatty(STDIN_FILENO) || code.find(',') == std::string::npos) return;
        if (tcgetattr(STDIN_FILENO, &original_termios) == -1) return;
        struct termios new_termios = original_termios;
        new_termios.c_lflag &= ~(ICANON | ECHO);
        new_termios.c_cc[VMIN] = 1;
        new_termios.c_cc[VTIME] = 0;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) != -1) terminal_configured = true;
    }

    void restoreTerminal() {
        if (terminal_configured) tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    }

    unsigned char readInput() {
        int input = getchar();
        return static_cast<unsigned char>(input != EOF ? input : 0);
    }

    void debugStep(size_t current_ip, char current_instr, size_t new_ip, int dp, const std::vector<unsigned char>& left_tape, const std::vector<unsigned char>& right_tape) {
        if (terminal_configured) tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
        std::cout << "Debug: Executed '" << current_instr << "' at position " << current_ip << "\n";
        std::cout << "Next IP: " << new_ip << " (next instruction after increment: " << (new_ip + 1) << ")\n";
        std::cout << "Data pointer: " << dp << "\n";
        unsigned char cell_value = 0;
        if (dp >= 0) {
            if (static_cast<size_t>(dp) < right_tape.size()) {
                cell_value = right_tape[dp];
            }
        } else {
            size_t index = -dp - 1;
            if (index < left_tape.size()) {
                cell_value = left_tape[index];
            }
        }
        std::cout << "Current cell value: " << static_cast<int>(cell_value) << "\n";
        std::cout << "Debug commands: (s)tep, (c)ontinue, (p)rint, (q)uit\n> ";
        std::flush(std::cout);
        std::string cmd;
        if (!std::getline(std::cin, cmd)) cmd = "q";
        if (cmd.empty()) cmd = "s";
        switch (cmd[0]) {
            case 's': break;
            case 'c': debug_mode = false; break;
            case 'p': printCells(dp, left_tape, right_tape); debugStep(current_ip, current_instr, new_ip, dp, left_tape, right_tape); break;
            case 'q': exit(0);
            default: std::cout << "Unknown command. Defaulting to step.\n"; break;
        }
        if (terminal_configured) {
            struct termios new_termios = original_termios;
            new_termios.c_lflag &= ~(ICANON | ECHO);
            new_termios.c_cc[VMIN] = 1;
            new_termios.c_cc[VTIME] = 0;
            tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
        }
    }

    void printCells(int dp, const std::vector<unsigned char>& left_tape, const std::vector<unsigned char>& right_tape) {
        const int range = 2;
        std::cout << "Cells around dp (" << dp << "):\n";
        for (int i = dp + range; i >= dp - range; --i) {
            std::cout << (i == dp ? "[" : " ") << i << (i == dp ? "]" : " ");
        }
        std::cout << "\n";
        for (int i = dp + range; i >= dp - range; --i) {
            unsigned char value = 0;
            if (i >= 0) {
                if (static_cast<size_t>(i) < right_tape.size()) {
                    value = right_tape[i];
                }
            } else {
                size_t index = -i - 1;
                if (index < left_tape.size()) {
                    value = left_tape[index];
                }
            }
            std::cout << (i == dp ? "[" : " ") << static_cast<int>(value) << (i == dp ? "]" : " ");
        }
        std::cout << "\n";
    }
};

int main(int argc, char* argv[]) {
    if (argc != 4 || std::string(argv[1]) != "bf" || (std::string(argv[2]) != "run" && std::string(argv[2]) != "debug")) {
        std::cerr << "Usage: " << argv[0] << " bf run|debug <filename.bf>\n";
        return 1;
    }
    bool debug_mode = (std::string(argv[2]) == "debug");
    BrainfuckInterpreter interpreter(argv[3], debug_mode);
    interpreter.execute();
    return 0;
}