#ifndef DEVICE_H
#define DEVICE_H

#include "Memory.h"

class Device {
  public:
    virtual bool test() { return true; }

    virtual int read() { return 0; }

    virtual void write(char value) {}

    virtual void close() {}
};

#endif