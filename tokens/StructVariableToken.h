#ifndef STRUCTVARIABLETOKEN_H
#define STRUCTVARIABLETOKEN_H

#include "Token.h"

class StructVariableToken : public Token {
public:
    StructVariableToken(Token* expr, string name);

    virtual string toString();
    virtual string getType();

    Token* expr;
    string name;
};

#endif // STRUCTVARIABLETOKEN_H
