#ifndef ADDRESSTOKEN_H
#define ADDRESSTOKEN_H

#include "Token.h"

class AddressToken : public Token {
public:
    AddressToken(Token *expr);

    virtual string toString();
    virtual string getType();

    Token* expr;
};

#endif // ADDRESSTOKEN_H
