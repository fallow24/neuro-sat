#include "invdimexcept.h"

InvDimExcept::InvDimExcept()
{

}

const char * InvDimExcept::what() const throw() {
    return "Output of controller doesnt fit number of wheels";
}
