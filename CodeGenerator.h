#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include <vector>

class CodeGenerator
{
public:
    CodeGenerator();
    static std::string generate(std::vector<std::string>);
};

#endif // CODE_GENERATOR_H
