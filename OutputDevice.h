#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include <iostream>

#include "Device.h"

class OutputDevice : public Device {
  private:
    bool errorMessage = false;

  public:
    OutputDevice(bool error) { this->errorMessage = error; }
    OutputDevice() = default;
    void write(char value) override {
        if (errorMessage)
            std::cerr << value << std::flush;
        else
            std::cout << value << std::flush;
    }
};

#endif