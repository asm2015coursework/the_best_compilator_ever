#ifndef BLOCKTOKEN_H
#define BLOCKTOKEN_H

#include <vector>
#include <string>
#include "Token.h"
#include "Variable.h"

class BlockToken : public Token {
public:
    BlockToken(vector<Token*> commands);

    virtual string toString();

    vector<Token*> _commands;
};

#endif // BLOCKTOKEN_H
