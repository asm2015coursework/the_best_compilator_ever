#include "BlockToken.h"

BlockToken::BlockToken(vector<Token*> commands) {
    this->_commands = commands;
}

string BlockToken::toString() {
    string ans = "{\n";
    for (size_t i = 0; i < _commands.size(); i++) {
        ans += _commands[i]->toString() + ";\n";
    }
    ans += "}";
    return ans;
}
