#ifndef COLORMOD
#define COLORMOD

#include <ostream>

enum ColorCode {
    FG_RED        = 31, FG_GREEN        = 32, FG_BLUE         = 34, FG_CLOSE        = 39,
    BG_RED        = 41, BG_GREEN        = 42, BG_BLUE         = 44, BG_CLOSE        = 49,
    BOLD          = 1,  DIM             = 2,  UNDER           = 4,  BLINK           = 5,
    BOLD_CLOSE    = 21, DIM_CLOSE       = 22, UNDER_CLOSE     = 24, BLINK_CLOSE     = 25,
    FG_MAGENTA    = 35, FG_CYAN         = 36, FG_YELLOW       = 33, FG_LRED         = 91
};

class ColorMod{
    ColorCode code;
    int numberCode;
public:
    ColorMod(ColorCode mCode) : code(mCode) {}
    ColorMod(int code) : numberCode(code) {}

    friend std::ostream&
    operator<<(std::ostream& os, const ColorMod& mod){
       if(mod.code)
        return os << "\033[" << mod.code << "m";
       else
        return os << "\033[" << mod.numberCode << "m";

    }

};
#endif
