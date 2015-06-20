#include "AsmToken.h"

AsmToken::AsmToken(string code) {
    this->code = code;
}

string AsmToken::toString() {
    return "asm {" + code + "}";
}

string AsmToken::getType() {
    return "Asm";
}
