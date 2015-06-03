#include "GreaterEqualityToken.h"

GreaterEqualityToken::GreaterEqualityToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string GreaterEqualityToken::toString() {
    return "(" + left->toString() + ">=" + right->toString() + ")";
}

string GreaterEqualityToken::getType() {
    return "GreaterEquality";
}
