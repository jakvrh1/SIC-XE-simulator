#ifndef MACHINE_H
#define MACHINE_H

#include <bitset>
#include <iomanip>
#include <iostream>

#include "Devices.h"
#include "Flags.h"
#include "Memory.h"
#include "Opcode.h"
#include "Registers.h"

//#define DEBUG

class Machine {
  public:
    Registers *registers;
    Memory *memory;
    Devices *devices;

    Machine() {
        this->registers = new Registers();
        this->memory = new Memory(Memory::MAX_ADDRESS);
        this->devices = new Devices(Devices::MAX_DEVICES);
    }

    ~Machine() { this->devices->~Devices(); }

    void displayRegisters() {
        /*std::bitset<6> A(registers->getA());
        std::bitset<6> X(registers->getX());
        std::bitset<6> L(registers->getL());
        std::bitset<6> S(registers->getS());
        std::bitset<6> T(registers->getT());
        std::bitset<6> B(registers->getB());
        std::bitset<6> SW(registers->getSW());
        std::bitset<6> PC(registers->getPC());
        std::bitset<12> F(registers->getF());

        std::cout << "A|" << A << "\tX|" << X << "\tL|" << L << "\n";
        std::cout << "S|" << S << "\tT|" << T << "\tB|" << B << "\n";
        std::cout << "SW|" << SW << "\tF|" << F << "\n";
        std::cout << "PC|" << PC << std::endl;
        */
        int A = registers->getA();
        int X = registers->getX();
        int L = registers->getL();
        int S = registers->getS();
        int T = registers->getT();
        int B = registers->getB();
        int SW = registers->getSW();
        int PC = registers->getPC();
        int F = registers->getF();

        std::ios oldState(nullptr);
        oldState.copyfmt(std::cout);

        std::cout << std::setbase(16);
        std::cout << " A|" << std::setfill('0') << std::setw(6) << A << "\tX|"
                  << std::setfill('0') << std::setw(6) << X << "\tL|"
                  << std::setfill('0') << std::setw(6) << L << "\n";
        std::cout << " S|" << std::setfill('0') << std::setw(6) << S << "\tT|"
                  << std::setfill('0') << std::setw(6) << T << "\tB|"
                  << std::setfill('0') << std::setw(6) << B << "\n";
        std::cout << "SW|" << std::setfill('0') << std::setw(6) << SW << "\tF|"
                  << std::setfill('0') << std::setw(12) << F << "\n";
        std::cout << "PC|" << std::setfill('0') << std::setw(6) << PC
                  << std::endl;

        std::cout.copyfmt(oldState);
    }

    void invalidOpcode(const int &opcode) {
        std::cerr
            << "Executor tried to execute the opcode which is not defined [ "
            << opcode << " ]" << std::endl;
    }

    void invalidAddressing() {
        std::cerr << "Invalid addressing bits" << std::endl;
    }

    int fetch() {
        int b = memory->getByte(registers->getPC());
        registers->incPC();
        return b;
    }

    void debug_print(std::string name) {
#ifdef DEBUG
        std::cout << "Called Opcode::" << name << std::endl;
#endif
    }

    bool execF1(const int &opcode) {
        switch (opcode) {
        case Opcode::FIX:
            registers->setA(registers->getF());
            return true;
        case Opcode::FLOAT:
            registers->setF(registers->getA());
            return true;
        case Opcode::HIO:
            invalidOpcode(opcode);
            return true;
        case Opcode::TIO:
            invalidOpcode(opcode);
            return true;
        case Opcode::SIO:
            invalidOpcode(opcode);
            return true;
        }
        return false;
    }

    bool execF2(const int &opcode, const int &op) {
        int op1 = (op & 0xF0) >> 4;
        int op2 = (0x0F & op);

        Registers &r = *this->registers;

        switch (opcode) {
        case Opcode::ADDR:
            debug_print("ADDR");
            r.setReg(op2, r.getReg(op2) + r.getReg(op1));
            return true;
        case Opcode::CLEAR:
            debug_print("CLEAR");
            r.setReg(op1, 0);
            return true;
        case Opcode::COMPR:
            debug_print("COMPR");
            r.setSW(r.getReg(op1) - r.getReg(op2));
            return true;
        case Opcode::DIVR:
            debug_print("DIVR");
            r.setReg(op2, r.getReg(op2) / r.getReg(op1));
            return true;
        case Opcode::MULR:
            debug_print("MULR");
            r.setReg(op2, r.getReg(op2) * r.getReg(op1));
            return true;
        case Opcode::RMO:
            debug_print("RMO");
            r.setReg(op2, r.getReg(op1));
            return true;
        case Opcode::SHIFTL:
            debug_print("SHIFTL");
            r.setReg(op1, r.getReg(op1) << (op2 + 1));
            return true;
        case Opcode::SHIFTR:
            debug_print("SHIFTR");
            r.setReg(op1, (r.getReg(op1) >> (op2 + 1)));
            return true;
        case Opcode::SUBR:
            debug_print("SUBR");
            r.setReg(op2, r.getReg(op2) - r.getReg(op1));
            return true;
        case Opcode::SVC:
            debug_print("SVC");
            invalidOpcode(opcode);
            return true;
        case Opcode::TIXR:
            debug_print("TIXR");
            r.setX(r.getX() + 1);
            r.setSW(r.getX() - r.getReg(op1));
            return true;
        }
        return false;
    }

    bool execF3F4(const int opcode, Flags &flags, const int operand) {
        Registers &r = *this->registers;
        Memory &m = *this->memory;

        switch (opcode) {
        case Opcode::ADD:
            debug_print("ADD");
            r.setA(r.getA() + loadWord(flags, operand));
            return true;
        case Opcode::ADDF:
            debug_print("ADDF");
            invalidOpcode(opcode);
            return true;
        case Opcode::AND:
            debug_print("AND");
            r.setA(r.getA() & loadWord(flags, operand));
            return true;
        case Opcode::COMP:
            debug_print("COMP");
            r.setSW(r.getA() - loadWord(flags, operand));
            return true;
        case Opcode::COMPF:
            debug_print("COMP");
            invalidOpcode(operand);
            return true;
        case Opcode::DIV:
            debug_print("DIV");
            r.setA(r.getA() / loadWord(flags, operand));
            return true;
        case Opcode::DIVF:
            debug_print("DIVF");
            invalidOpcode(operand);
            return true;
        case Opcode::J:
            debug_print("J");
            r.setPC(storeAddr(flags, operand));
            return true;
        case Opcode::JEQ:
            debug_print("JEQ");
            if (r.isEqual()) r.setPC(storeAddr(flags, operand));
            return true;
        case Opcode::JGT:
            debug_print("JGT");
            if (r.isGreater()) r.setPC(storeAddr(flags, operand));
            return true;
        case Opcode::JLT:
            debug_print("JLT");
            if (r.isLower()) r.setPC(storeAddr(flags, operand));
            return true;
        case Opcode::JSUB:
            debug_print("JSUB");
            r.setL(r.getPC());
            r.setPC(storeAddr(flags, operand));
            return true;
        case Opcode::LDA:
            debug_print("LDA");
            r.setA(loadWord(flags, operand));
            return true;
        case Opcode::LDB:
            debug_print("LDB");
            r.setB(loadWord(flags, operand));
            return true;
        case Opcode::LDCH:
            debug_print("LDCH");
            r.setLastByteA(loadByte(flags, operand));
            return true;
        case Opcode::LDF:
            debug_print("LDF");
            invalidOpcode(opcode);
            return true;
        case Opcode::LDL:
            debug_print("LDL");
            r.setL(loadWord(flags, operand));
            return true;
        case Opcode::LDS:
            debug_print("LDS");
            r.setS(loadWord(flags, operand));
            return true;
        case Opcode::LDT:
            debug_print("LDT");
            r.setT(loadWord(flags, operand));
            return true;
        case Opcode::LDX:
            debug_print("LDX");
            r.setX(loadWord(flags, operand));
            return true;
        case Opcode::LPS:
            debug_print("LPS");
            invalidOpcode(opcode);
            return true;
        case Opcode::MUL:
            debug_print("MUL");
            r.setA(r.getA() * loadWord(flags, operand));
            return true;
        case Opcode::MULF:
            debug_print("MULF");
            invalidOpcode(opcode);
            return true;
        case Opcode::OR:
            debug_print("OR");
            r.setA(r.getA() | loadWord(flags, operand));
            return true;
        case Opcode::RD:
            debug_print("RD");
            r.setLastByteA(devices->read(loadByte(flags, operand)));
            return true;
        case Opcode::RSUB:
            debug_print("RSUB");
            r.setPC(r.getL());
            return true;
        case Opcode::SSK:
            debug_print("SSK");
            invalidOpcode(opcode);
            return true;
        case Opcode::STA:
            debug_print("STA");
            m.setWord(storeAddr(flags, operand), r.getA());
            return true;
        case Opcode::STB:
            debug_print("STB");
            m.setWord(storeAddr(flags, operand), r.getB());
            return true;
        case Opcode::STCH:
            debug_print("STCH");
            m.setByte(storeAddr(flags, operand), r.getA());
            return true;
        case Opcode::STF:
            debug_print("STF");
            invalidOpcode(opcode);
            return true;
        case Opcode::STI:
            debug_print("STI");
            invalidOpcode(opcode);
            return true;
        case Opcode::STL:
            debug_print("STL");
            m.setWord(storeAddr(flags, operand), r.getL());
            return true;
        case Opcode::STS:
            debug_print("STS");
            m.setWord(storeAddr(flags, operand), r.getS());
            return true;
        case Opcode::STSW:
            debug_print("STSW");
            m.setWord(storeAddr(flags, operand), r.getSW());
            return true;
        case Opcode::STT:
            debug_print("STT");
            m.setWord(storeAddr(flags, operand), r.getT());
            return true;
        case Opcode::STX:
            debug_print("STX");
            m.setWord(storeAddr(flags, operand), r.getX());
            return true;
        case Opcode::SUB:
            debug_print("SUB");
            r.setA(r.getA() - loadWord(flags, operand));
            return true;
        case Opcode::SUBF:
            debug_print("SUBF");
            invalidOpcode(opcode);
            return true;
        case Opcode::TD:
            debug_print("TD");
            r.setSW(devices->test(loadByte(flags, operand)) ? -1 : 0);
            return true;
        case Opcode::TIX:
            debug_print("TIX");
            r.setX(r.getX() + 1);
            r.setSW(r.getX() - loadWord(flags, operand));
            return true;
        case Opcode::WD:
            debug_print("WD");
            devices->write(loadByte(flags, operand), r.getLastByteA());
            return true;
        }

        return false;
    }

    void execute() {
        int opcode = fetch();

        if (execF1(opcode)) return;

        int op = fetch();

        if (execF2(opcode, op)) return;

        Flags flags(opcode, op);
        int operand = 0;

        if (flags.isSic()) {
            operand = flags.operandSic(op, fetch());
        } else if (flags.isExtended()) {
            operand = flags.operandF4(op, fetch(), fetch());
            if (flags.isRelative()) invalidAddressing();
        } else {
            operand = flags.operandF3(op, fetch());
            if (flags.isPCRelative()) {
                operand = flags.operandPCRelative(operand) + registers->getPC();
            } else if (flags.isBaseRelative())
                operand += registers->getB();
            else if (!flags.isAbsolute())
                invalidAddressing();
        }

        if (flags.isIndexed()) {
            if (flags.isSimple())
                operand += registers->getX();
            else
                invalidAddressing();
        }

        if (execF3F4(opcode & 0xFC, flags, operand)) return;

        invalidOpcode(opcode);
    }

  private:
    int storeAddr(Flags &flags, const int &addr) {
        if (flags.isIndirect()) return memory->getWord(addr);
        return addr;
    }

    int loadWord(Flags flags, int operand) {
        if (flags.isImmediate()) return operand;
        operand = memory->getWord(operand);
        if (flags.isIndirect()) operand = memory->getWord(operand);
        return operand;
    }

    int loadByte(Flags flags, int operand) {
        if (flags.isImmediate()) return operand;
        if (flags.isIndirect())
            return memory->getByte(memory->getWord(operand));
        return memory->getByte(operand);
    }
};

#endif