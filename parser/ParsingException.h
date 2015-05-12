#ifndef PARSINGEXCEPTION_H
#define PARSINGEXCEPTION_H

#include <exception>
#include <stdexcept>

using std::string;

class ParsingException : public std::runtime_error {
public:    
    ParsingException(string msg) : std::runtime_error(msg) {}
};

#endif // PARSINGEXCEPTION_H
