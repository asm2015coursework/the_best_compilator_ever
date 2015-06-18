#include "GreaterToken.h"

GreaterToken::GreaterToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string GreaterToken::toString() {
    return "(" + left->toString() + ">" + right->toString() + ")";
}

string GreaterToken::getType() {
    return "Greater";
}
