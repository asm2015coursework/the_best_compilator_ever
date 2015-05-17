#ifndef ASSIGNMENTTOKEN_H
#define ASSIGNMENTTOKEN_H

#include "Token.h"

class AssignmentToken : public Token {
public:
    AssignmentToken(Token* left, Token* right);

    virtual string toString();
    virtual string getType();

    Token *left;
    Token *right;
};
#endif // ASSIGNMENTTOKEN_H
