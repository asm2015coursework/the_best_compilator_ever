#include "Parser.h"
#include <ctype.h>

using std::make_pair;

Parser::Parser() {
}

vector<Token*> Parser::parse(string code) {
    str = code;

    //InitializationToken or FunctionToken
    size_t x = 0;
    while (x < str.length()) {
        while (x < str.length() && isspace(str[x])) x++;
        pair<string, int> p = nameParse(x);
        string type = p.first;
        x = p.second;
        while (x < str.length() && isspace(str[x])) x++;
        p = nameParse(x);
        string name = p.first;
        x = p.second;
        while (x < str.length() && isspace(str[x])) x++;

        if (x < str.length() && str[x] == '(') {
            //FunctionToken
            vector<Variable> args;
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            while (x < str.length() && str[x] != ')') {
                while (x < str.length() && isspace(str[x])) x++;
                p = nameParse(x);
                string type = p.first;
                x = p.second;
                while (x < str.length() && isspace(str[x])) x++;
                p = nameParse(x);
                string name = p.first;
                x = p.second;
                while (x < str.length() && isspace(str[x])) x++;
                Variable v(type, name);
                args.push_back(v);
                if (x >= str.length()) break;
                if (str[x] == ')')  break;
                if (str[x] != ',') throw ParsingException(", or ) expected (symbol " + std::string(1, str[x]) +  "" + std::to_string(x) + ")");
                x++;
            }            
            if (x >= str.length()) throw ParsingException("unexpected end of file");
            x++;
            while (x < str.length() && isspace(str[x])) x++;            
            pair<Token*, size_t> res = blockParse(x);
            x = res.second;
            while (x < str.length() && isspace(str[x])) x++;
            ans.push_back(new FunctionToken(type, name, args, res.first));
        } else {
            //InitializationToken
            while (x < str.length() && isspace(str[x])) x++;
            if (x >= str.length()) throw ParsingException("unexpected end of file");
            if (str[x] != ';') throw ParsingException("; expected (symbol " + std::string(1, str[x]) + " " + std::to_string(x) + ")");
            x++;
            while (x < str.length() && isspace(str[x])) x++;            
            ans.push_back(new InitializationToken(type, name, nullptr));
        }
    }


    return ans;
}

pair<Token*, size_t> Parser::commandParse(size_t x) {
    if (nameFirstSymbol(str[x])) {
        // Command
        pair<string, int> p = nameParse(x);
        string name = p.first;
        size_t y = p.second;
        if (y >= str.length()) throw ParsingException("unexpected end of file");
        while (y < str.length() && isspace(str[y])) y++;
        if (nameFirstSymbol(str[y])) {
            //InititalizationToken
            pair<string, int> p = nameParse(y);
            y = p.second;
            while (y < str.length() && isspace(str[y])) y++;
            if (str[y] != ';') throw ParsingException("; expected (symbol " + std::string(1, str[y]) + " " + std::to_string(y) + ")");
            y++;
            while (y < str.length() && isspace(str[y])) y++;
            return make_pair(new InitializationToken(name, p.first, nullptr), y);
        } else {
            //Expression
            return expressionParse(x);
        }
    } else {
        //???
    }    
}

pair<Token*, size_t> Parser::expressionParse(size_t x) {
    // AssignmentToken
    pair<Token*, size_t> cur1 = LexemParse(x);
}

pair<Token*, size_t> Parser::LexemParse(size_t x) {

}

pair<Token*, size_t> Parser::blockParse(size_t x) {
    // { }
    if (str[x] != '{') throw ParsingException("{ expected (symbol " + std::string(1, str[x]) + " " + std::to_string(x) + ")");
    x++;
    while (x < str.length() && isspace(str[x])) x++;
    vector<Token*> ans;
    while (x < str.length() && str[x] != '}') {
        pair<Token*, size_t> res;
        if (str[x] == '{') res = blockParse(x); else res = commandParse(x);
        x = res.second;
        while (x < str.length() && isspace(str[x])) x++;
        ans.push_back(res.first);
    }
    x++;
    while (x < str.length() && isspace(str[x])) x++;
    return make_pair(new BlockToken(ans), x);
}

pair<string, int> Parser::nameParse(size_t x) {    
    if (!nameFirstSymbol(str[x])) throw ParsingException("incorrect name (symbol " + std::string(1, str[x]) + " " + std::to_string(x) + ")");
    string f(1, str[x]);
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
