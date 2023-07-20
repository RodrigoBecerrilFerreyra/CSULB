/**
 * Implementation file for InvalidDay error class
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <cstdio>
#include "InvalidDay.h"

InvalidDay::InvalidDay(int day, int month, bool leapYear)
{
    this->day = day;
    this->month = month;
    // the error message is 94 characters plus \0, I counted
    errormessage = new char[95];

    int daycap;
    if(month == 2) // February
        daycap = leapYear ? 29 : 28;
    else if(month == 4 || month == 6 || month == 9 || month == 11)
        daycap = 30;
    else // 1, 3, 5, 7, 8, 10, 12
        daycap = 31;

    // even though I counted, I'm still using snprintf instead of sprintf
    //   for reliability (in case user inputs a large positive or
    //   negative number)
    snprintf(errormessage, 95, "Invalid day: received day %02d for month %02d, but the highest day is %02d and the lowest day is 01.", day, month, daycap);
}

InvalidDay::~InvalidDay()
{
    delete[] errormessage;
    errormessage = nullptr;
}

const char* InvalidDay::what() const noexcept
{
    return errormessage;
}
