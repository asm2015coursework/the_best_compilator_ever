#ifndef PARSINGEXCEPTION_H
#define PARSINGEXCEPTION_H

#include <exception>
#include <stdexcept>

using std::string;

class ParsingException : public std::runtime_error {
public:    
    ParsingException(string msg) : std::runtime_error(msg) {}
    ParsingException(int place, char expected, char found) : std::runtime_error("'" + std::string(1, expected) +  "' expected at " + std::to_string(place) + " (found symbol '" + std::string(1, found) + "')") {}
};

#endif // PARSINGEXCEPTION_H
