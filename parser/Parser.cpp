#include "Parser.h"
#include <ctype.h>

using std::make_pair;

Parser::Parser() {
    types.insert("int");
    types.insert("long");
    types.insert("char");
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
        while (x < str.length() && (str[x] == '*' || str[x] == '&')) {
            type += str[x];
            x++;
            while (x < str.length() && isspace(str[x])) x++;
        }
        p = nameParse(x);
        string name = p.first;
        x = p.second;        

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
                p = nameParse(x);
                string name = p.first;
                x = p.second;                
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
        if (name == "asm") {
            x = y;
            string f = "";
            while (x < str.length() && isspace(str[x])) x++;
            if (str[x] != '{') throw ParsingException(x, '{', str[x]);
            while (x < str.length() && str[x] != '}') {
                f += str[x];
                x++;
            }
            if (x >= str.length()) throw ParsingException("unexpected end of file");
            f += str[x];
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            return make_pair(new AsmToken(f), x);
        } else if (name == "if") {
            //IfToken

        } else if (name == "for") {
            //ForToken

        } else if (name == "while") {
            //WhileToken

        } else if (name == "return") {
            //ReturnToken
            x += 6;
            while (x < str.length() && isspace(str[x])) x++;
            if (str[x] == ';') {
                if (str[x] != ';') throw ParsingException(x, ';', str[x]);
                x++;
                while (x < str.length() && isspace(str[x])) x++;
                return make_pair(new ReturnToken(nullptr), x);
            }
            pair<Token*, size_t> p = expressionParse(x);
            x = p.second;
            if (str[x] != ';') throw ParsingException(x, ';', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            return make_pair(new ReturnToken(p.first), x);
        } else if (types.find(name) != types.end()) {
            //InititalizationToken
            while (y < str.length() && (str[y] == '*' || str[y] == '&')) {
                name += str[y];
                y++;
                while (y < str.length() && isspace(str[y])) y++;
            }
            pair<string, int> p = nameParse(y);
            y = p.second;
            if (str[y] != ';') throw ParsingException(y, ';', str[y]);
            y++;                    
            while (y < str.length() && isspace(str[y])) y++;
            return make_pair(new InitializationToken(name, p.first, nullptr), y);
        } else {
            //Expression
            pair<Token*, size_t> p = expressionParse(x);
            x = p.second;
            if (str[x] != ';') throw ParsingException(x, ';', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            return make_pair(p.first, x);
        }
    } else {
        //Expression
        pair<Token*, size_t> p = expressionParse(x);
        x = p.second;
        if (str[x] != ';') throw ParsingException(x, ';', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        return make_pair(p.first, x);
    }
}

pair<Token*, size_t> Parser::expressionParse(size_t x) {
    // AssignmentToken
    pair<Token*, size_t> cur1 = orParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && str[x] == '=') {
        char oprtn = str[x];
        if (oprtn != '=') throw ParsingException(x, '=', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = expressionParse(x);
        x = cur2.second;
        cur1.first = new AssignmentToken(cur1.first, cur2.first);
    }
    return make_pair(cur1.first, x);
}

pair<Token*, size_t> Parser::orParse(size_t x) {
    //OrToken
    pair<Token*, size_t> cur1 = andParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && str[x] == '|') {
        char oprtn = str[x];
        if (oprtn != '|') throw ParsingException(x, '|', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = andParse(x);
        x = cur2.second;
        cur1.first = new OrToken(cur1.first, cur2.first);
    }
    return make_pair(cur1.first, x);
}

pair<Token*, size_t> Parser::andParse(size_t x) {
    //AndToken
    pair<Token*, size_t> cur1 = addSubtractParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && str[x] == '&') {
        char oprtn = str[x];
        if (oprtn != '&') throw ParsingException(x, '&', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = addSubtractParse(x);
        x = cur2.second;
        cur1.first = new AndToken(cur1.first, cur2.first);
    }
    return make_pair(cur1.first, x);
}

pair<Token*, size_t> Parser::addSubtractParse(size_t x) {
    //AddToken or SubtractToken
    pair<Token*, size_t> cur1 = multiplyDivideParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && (str[x] == '+' || str[x] == '-')) {
        char oprtn = str[x];
        if (oprtn != '+' && oprtn != '-') throw ParsingException(x, '+', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = multiplyDivideParse(x);
        x = cur2.second;
        if (oprtn == '+') {
            cur1.first = new AddToken(cur1.first, cur2.first);
        } else { //oprtn == '-'
            cur1.first = new SubtractToken(cur1.first, cur2.first);
        }
    }
    return make_pair(cur1.first, x);
}

pair<Token*, size_t> Parser::multiplyDivideParse(size_t x) {
    //MultiplyToken or DivideToken
    pair<Token*, size_t> cur1 = unaryParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && (str[x] == '*' || str[x] == '/')) {
        char oprtn = str[x];
        if (oprtn != '*' && oprtn != '/') throw ParsingException(x, '*', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = unaryParse(x);
        x = cur2.second;
        if (oprtn == '*') {
            cur1.first = new MultiplyToken(cur1.first, cur2.first);
        } else { //oprtn == '/'
            cur1.first = new DivideToken(cur1.first, cur2.first);
        }
    }
    return make_pair(cur1.first, x);
}

pair<Token*, size_t> Parser::unaryParse(size_t x) {
    if (str[x] == '*') {
        //DereferenceToken
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> p = unaryParse(x);
        return make_pair(new DereferenceToken(p.first), p.second);
    } else if (str[x] == '&') {
        //AddressToken
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> p = unaryParse(x);
        return make_pair(new AddressToken(p.first), p.second);
    } else if (str[x] == '-') {
        //UnaryMinusToken
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> p = unaryParse(x);
        return make_pair(new UnaryMinusToken(p.first), p.second);
    } else if (str[x] == '+') {
        //UnaryPlusToken
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> p = unaryParse(x);
        return make_pair(new UnaryPlusToken(p.first), p.second);
    } else if (nameFirstSymbol(str[x])){
        pair<string, size_t> p = nameParse(x);
        string name = p.first;
        if (str[p.second] == '(') {
            //FunctionCallToken
            x = p.second;
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            vector<Token*> args;
            while (x < str.length() && str[x] != ')') {
                pair<Token*, size_t> p = expressionParse(x);
                args.push_back(p.first);
                x = p.second;
                if (str[x] == ')') break;
                if (str[x] != ',') throw ParsingException("expected argument of function " + name);
                x++;
                while (x < str.length() && isspace(str[x])) x++;
            }
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            return make_pair(new FunctionCallToken(name, args), x);
        } else {
            //VariableToken
            return variableParse(x);
        }
    } else if (str[x] >= '0' && str[x] <= '9') {
        return constIntParse(x);
    } else if (str[x] == '\'') {
        return constCharParse(x);
    } else { //if (str[x] == '(') { // brackets
        if (str[x] != '(') throw ParsingException(x, '(', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> p = expressionParse(x);
        x = p.second;
        if (str[x] != ')') throw ParsingException(x, ')', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        return make_pair(p.first, x);
    }
}

pair<Token*, size_t> Parser::constIntParse(size_t x) {
    string f = "";
    while (str[x] >= '0' && str[x] <= '9') {
        f += str[x];
        x++;
    }
    while (x < str.length() && isspace(str[x])) x++;
    int v = std::stoi(f);
    return make_pair(new ConstIntToken(v), x);
}

pair<Token*, size_t> Parser::constCharParse(size_t x) {
    x++;
    while (x < str.length() && isspace(str[x])) x++;
    string f = "";
    while (x < str.length() && str[x] != '\'') {
        f += str[x];
        x++;
    }
    if (x >= str.length()) throw ParsingException("unexpected end of file");
    if (f.length() > 2) throw ParsingException("wrong character constant");
    x++;
    while (x < str.length() && isspace(str[x])) x++;
    char v = f[0];
    if (v == '\\') {
        if (f[1] == 'n') v = '\n'; else
        if (f[1] == 't') v = '\t'; else
        if (f[1] == '0') v = '\0'; else v = f[1];
    }
    return make_pair(new ConstCharToken(v), x);
}

pair<Token*, size_t> Parser::variableParse(size_t x) {
    //VariableToken
    pair<string, size_t> p = nameParse(x);    
    return make_pair(new VariableToken(p.first), p.second);
}

pair<Token*, size_t> Parser::blockParse(size_t x) {
    // { }
    if (str[x] != '{') throw ParsingException(x, '{', str[x]);
    x++;
    while (x < str.length() && isspace(str[x])) x++;
    vector<Token*> ans;
    while (x < str.length() && str[x] != '}') {
        pair<Token*, size_t> res;
        if (str[x] == '{') res = blockParse(x); else res = commandParse(x);
        x = res.second;        
        ans.push_back(res.first);
    }
    x++;
    while (x < str.length() && isspace(str[x])) x++;
    return make_pair(new BlockToken(ans), x);
}

pair<string, size_t> Parser::nameParse(size_t x) {
    if (!nameFirstSymbol(str[x])) throw ParsingException("incorrect name (found symbol '" + std::string(1, str[x]) + "' at " + std::to_string(x) + ")");
    string f(1, str[x]);
    size_t i = x + 1;

    while (i < str.length() && nameSymbol(str[i])) {
        f += str[i];
        i++;
    }

    while (i < str.length() && isspace(str[i])) i++;

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
