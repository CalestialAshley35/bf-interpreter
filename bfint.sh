#!/bin/bash

version="2.7.4"
repo="https://github.com/CalestialAshley35/bf-interpreter"
os_name=$(uname)

echo "Brainfuck Interpreter $version (March 2 2025) [Repository: $repo] on $os_name"
echo 'Type "help", "creator", "exit", "install" or "license" for more information.'
echo -n ">>> "

while true; do
    read input
    case $input in
        help)
            echo "You Should Check our Detailed Tutorial at https://github.com/CalestialAshley35/bf-interpreter/blob/main/TUTORIALS.md"
            ;;
        license)
            echo "MIT License"
            echo
            echo "Copyright (c) 2025 Calestial Ashley"
            echo
            echo "Permission is hereby granted, free of charge, to any person obtaining a copy"
            echo "of this software and associated documentation files (the 'Software'), to deal"
            echo "in the Software without restriction, including without limitation the rights"
            echo "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell"
            echo "copies of the Software, and to permit persons to whom the Software is"
            echo "furnished to do so, subject to the following conditions:"
            echo
            echo "The above copyright notice and this permission notice shall be included in all"
            echo "copies or substantial portions of the Software."
            echo
            echo "THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR"
            echo "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,"
            echo "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE"
            echo "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER"
            echo "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,"
            echo "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN"
            echo "THE SOFTWARE."
            ;;
        creator)
            echo "Creates and Maintained by Calestial Ashley"
            ;;
        install)
            wget https://github.com/CalestialAshley35/bf-interpreter/raw/main/interpreter.cpp
            g++ interpreter.cpp -o interpreter
            echo "Launch the Interpreter by ./interpreter"
            ;;
        exit)
            break
            ;;
        *)
            echo "Unknown command. Type 'help' for a list of available commands."
            ;;
    esac
    echo -n ">>> "
done