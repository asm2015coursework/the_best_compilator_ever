#include "ConstCharToken.h"

ConstCharToken::ConstCharToken(char value) {
    this->value = value;
}

string ConstCharToken::toString() {
    string ans(1, value);
    if (value == '\n') ans = "\\n";
    if (value == '\t') ans = "\\t";
    if (value == '\0') ans = "\\0";
    return "'" + ans + "'";
}

string ConstCharToken::getType() {
    return "ConstChar";
}
