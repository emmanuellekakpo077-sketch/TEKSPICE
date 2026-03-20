#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <exception>
#include <iostream>
#include <string>

class Errors: public std::exception {
    public:
        Errors(std::ostream &os, const std::string &message) throw() : _message(message), _os(os) {};
        ~Errors(void){};
    
        const char *what(void) const throw() {
            return _message.c_str();
        }
    
    private:
        std::string _message;
        std::ostream &_os;
    };
    #endif