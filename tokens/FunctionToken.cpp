#include "FunctionToken.h"

FunctionToken::FunctionToken(string type, string name, vector<Variable> args, vector<Token*> body) {
    this->_type = type;
    this->_name = name;
    this->_args = args;
    this->_body = body;
}

string FunctionToken::toString() {
    string ans = _type + " " + _name + "(";
    for (size_t i = 0; i < _args.size() - 1; i++) {
        ans += _args[i]._type + " " + _args[i]._name + ",";
    }
    ans += _args[_args.size() - 1]._type + " " + _args[_args.size() - 1]._name + ") {\n";
    for (size_t i = 0; i < _body.size(); i++) {
        ans += _body[i]->toString() + "\n";
    }
    ans += "}\n";
    return ans;
}
