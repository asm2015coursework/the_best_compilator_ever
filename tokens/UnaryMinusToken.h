#ifndef UNARYMINUSTOKEN_H
#define UNARYMINUSTOKEN_H

#include "Token.h"

class UnaryMinusToken : public Token {
public:
    UnaryMinusToken(Token *expr);

    virtual string toString();
    virtual string getType();

    Token* expr;
};

#endif // UNARYMINUSTOKEN_H
