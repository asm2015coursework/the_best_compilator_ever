#ifndef STRUCTTOKEN_H
#define STRUCTTOKEN_H

#include "Token.h"
#include "InitializationToken.h"
#include "FunctionToken.h"

class StructToken : public Token {
public:
    StructToken(string name, vector<InitializationToken*> variables, vector<FunctionToken*> functions);

    virtual string getType();
    virtual string toString();

    string name;
    vector<InitializationToken*> variables;
    vector<FunctionToken*> functions;
};

#endif // STRUCTTOKEN_H
