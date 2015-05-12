#ifndef VARIABLETOKEN_H
#define VARIABLETOKEN_H

#include "Token.h"

class VariableToken : public Token {
public:
    VariableToken(string name);

    virtual string toString();

    string _name;
};
#endif // VARIABLETOKEN_H
