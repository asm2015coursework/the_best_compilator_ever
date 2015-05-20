#ifndef FUNCTIONCALLTOKEN_H
#define FUNCTIONCALLTOKEN_H

#include "Token.h"

class FunctionCallToken : public Token {
public:
    FunctionCallToken(string name, vector<Token*> args);

    virtual string toString();
    virtual string getType();

    string name;
    vector<Token*> args;
};

#endif // FUNCTIONCALLTOKEN_H
