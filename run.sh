#!/bin/bash

# Create windows program
# g++ -pthread Main.cpp -o windows_out.exe

# Create linux program
# g++ -lpthread Main.cpp -o linux_out

if [[ "$OSTYPE" == "msys" ]]; then
    echo "Compiling for Windows"
    g++ -std=c++11 -pthread Main.cpp -o out.exe
else
    echo "Compiling for Linux"
    g++ -std=c++11 -lpthread Main.cpp -o out
fi