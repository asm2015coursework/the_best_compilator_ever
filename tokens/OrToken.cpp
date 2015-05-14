#include "OrToken.h"

OrToken::OrToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string OrToken::toString() {
    return "(" + left->toString() + "|" + right->toString() + ")";
}
