#ifndef FUNCTIONTOKEN_H
#define FUNCTIONTOKEN_H

#include <string>
#include "Token.h"
#include "Variable.h"

class FunctionToken : public Token {
public:
    FunctionToken(string type, string name, vector<Variable> args, vector<Token*> body);

    virtual string toString();

    string _type;
    string _name;
    vector<Variable> _args;
    vector<Token*> _body;
};

#endif // FUNCTIONTOKEN_H
