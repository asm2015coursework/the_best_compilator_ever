#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class parser
{
public:
    parser();
    static std::vector<std::string> parse(std::string code);
};

#endif // PARSER_H
