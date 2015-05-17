#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <string>

using std::string;
using std::vector;

class Token {
public:        
    virtual string toString() = 0; // for testing
    virtual string getType() = 0;
};

#endif // TOKEN_H
