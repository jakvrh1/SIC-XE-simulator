#ifndef MEMORY_H
#define MEMORY_H

#include <iomanip>
#include <iostream>
#include <vector>

class Memory {
  public:
    
    static constexpr int MAX_ADDRESS = 1 << 20;
    std::vector<int> memory;

    Memory(int size) { this->memory.assign(size, 0); }

    void display() {
        std::ios oldState(nullptr);
        oldState.copyfmt(std::cout);
        std::cout << "Memory\n";
        int j = 0;
        bool insertedEmptyDots = false;
        while (j < MAX_ADDRESS) {
            bool isEmptyLine = true;
            for (int i = 0; i < 16 && i + j < MAX_ADDRESS; ++i) {
                if (this->getByte(i + j) != 0) isEmptyLine = false;
            }

            if(isEmptyLine && !insertedEmptyDots) {
                std::cout << "[empty]\n";
                insertedEmptyDots = true;
            }

            if (!isEmptyLine) {
                insertedEmptyDots = false;
                std::cout << std::hex << std::setfill('0') << std::setw(5) << j
                      << "\t";

                std::cout.copyfmt(oldState);

                for (int i = 0; i < 16 && i + j < MAX_ADDRESS; ++i)
                    std::cout << std::hex << std::setfill('0') << std::setw(2) << this->getByte(i + j) << "  ";
                std::cout << "\n";
                std::cout.copyfmt(oldState);
            }

            j += 16;
        }

        std::cout << std::flush;
    }

    int getWord(int addr) {
        return getByte(addr) << 16 | (getByte(addr + 1) << 8) |
               (getByte(addr + 2));
    }

    int getByte(int addr) {
        if (checkAddress(addr))
            return (memory[addr] & 0xFF);
        else
            return 0;
    }

    void setWord(int addr, int val) {
        setByte(addr, val >> 16);
        setByte(addr + 1, val >> 8);
        setByte(addr + 2, val);
    }

    void setByte(int addr, int val) {
        if (checkAddress(addr)) memory[addr] = val;
    }

  private:
    bool checkAddress(int addr) {
        bool valid = (addr >= 0 && addr < memory.size());
        if (!valid) printf("Invalid memory address: %d\n", addr);
        return valid;
    }
};

#endif