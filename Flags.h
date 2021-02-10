#ifndef FLAGS_H
#define FLAGS_H

// https://www.gopalancolleges.com/gcem/course-material/computer-science/course-plan/sem-V/system-software-10CS52.pdf
class Flags {
  private:
    static constexpr int SIC = 0x00; // n = 0, i = 0
    static constexpr int IMMEDIATE = 0x01; // i = 1, n = 0
    static constexpr int INDIRECT = 0x02; // i = 0, n = 1
    static constexpr int SIMPLE = 0x03; // i = 0, n = 0 or i = 1, n = 1

    static constexpr int EXTENDED = 0x1; // e = 1
    static constexpr int BASE_RELATIVE = 0x4; // b = 1, p = 0
    static constexpr int PC_RELATIVE = 0x2; // b = 0, p = 1
    static constexpr int NONE = 0x0; 
    static constexpr int INDEXED = 0x8; // x = 1

    int ni;
    int xbpe;

  public:
    Flags(int ni, int xbpe) {
        this->ni = (ni & 0x03);
        this->xbpe = xbpe >> 4;
    }

    bool isSic() { return ni == SIC; }

    bool isImmediate() { return ni == IMMEDIATE; }

    bool isIndirect() { return ni == INDIRECT; }

    bool isSimple() { return (ni == SIMPLE) || (ni == NONE); }

    bool isExtended() { return (xbpe & EXTENDED) == EXTENDED; }

    bool isBaseRelative() { return (xbpe & BASE_RELATIVE) == BASE_RELATIVE; }

    bool isPCRelative() { return (xbpe & PC_RELATIVE) == PC_RELATIVE; }

    bool isAbsolute() { return xbpe == NONE; }

    bool isIndexed() { return (xbpe & INDEXED) == INDEXED; }

    // either b or p equal to 1 and the other one to 0
    bool isRelative() { return isPCRelative() || isBaseRelative(); }

    // https://ucilnica.fri.uni-lj.si/pluginfile.php/95005/mod_resource/content/0/05%20-%20Emulation.pdf
    // SIC/XE instruction format
    int operandSic(int a, int b) { return ((a & 0x7F) << 8) | (b & 0xFF); }

    // -2048 <= disp <= 2047
    int operandPCRelative(int a) { return a > 2047 ? a - 4096 : a; }

    int operandF4(int a, int b, int c) {
        return ((a & 0x7F) << 16) | (b << 8) | c;
    }

    int operandF3(int a, int b) { return (a & 0x0F) << 8 | b; }
};

#endif