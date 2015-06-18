#include "IfToken.h"

IfToken::IfToken(Token *expr, Token* block1, Token* block2) {
    this->block1 = block1;
    this->block2 = block2;
    this->expr = expr;
}

string IfToken::getType() {
    return "If";
}

string IfToken::toString() {
    string ans =  "if (" + expr->toString() + ") " + block1->toString() + "";
    if (block2 != nullptr) {
        ans += "; else " + block2->toString() + "";
    }
    return ans;
}
