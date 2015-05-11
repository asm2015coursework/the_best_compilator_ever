#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include <vector>

class code_generator
{
public:
    code_generator();
    static std::string generate(std::vector<std::string>);
};

#endif // CODE_GENERATOR_H
