#ifndef DEVICES_H
#define DEVICES_H

#include <sstream>
#include <string>
#include <vector>

#include "FileDevice.h"
#include "InputDevice.h"
#include "OutputDevice.h"

class Devices {
  private:
    std::vector<Device *> devices;
    const std::string location = "DEVS/";

  public:
    static constexpr int MAX_DEVICES = 255;

    Devices(int num) {
        this->devices.push_back(new InputDevice());
        this->devices.push_back(new OutputDevice());
        this->devices.push_back(new OutputDevice(true));

        for (int i = 3; i < 256; ++i) {
            std::stringstream stream;
            stream << std::hex << i;
            std::string file(stream.str());

            for (auto &c : file)
                c = toupper(c);

            this->devices.push_back(new FileDevice(location + file + ".dev"));
        }
    }

    ~Devices() {
        for (int i = 3; i < 256; ++i)
            this->devices[i]->close();
    }

    // void setDevice(int ind, Device device) { this->devices[ind] = device; }

    Device *getDevice(int ind) { return devices[ind]; }

    int read(int ind) {
        if (checkDeviceInd(ind)) {
            int val = devices[ind]->read();
            if (val < 0 || val > 255) val = 0;
            return val;
        } else
            return 0;
    }

    void write(int ind, char val) {
        if (checkDeviceInd(ind)) devices[ind]->write(val);
    }

    bool test(int ind) {
        if (checkDeviceInd(ind))
            return devices[ind]->test();
        else
            return false;
    }

  private:
    bool checkDeviceInd(int ind) {
        bool valid = (ind >= 0 && ind < devices.size());
        if (!valid) std::cout << "Invalid ind for device: " << ind << std::endl;

        return valid;
    }
};

#endif