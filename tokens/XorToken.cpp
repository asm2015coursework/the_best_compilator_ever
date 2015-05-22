#include "XorToken.h"

XorToken::XorToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string XorToken::toString() {
    return "(" + left->toString() + "-" + right->toString() + ")";
}

string XorToken::getType() {
    return "Subtract";
}
