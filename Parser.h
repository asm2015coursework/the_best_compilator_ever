#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class Parser
{
public:
    Parser();
    static std::vector<std::string> parse(std::string code);
};

#endif // PARSER_H
