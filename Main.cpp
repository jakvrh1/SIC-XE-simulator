#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <pthread.h>

#include "Machine.h"
#include "Utils.h"

using namespace std;

std::string objFile = "OBJ_FILES/SECOND_FACT_FA.obj";
Machine *machine = new Machine();
const int INITIAL_SPEED = 1;
bool _isRunning = false;
bool needToStop = false;
int speed = 1;

void sleepFun() {
#ifdef _WIN32
    Sleep(INITIAL_SPEED);
#else
    usleep(INITIAL_SPEED * 10000);
#endif
}

void sleepFun(int sec) {
#ifdef _WIN32
    Sleep(1000 * sec);
#else
    usleep(10000 * 1000 * sec);
#endif
}

void *threading(void *args) {
    _isRunning = true;
    i_register prev_PC = -1;

    while (!needToStop) {
        for (int i = 0; i < speed; ++i) {
            if (machine->registers->getPC() == prev_PC) {
                needToStop = true;
                break;
            }
            prev_PC = machine->registers->getPC();
            machine->execute();
        }

        sleepFun();
    }

    if (prev_PC == machine->registers->getPC()) {
        cout << "\nProgram finished" << endl;
    }

    _isRunning = false;
    needToStop = false;
    pthread_exit(NULL);

    return NULL;
}

void start() {
    pthread_t t;
    pthread_create(&t, NULL, threading, NULL);
    pthread_detach(t);
}

void stop() { needToStop = true; }

bool isRunning() { return _isRunning; }

int getSpeed() { return speed; }

void setSpeed(int kHz) { speed = kHz; }

void terminalInput() {
    char c;
    while (true) {
        cin >> c;
        if (c == 'q') {
            stop();
            break;
        } else if (c == 's') {
            stop();
        } else if (c == 'r' && !_isRunning) {
            start();
        } else if (c == 'd') {
            cout << endl;
            machine->displayRegisters();
        } else if (c == 'c') {
            int khz;
            cin >> khz;
            setSpeed(khz);
        } else if (c == 'g') {
            cout << "Current speed: " << speed * 100 << " kHz" << endl;
        } else if (c == 'o') {
            machine->execute();
        } else if(c == 'm') {
            cout << endl;
            machine->memory->display();
            cout << endl;
        }
    }
    //cout << endl;
    //machine->displayRegisters();
}

int main(int argc, char *argv[]) {
    if (argc > 1) // read file
        objFile = std::string(argv[1]);

    if (Utils::readOBJFile(objFile, machine)) {
        cout << "successfully read: " << objFile << endl;
    } else {
        cerr << "Obj file issue!" << endl;
    }

    // controls
    terminalInput();

    // close devices
    machine->~Machine();

    pthread_exit(NULL);
}