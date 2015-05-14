#include "DivideToken.h"

DivideToken::DivideToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string DivideToken::toString() {
    return "(" + left->toString() + "+" + right->toString() + ")";
}
