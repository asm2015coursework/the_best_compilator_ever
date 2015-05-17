#include "IfToken.h"

IfToken::IfToken(Token *expr, Token* block1, Token* block2) {
    this->block1 = block1;
    this->block2 = block2;
    this->expr = expr;
}
