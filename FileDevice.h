#ifndef FILEDEVICE_H
#define FILEDEVICE_H

#include <fstream>
#include <string>

#include "Device.h"

class FileDevice : public Device {
  private:
    std::string fileName;
    std::fstream file;

  public:
    FileDevice(std::string fileName) { this->fileName = fileName; }

    void close() override { this->file.close(); }

    int read() override {
        // std::cout << "READ" << std::endl;
        if (!this->file.is_open()) {
            std::ofstream outfile(fileName,
                                  std::fstream::out | std::fstream::app);
            outfile.close();
            file.open(this->fileName, std::fstream::in | std::fstream::out |
                                          std::fstream::app |
                                          std::ios_base::binary);
        }

        if (this->file.is_open()) {
            return this->file.get();
        } else {
            std::cout << "Cannot read from file " << fileName << std::endl;
            return 0;
        }
    }

    void write(char value) override {
        // std::cout << "WRITE" << std::endl;
        if (!this->file.is_open()) {
            std::ofstream outfile(fileName,
                                  std::fstream::out | std::fstream::app);
            outfile.close();
            file.open(this->fileName, std::fstream::in | std::fstream::out |
                                          std::fstream::app |
                                          std::ios_base::binary);
        }
        if (this->file.is_open()) {
            this->file << value;
        } else {
            std::cout << "Canno write to file " << fileName << std::endl;
        }
    }
};

#endif