#ifndef CONSTINTTOKEN_H
#define CONSTINTTOKEN_H

#include "Token.h"

class ConstIntToken : public Token {
public:
    ConstIntToken(long long value);

    virtual string toString();
    virtual string getType();

    long long value;
};


#endif // CONSTINTTOKEN_H
