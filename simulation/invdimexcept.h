#ifndef INVDIMEXCEPT_H
#define INVDIMEXCEPT_H

#include <exception>
using namespace std;

class InvDimExcept : public exception
{
public:
    InvDimExcept();
    const char * what() const throw();
};

#endif // INVDIMEXCEPT_H
