#ifndef DEREFERENCETOKEN_H
#define DEREFERENCETOKEN_H

#include "Token.h"

class DereferenceToken : public Token {
public:
    DereferenceToken(Token *expr);

    virtual string toString();
    virtual string getType();

    Token* expr;
};

#endif // DEREFERENCETOKEN_H
