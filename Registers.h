#ifndef REGISTERS_H
#define REGISTERS_H

typedef int i_register;
typedef float f_register;

class Registers {
  private:
    static constexpr int REG_NO_A = 0;
    static constexpr int REG_NO_X = 1;
    static constexpr int REG_NO_L = 2;
    static constexpr int REG_NO_B = 3;
    static constexpr int REG_NO_S = 4;
    static constexpr int REG_NO_T = 5;

    i_register A, X, L, B, S, T;
    f_register F;
    i_register PC;
    i_register CC;

  public:
    Registers() { resetRegisters(); }

    i_register getA() { return this->A; }
    i_register getX() { return this->X; }
    i_register getL() { return this->L; }
    i_register getB() { return this->B; }
    i_register getS() { return this->S; }
    i_register getT() { return this->T; }
    f_register getF() { return this->F; }
    i_register getPC() { return this->PC; }

    i_register getSW() {
        if (CC == 0)
            return 0;
        else if (CC > 0)
            return 0x80;
        else
            return 0x40;
    }

    i_register getReg(int regno) {
        switch (regno) {
        case Registers::REG_NO_A:
            return getA();
        case Registers::REG_NO_X:
            return getX();
        case Registers::REG_NO_L:
            return getL();
        case Registers::REG_NO_B:
            return getB();
        case Registers::REG_NO_S:
            return getS();
        case Registers::REG_NO_T:
            return getT();
        }
        return 0;
    }

    int getLastByteA() { return this->A & 0xFF; }

    bool isEqual() { return CC == 0; }

    bool isGreater() { return CC > 0; }

    bool isLower() { return CC < 0; }

    void setSW(int val) { CC = val; }

    void setReg(int regno, int val) {
        switch (regno) {
        case Registers::REG_NO_A:
            setA(val);
            break;
        case Registers::REG_NO_X:
            setX(val);
            break;
        case Registers::REG_NO_L:
            setL(val);
            break;
        case Registers::REG_NO_B:
            setB(val);
            break;
        case Registers::REG_NO_S:
            setS(val);
            break;
        case Registers::REG_NO_T:
            setT(val);
            break;
        }
    }

    void setA(i_register val) { this->A = val; }
    void setX(i_register val) { this->X = val; }
    void setL(i_register val) { this->L = val; }
    void setB(i_register val) { this->B = val; }
    void setS(i_register val) { this->S = val; }
    void setT(i_register val) { this->T = val; }
    void setF(f_register val) { this->F = val; }

    void setLastByteA(int val) {
        this->A = this->A & 0x00;
        this->A = this->A | (val & 0xFF);
    }

    void setPC(i_register val) { this->PC = val; }
    i_register incPC() { return ++this->PC; }

    void resetRegisters() {
        A = X = L = B = S = T = 0;
        F = 0;
        PC = 0;
        CC = 0;
    }
};

#endif