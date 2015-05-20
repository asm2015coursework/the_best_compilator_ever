#ifndef ASMTOKEN_H
#define ASMTOKEN_H

#include "Token.h"

class AsmToken : public Token {
public:
    AsmToken(string code);

    string toString();
    string getType();

    string code;
};

#endif // ASMTOKEN_H
