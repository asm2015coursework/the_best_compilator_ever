#ifndef BREAKTOKEN_H
#define BREAKTOKEN_H

#include "Token.h"

class BreakToken : public Token {
public:
    BreakToken();

    virtual string toString();
    virtual string getType();
};

#endif // BREAKTOKEN_H
