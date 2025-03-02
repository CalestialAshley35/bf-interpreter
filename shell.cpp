#include <iostream>
#include <vector>
#include <stack>

int main() {
    std::string code;
    while (true) {
        std::cout << "Enter Brainfuck code (Ctrl+C to exit): ";
        std::getline(std::cin, code);
        std::vector<unsigned char> tape(30000, 0);
        int ptr = 0;
        size_t pc = 0;
        std::stack<size_t> loop_stack;

        while (pc < code.size()) {
            char cmd = code[pc];
            if (cmd == '>') {
                ptr++;
            } else if (cmd == '<') {
                ptr--;
            } else if (cmd == '+') {
                tape[ptr]++;
            } else if (cmd == '-') {
                tape[ptr]--;
            } else if (cmd == '.') {
                std::cout << tape[ptr];
            } else if (cmd == ',') {
                std::cin >> tape[ptr];
            } else if (cmd == '[') {
                if (tape[ptr] == 0) {
                    int loop = 1;
                    while (loop > 0) {
                        pc++;
                        if (code[pc] == '[') loop++;
                        else if (code[pc] == ']') loop--;
                    }
                } else {
                    loop_stack.push(pc);
                }
            } else if (cmd == ']') {
                if (tape[ptr] != 0) {
                    pc = loop_stack.top();
                } else {
                    loop_stack.pop();
                }
            }
            pc++;
        }
        std::cout << std::endl;
    }
}