#include "NotEqualityToken.h"

NotEqualityToken::NotEqualityToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string NotEqualityToken::toString() {
    return "(" + left->toString() + "!=" + right->toString() + ")";
}

string NotEqualityToken::getType() {
    return "NotEquality";
}
