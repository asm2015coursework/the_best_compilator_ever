#include "InitializationToken.h"

InitializationToken::InitializationToken(string type, string name, Token *expr) {
    this->_name = name;
    this->_type = type;
    this->_expr = expr;
}

string InitializationToken::toString() {
    string ans = _type + " " + _name;
    if (_expr != nullptr) ans += _expr->toString(); else ans += "";
    return ans;
}

string InitializationToken::getType() {
    return "Initialization";
}
