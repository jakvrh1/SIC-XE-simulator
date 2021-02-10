#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <iostream>

#include "Device.h"

class InputDevice : public Device {
  public:
    int read() override {
        char a;
        std::cin >> a;
        return a;
    }
};

#endif