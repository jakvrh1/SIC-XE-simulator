#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "Machine.h"

class Utils {
  public:
    static int charValue(char c) {
        std::string HEX = "0123456789ABCDEF";
        for (int i = 0; i < HEX.size(); ++i) {
            if (c == HEX[i]) return i;
        }
        return 0;
    }

    static int readByte(std::fstream &file) {
        int b = 0;
        char c;
        file >> c;
        b = charValue(c) << 4;
        file >> c;
        b |= charValue(c);
        return b;
    }

    static int readWord(std::fstream &file) {
        int word = 0;
        word = readByte(file) << 16;
        word |= readByte(file) << 8;
        word |= readByte(file);
        return word;
    }

    static bool readOBJFile(std::string file_location, Machine *m) {
        std::fstream file(file_location);
        if (file.is_open()) {
            char c;
            file >> c;

            if (c != 'H') return false;

            std::cout << "PROGRAM NAME: ";
            for (int i = 0; i < 6; ++i) {
                file >> c;
                std::cout << c;
            }
            std::cout << std::endl;
            int beg = readWord(file);
            int length = readWord(file);

            file >> c;

            while (c == 'T') {
                int addr = readWord(file);
                int len = readByte(file);
                while (len--) {
                    if (addr < beg || addr >= beg + length) return false;
                    m->memory->setByte(addr++, readByte(file));
                }

                file >> c;
            }

            while (c == 'M') {
                readWord(file);
                readByte(file);
                file >> c;
            }

            if (c != 'E') return false;

            m->registers->setPC(readWord(file));

            return true;
        }
        return false;
    }
};

#endif