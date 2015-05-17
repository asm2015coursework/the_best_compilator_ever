#include "AddToken.h"

AddToken::AddToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string AddToken::toString() {
    return "(" + left->toString() + "+" + right->toString() + ")";
}

string AddToken::getType() {
    return "Add";
}
