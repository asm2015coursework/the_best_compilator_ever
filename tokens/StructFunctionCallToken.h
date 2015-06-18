#ifndef STRUCTFUNCTIONCALLTOKEN_H
#define STRUCTFUNCTIONCALLTOKEN_H

#include "Token.h"

class StructFunctionCallToken : public Token {
public:
    StructFunctionCallToken(Token* expr, string name, vector<Token*> args);

    virtual string toString();
    virtual string getType();

    Token* expr;
    string name;
    vector<Token*> args;
};

#endif // STRUCTFUNCTIONCALLTOKEN_H
