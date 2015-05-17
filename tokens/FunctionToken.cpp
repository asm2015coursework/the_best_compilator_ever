#include "FunctionToken.h"

FunctionToken::FunctionToken(string type, string name, vector<Variable> args, Token *body) {
    this->_type = type;
    this->_name = name;
    this->_args = args;
    this->_body = body;
}

string FunctionToken::toString() {
    string ans = _type + " " + _name + "(";
    if (_args.size() > 0) {
        for (size_t i = 0; i < _args.size() - 1; i++) {
            ans += _args[i]._type + " " + _args[i]._name + ", ";
        }
        ans += _args[_args.size() - 1]._type + " " + _args[_args.size() - 1]._name + ")\n";
    } else ans += ")\n";
    ans += _body->toString();
    return ans;
}

string FunctionToken::getType() {
    return "Function";
}
