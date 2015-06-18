#include "StringToken.h"

StringToken::StringToken(string str) {
    this->str = str;
}

string StringToken::toString() {
    return "\"" + str + "\"";
}

string StringToken::getType() {
    return "String";
}
