/**
 * Implementation file for InvalidMonth error class
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <cstdio>
#include "InvalidMonth.h"

InvalidMonth::InvalidMonth(int month)
{
    this->month = month;
    errormessage = new char[78];

    // snprintf protects against long user strings
    snprintf(errormessage, 78, "Invalid month: received %02d, but months should be between 01 and 12 inclusive.", month);
}

InvalidMonth::~InvalidMonth()
{
    delete[] errormessage;
    errormessage = nullptr;
}

const char* InvalidMonth::what() const noexcept
{
    return errormessage;
}
