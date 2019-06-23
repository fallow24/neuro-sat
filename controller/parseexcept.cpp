#include "parseexcept.h"

ParseExcept::ParseExcept()
{

}

const char * ParseExcept::what() const throw() {
    return "File has corrupted dnn format.";
}
