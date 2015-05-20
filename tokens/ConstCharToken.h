#ifndef CONSTCHARTOKEN_H
#define CONSTCHARTOKEN_H

#include "Token.h"

class ConstCharToken : public Token {
public:
    ConstCharToken(char value);

    virtual string toString();
    virtual string getType();

    char value;
};

#endif // CONSTCHARTOKEN_H
