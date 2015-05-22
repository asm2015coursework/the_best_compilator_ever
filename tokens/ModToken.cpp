#include "ModToken.h"


ModToken::ModToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string ModToken::toString() {
    return "(" + left->toString() + "%" + right->toString() + ")";
}

string ModToken::getType() {
    return "Multiply";
}
