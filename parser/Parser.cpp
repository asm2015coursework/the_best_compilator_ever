#include "Parser.h"
#include <ctype.h>

Parser::Parser() {
}

vector<Token*> Parser::parse(string code) {
    str = code;

    //InitializationToken or FunctionToken
    size_t x = 0;
    while (x < str.length()) {
        pair<string, int> p = nameParse(x);
        string type = p.first;
        x = p.second;
        p = nameParse(x);
        string name = p.first;
        x = p.second;

        if (x < str.length() && str[x] == '(') {
            //FunctionToken
            vector<Variable> args;
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            while (x < str.length() && str[x] != ')') {
                p = nameParse(x);
                type = p.first;
                x = p.second;
                p = nameParse(x);
                name = p.first;
                x = p.second;
                while (x < str.length() && isspace(str[x])) x++;
                if (x >= str.length() || (str[x] != ',' && str[x] != ')')) throw ParsingException("','' or ')' expected");
                Variable v(type, name);
                args.push_back(v);
                x++;
            }

        } else {
            //InitializationToken
            while (x < str.length() && isspace(str[x])) x++;
            if (x >= str.length() || str[x] != ';') throw ParsingException("; expected (symbol " + std::to_string(x) + ")");
            x++;
            ans.push_back(new InitializationToken(type, name, nullptr));
        }
    }


    return ans;
}

Result Parser::commandParse(size_t x) {
    //return Result(new EqualityToken(, ), x + 1);
}

pair<string, int> Parser::nameParse(size_t x) {
    while (x < str.length() && isspace(str[x])) x++;
    if (!nameFirstSymbol(str[x])) throw ParsingException("incorrect name (symbol " + std::to_string(x) + ")");
    string f = "" + str[x];
    size_t i = x + 1;

    while (i < str.length() && nameSymbol(str[i])) {
        f += str[i];
        i++;
    }

    return make_pair(f, i);
}

bool Parser::nameSymbol(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c <= '9' && c >= '0') || c == '_') return true;
        else return false;
}

bool Parser::nameFirstSymbol(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') return true;
        else return false;
}

bool Parser::letter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
        else return false;
}
