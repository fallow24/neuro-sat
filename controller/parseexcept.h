#ifndef PARSEEXCEPT_H
#define PARSEEXCEPT_H

#include <exception>
using namespace std;

class ParseExcept : public exception
{
public:
    ParseExcept();
    const char * what() const throw();
};

#endif // PARSEEXCEPT_H
