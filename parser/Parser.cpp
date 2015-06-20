#include "Parser.h"
#include <ctype.h>

using std::make_pair;

Parser::Parser() {
    types.insert("int");    
    types.insert("char");
}

vector<Token*> Parser::parse(string code) {
    str = code;

    //InitializationToken or FunctionToken
    size_t x = 0;
    while (x < str.length()) {
        while (x < str.length() && isspace(str[x])) x++;
        int y = x;
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
        if (x > str.length()) throw ParsingException("unexpected end of file");
        if (str[x] == '(') {
            //FunctionToken            
            pair<FunctionToken*, size_t> p = functionParse(y);
            ans.push_back(p.first);
            x = p.second;
        } else if (type == "struct") {
            vector<InitializationToken*> variables;
            vector<FunctionToken*> functions;
            if (str[x] != '{') throw ParsingException(x, '{', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            while (x < str.length() && str[x] != '}') {
                int y = x;
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
                if (str[x] == '(') {
                    pair<FunctionToken*, size_t> p = functionParse(y);
                    functions.push_back(p.first);
                    x = p.second;
                } else {
                    pair<InitializationToken*, size_t> p = initializationParse(y);
                    variables.push_back(p.first);
                    x = p.second;
                }
            }
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            types.insert(name);
            ans.push_back(new StructToken(name, variables, functions));
        } else {
            pair<InitializationToken*, size_t> p = initializationParse(y);
            ans.push_back(p.first);
            x = p.second;
        }
    }

    return ans;
}

pair<FunctionToken*, size_t> Parser::functionParse(size_t x) {
    //FunctionToken
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
    if (str[x] != '(') throw ParsingException(x, '(', str[x]);
    x++;
    while (x < str.length() && isspace(str[x])) x++;

    vector<Variable> args;
    while (x < str.length() && str[x] != ')') {
        while (x < str.length() && isspace(str[x])) x++;
        p = nameParse(x);
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
    if (str[x] != '{') throw ParsingException("function's body expected at " + x);
    pair<BlockToken*, size_t> res = blockParse(x);
    x = res.second;
    while (x < str.length() && isspace(str[x])) x++;
    return make_pair(new FunctionToken(type, name, args, res.first), x);
}

pair<InitializationToken*, size_t> Parser::initializationParse(size_t x) {
    //InititalizationToken
    Token *size = nullptr;
    Token *expr = nullptr;
    pair<string, int> p = nameParse(x);
    string name = p.first;
    x = p.second;
    while (x < str.length() && (str[x] == '*' || str[x] == '&')) {
        name += str[x];
        x++;
        while (x < str.length() && isspace(str[x])) x++;
    }
    pair<string, int> p2 = nameParse(x);
    x = p2.second;
    if (str[x] == '[') {
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> p = expressionParse(x);
        size = p.first;
        x = p.second;
        if (str[x] != ']') throw ParsingException(x, ']', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
    }
    if (str[x] == '=') {
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> p = expressionParse(x);
        expr = p.first;
        x = p.second;
    }
    if (str[x] != ';') throw ParsingException(x, ';', str[x]);
    x++;
    while (x < str.length() && isspace(str[x])) x++;
    return make_pair(new InitializationToken(name, p2.first, expr, size), x);
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
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            while (x < str.length() && str[x] != '}') {
                f += str[x];
                x++;
            }
            if (x >= str.length()) throw ParsingException("unexpected end of file");
            if (str[x] != '}') throw ParsingException(x, '}', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            return make_pair(new AsmToken(f), x);
        } else if (name == "if") {
            //IfToken            
            x += 2;
            while (x < str.length() && isspace(str[x])) x++;
            if (x >= str.length()) throw ParsingException("unexpected end of file");
            if (str[x] != '(') throw ParsingException(x, '(', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            pair<Token*, size_t> p = expressionParse(x);
            Token* expr = p.first;
            x = p.second;
            if (str[x] != ')') throw ParsingException(x, ')', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            if (str[x] == '{') p = blockParse(x); else p = commandParse(x);
            Token* block1 = p.first;
            x = p.second;
            string f = "";
            y = x;
            while (y < str.length() && y - x < 4) {
                f += str[y];
                y++;
            }
            if (f == "else") {
                x = y;
                while (x < str.length() && isspace(str[x])) x++;
                if (str[x] == '{') p = blockParse(x); else p = commandParse(x);
                Token* block2 = p.first;
                x = p.second;
                return make_pair(new IfToken(expr, block1, block2), x);
            } else {
                return make_pair(new IfToken(expr, block1, nullptr), x);
            }
        } else if (name == "for") {
            //ForToken            
            Token* expr1 = nullptr, *expr2 = nullptr, *expr3 = nullptr, *cmd = nullptr;
            x += 3;
            while (x < str.length() && isspace(str[x])) x++;
            if (str[x] != '(') throw ParsingException(x, '(', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            if (types.find(nameParse(x).first) != types.end()) {
                pair <Token*, size_t> p = initializationParse(x);
                expr1 = p.first;
                x = p.second;
            } else {
                pair <Token*, size_t> p = expressionParse(x);
                expr1 = p.first;
                x = p.second;
                if (str[x] != ';') throw ParsingException(x, ';', str[x]);
                x++;
                while (x < str.length() && isspace(str[x])) x++;
            }
            pair <Token*, size_t> p2 = expressionParse(x);
            expr2 = p2.first;
            x = p2.second;
            if (str[x] != ';') throw ParsingException(x, ';', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            pair <Token*, size_t> p3 = expressionParse(x);
            expr3 = p3.first;
            x = p3.second;
            if (str[x] != ')') throw ParsingException(x, ')', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            if (str[x] == '{') {
                pair <Token* , size_t> p3 = blockParse(x);
                cmd = p3.first;
                x = p3.second;
            } else {
                pair <Token* , size_t> p3 = commandParse(x);
                cmd = p3.first;
                x = p3.second;
            }
            return make_pair(new ForToken(expr1, expr2, expr3, cmd), x);
        } else if (name == "while") {
            //WhileToken
            x += 5;
            while (x < str.length() && isspace(str[x])) x++;
            if (str[x] != '(') throw ParsingException(x, '(', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            pair<Token*, size_t> p = expressionParse(x);
            x = p.second;
            if (str[x] != ')') throw ParsingException(x, ')', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            pair<Token*, size_t> p2;
            if (str[x] == '{') {
                p2 = blockParse(x);
            } else {
                p2 = commandParse(x);
            }
            x = p2.second;
            return make_pair(new WhileToken(p.first, p2.first), x);
        } else  if (name == "break") {
            //BreakToken
            x += 5;
            while (x < str.length() && isspace(str[x])) x++;
            if (str[x] != ';') throw ParsingException(x, ';', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            return make_pair(new BreakToken(), x);
        } else  if (name == "continue") {
            //ContinueToken
            x += 8;
            while (x < str.length() && isspace(str[x])) x++;
            if (str[x] != ';') throw ParsingException(x, ';', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            return make_pair(new ContinueToken(), x);
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
            return initializationParse(x);
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

pair<Token*, size_t> Parser::equalityParse(size_t x) {
    //EqualityToken
    pair<Token*, size_t> cur1 = greaterLowerParse(x);
    x = cur1.second;
    while (x + 1 < str.length() && str[x] != ')' && str[x] != ';' && ((str[x] == '=' && str[x + 1] == '=') || (str[x] == '!' && str[x + 1] == '=')) ) {
        char oprtn = str[x];
        if (str[x + 1] != '=') throw ParsingException(x, '=', str[x]);
        x += 2;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = greaterLowerParse(x);
        x = cur2.second;
        if (oprtn == '!') {
            cur1.first = new NotEqualityToken(cur1.first, cur2.first);
        } else {
            cur1.first = new EqualityToken(cur1.first, cur2.first);
        }
    }
    return make_pair(cur1.first, x);
}

pair<Token*, size_t> Parser::greaterLowerParse(size_t x) {
    //GreaterToken or LowerToken or GreaterEqualityToken or LowerEqualityToken
    pair<Token*, size_t> cur1 = addSubtractParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && (str[x] == '<' || str[x] == '>')) {
        char oprtn = str[x];
        x++;
        bool eq = false;
        if (str[x] == '=') {
            eq = true;
            x++;
        }
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = addSubtractParse(x);
        x = cur2.second;
        if (oprtn == '<') {
            if (!eq) cur1.first = new LowerToken(cur1.first, cur2.first);
                else cur1.first = new LowerEqualityToken(cur1.first, cur2.first);
        } else {
            if (!eq) cur1.first = new GreaterToken(cur1.first, cur2.first);
                else cur1.first = new GreaterEqualityToken(cur1.first, cur2.first);
        }
    }
    return make_pair(cur1.first, x);

}

pair<Token*, size_t> Parser::orParse(size_t x) {
    //OrToken
    pair<Token*, size_t> cur1 = xorParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && str[x] == '|') {
        char oprtn = str[x];
        if (oprtn != '|') throw ParsingException(x, '|', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = xorParse(x);
        x = cur2.second;
        cur1.first = new OrToken(cur1.first, cur2.first);
    }
    return make_pair(cur1.first, x);
}

pair<Token*, size_t> Parser::xorParse(size_t x) {
    //XorToken
    pair<Token*, size_t> cur1 = andParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && str[x] == '^') {
        char oprtn = str[x];
        if (oprtn != '^') throw ParsingException(x, '^', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = andParse(x);
        x = cur2.second;
        cur1.first = new XorToken(cur1.first, cur2.first);
    }
    return make_pair(cur1.first, x);
}

pair<Token*, size_t> Parser::andParse(size_t x) {
    //AndToken
    pair<Token*, size_t> cur1 = equalityParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && str[x] == '&') {
        char oprtn = str[x];
        if (oprtn != '&') throw ParsingException(x, '&', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = equalityParse(x);
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
    //MultiplyToken or DivideToken or ModToken
    pair<Token*, size_t> cur1 = unaryParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && (str[x] == '*' || str[x] == '/' || str[x] == '%')) {
        char oprtn = str[x];
        if (oprtn != '*' && oprtn != '/' && oprtn != '%') throw ParsingException(x, '*', str[x]);
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> cur2 = unaryParse(x);
        x = cur2.second;
        if (oprtn == '*') {
            cur1.first = new MultiplyToken(cur1.first, cur2.first);
        } else if (oprtn == '/') {
            cur1.first = new DivideToken(cur1.first, cur2.first);
        } else {
            cur1.first = new ModToken(cur1.first, cur2.first);
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
    } else if (str[x] == '!') {
        //NotToken
        x++;
        while (x < str.length() && isspace(str[x])) x++;
        pair<Token*, size_t> p = unaryParse(x);
        return make_pair(new NotToken(p.first), p.second);
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
    } else {
        return structVariableOrFunctionParse(x);
    }
}

pair<Token*, size_t> Parser::structVariableOrFunctionParse(size_t x) {
    //StructVariableToken or StructFunctionCallToken
    pair<Token*, size_t> cur1 = constOrVariableOrFunctionParse(x);
    x = cur1.second;
    while (x < str.length() && str[x] != ')' && str[x] != ';' && ((str[x] == '.') || (str[x] == '-' && x + 1 < str.length() && str[x + 1] == '>'))) {
        char oprtn = str[x];
        if (oprtn == '.') x++; else x += 2;
        while (x < str.length() && isspace(str[x])) x++;
        pair<string, size_t> cur2 = nameParse(x);
        x = cur2.second;
        vector<Token*> args;
        if (str[x] == '(') {
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            while (x < str.length() && str[x] != ')') {
                pair<Token*, size_t> p = expressionParse(x);
                args.push_back(p.first);
                x = p.second;
                if (str[x] == ')') break;
                if (str[x] != ',') throw ParsingException("expected argument of function " + cur2.first);
                x++;
                while (x < str.length() && isspace(str[x])) x++;
            }
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            if (oprtn == '.') {
                cur1.first = new StructFunctionCallToken(cur1.first, cur2.first, args);
            } else {
                cur1.first = new StructPtrFunctionCallToken(cur1.first, cur2.first, args);
            }
        } else {
            if (oprtn == '.') {
                cur1.first = new StructVariableToken(cur1.first, cur2.first);
            } else {
                cur1.first = new StructPtrVariableToken(cur1.first, cur2.first);
            }
        }
    }
    return make_pair(cur1.first, x);
}

pair<Token*, size_t> Parser::constOrVariableOrFunctionParse(size_t x) {
    if (nameFirstSymbol(str[x])){
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
        } else if (str[p.second] == '[') {
            //ArrayCallToken
            x = p.second;
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            pair<Token*, size_t> p = expressionParse(x);
            x = p.second;
            if (str[x] != ']') throw ParsingException(x, ']', str[x]);
            x++;
            while (x < str.length() && isspace(str[x])) x++;
            return make_pair(new ArrayCallToken(name, p.first), x);
        } else {
            //VariableToken
            return variableParse(x);
        }
    } else if (str[x] >= '0' && str[x] <= '9') {
        return constIntParse(x);
    } else if (str[x] == '\'') {
        return constCharParse(x);
    } else  if (str[x] == '"') {
        return constStringParse(x);
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

pair<Token*, size_t> Parser::constStringParse(size_t x) {
    x++;
    while (x < str.length() && isspace(str[x])) x++;
    string f = "";
    while (x < str.length() && str[x] != '"') {
        f += str[x];
        x++;
    }
    x++;
    while (x < str.length() && isspace(str[x])) x++;
    return make_pair(new StringToken(f), x);
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

pair<BlockToken*, size_t> Parser::blockParse(size_t x) {
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
