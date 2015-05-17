#include "EqualityToken.h"

EqualityToken::EqualityToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string EqualityToken::toString() {
    return "(" + left->toString() + "==" + right->toString() + ")";
}

string EqualityToken::getType() {
    return "Equality";
}
