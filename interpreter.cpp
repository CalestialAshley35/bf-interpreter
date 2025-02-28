#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <termios.h>
#include <unistd.h>

class BrainfuckInterpreter {
public:
    BrainfuckInterpreter(const std::string& filename) {
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
            switch (code[ip]) {
                case '>':
                    if (++dp >= 0) {
                        if (dp >= static_cast<int>(right_tape.size())) {
                            right_tape.push_back(0);
                        }
                    }
                    break;
                case '<':
                    if (--dp < 0) {
                        const size_t index = -dp - 1;
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
                    if (!accessCell(dp, right_tape, left_tape)) ip = jump_map[ip];
                    break;
                case ']':
                    if (accessCell(dp, right_tape, left_tape)) ip = jump_map[ip];
                    break;
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

    bool loadFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) return false;
        std::string raw_code((std::istreambuf_iterator<char>(file)), filtered;
        for (char c : raw_code) if (std::string("><+-.,[]").find(c) != std::string::npos) filtered += c;
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
};

int main(int argc, char* argv[]) {
    if (argc != 4 || std::string(argv[1]) != "bf" || std::string(argv[2]) != "run") {
        std::cerr << "Usage: " << argv[0] << " bf run <filename.bf>\n";
        return 1;
    }
    BrainfuckInterpreter interpreter(argv[3]);
    interpreter.execute();
    return 0;
}