#ifndef UNARYPLUSTOKEN_H
#define UNARYPLUSTOKEN_H

#include "Token.h"

class UnaryPlusToken : public Token {
public:
    UnaryPlusToken(Token *expr);

    virtual string toString();
    virtual string getType();

    Token* expr;
};

#endif // UNARYPLUSTOKEN_H
