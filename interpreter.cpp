#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <termios.h>
#include <unistd.h>
#include <limits>

class BrainfuckInterpreter {
public:
    BrainfuckInterpreter(const std::string& filename) {
        if (!loadFile(filename)) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            exit(1);
        }
        preprocessJumps();
        is_stdin_tty = isatty(STDIN_FILENO);
        configureTerminal();
    }

    ~BrainfuckInterpreter() {
        restoreTerminal();
    }

    void execute() {
        std::vector<unsigned char> tape(1, 0);
        size_t dp = 0, ip = 0;

        while (ip < code.size()) {
            switch (code[ip]) {
                case '>':
                    if (++dp == tape.size()) tape.push_back(0);
                    break;
                case '<':
                    if (dp > 0) --dp;
                    break;
                case '+':
                    ++tape[dp];
                    break;
                case '-':
                    --tape[dp];
                    break;
                case '.':
                    std::cout.put(tape[dp]).flush();
                    break;
                case ',':
                    tape[dp] = readInput();
                    break;
                case '[':
                    if (tape[dp] == 0) ip = jump_map[ip];
                    break;
                case ']':
                    if (tape[dp] != 0) ip = jump_map[ip];
                    break;
            }
            ++ip;
        }
    }

private:
    std::string code;
    std::unordered_map<size_t, size_t> jump_map;
    bool is_stdin_tty;
    struct termios original_termios;
    bool terminal_configured = false;

    bool loadFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) return false;
        std::string raw_code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        for (char c : raw_code) {
            if (std::string("><+-.,[]").find(c) != std::string::npos) code += c;
        }
        return true;
    }

    void preprocessJumps() {
        std::stack<size_t> stack;
        for (size_t i = 0; i < code.size(); ++i) {
            if (code[i] == '[') stack.push(i);
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

    void configureTerminal() {
        if (!is_stdin_tty || code.find(',') == std::string::npos) return;
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
        return (input == EOF) ? 0 : static_cast<unsigned char>(input);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 4 || std::string(argv[1]) != "bf" || std::string(argv[2]) != "run") {
        std::cerr << "Usage: " << argv[0] << " bf run <filename.bf>" << std::endl;
        return 1;
    }
    BrainfuckInterpreter interpreter(argv[3]);
    interpreter.execute();
    return 0;
}
