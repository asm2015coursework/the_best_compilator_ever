#include "LowerToken.h"

LowerToken::LowerToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string LowerToken::toString() {
    return "(" + left->toString() + "<" + right->toString() + ")";
}

string LowerToken::getType() {
    return "Lower";
}
