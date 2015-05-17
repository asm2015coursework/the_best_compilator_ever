#ifndef CONSTINTTOKEN_H
#define CONSTINTTOKEN_H

#include "Token.h"

class ConstIntToken : public Token {
public:
    ConstIntToken(int value);

    virtual string toString();
    virtual string getType();

    int value;
};


#endif // CONSTINTTOKEN_H
