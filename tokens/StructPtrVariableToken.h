#ifndef STRUCTPTRVARIABLETOKEN_H
#define STRUCTPTRVARIABLETOKEN_H

#include "Token.h"

class StructPtrVariableToken : public Token {
public:
    StructPtrVariableToken(Token* expr, string name);

    virtual string toString();
    virtual string getType();

    Token* expr;
    string name;
};

#endif // STRUCTPTRVARIABLETOKEN_H
