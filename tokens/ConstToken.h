#ifndef CONSTTOKEN_H
#define CONSTTOKEN_H

#include "Token.h"

class ConstToken : public Token {
public:
    ConstToken(string value);

    virtual string toString();

    string _value;
};

#endif // CONSTTOKEN_H
