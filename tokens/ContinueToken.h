#ifndef CONTINUETOKEN_H
#define CONTINUETOKEN_H

#include "Token.h"

class ContinueToken : public Token {
public:
    ContinueToken();

    virtual string toString();
    virtual string getType();
};

#endif // CONTINUETOKEN_H
