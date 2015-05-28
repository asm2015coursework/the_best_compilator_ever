#ifndef ARRAYCALLTOKEN_H
#define ARRAYCALLTOKEN_H

#include "Token.h"

class ArrayCallToken : public Token {
public:
    ArrayCallToken(string name, Token* expr);

    virtual string toString();
    virtual string getType();

    string name;
    Token* expr;
};

#endif // ARRAYCALLTOKEN_H
