#include "ConstIntToken.h"

ConstIntToken::ConstIntToken(int value) {
    this->value = value;
}

string ConstIntToken::toString() {
    return std::to_string(value);
}

string ConstIntToken::getType() {
    return "ConstInt";
}
