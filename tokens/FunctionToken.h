#ifndef FUNCTIONTOKEN_H
#define FUNCTIONTOKEN_H

#include <string>
#include "Token.h"
#include "Variable.h"

class FunctionToken : public Token {
public:
    FunctionToken(string type, string name, vector<Variable> args, Token* body);

    virtual string toString();
    virtual string getType();

    string _type;
    string _name;
    vector<Variable> _args;
    Token* _body;
};

#endif // FUNCTIONTOKEN_H
