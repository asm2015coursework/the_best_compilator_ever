#ifndef STRUCTPTRFUNCTIONCALL_H
#define STRUCTPTRFUNCTIONCALL_H

#include "Token.h"

class StructPtrFunctionCallToken : public Token {
public:
    StructPtrFunctionCallToken(Token* expr, string name, vector<Token*> args);

    virtual string toString();
    virtual string getType();

    Token* expr;
    string name;
    vector<Token*> args;
};

#endif // STRUCTPTRFUNCTIONCALL_H
