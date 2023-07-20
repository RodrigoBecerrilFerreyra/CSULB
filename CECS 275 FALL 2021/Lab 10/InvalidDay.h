/**
 * Header file for InvalidDay error class.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef INVALIDDAY_H
#define INVALIDDAY_H

#include <exception>

/**
 * This class should be thrown if the day is not valid. Extends std::exception.
 */
class InvalidDay : public std::exception
{
    public:
        /**
         * Initializes the error variables.
         * @param day The day that triggered the exception.
         * @param month The month that the day should be in.
         * @param leapYear True if the year is a leapyear, false if not.
         */
        InvalidDay(int day, int month, bool leapYear);

        /**
         * Overrides std::exception function what().
         * @return A null-terminated string detailing what went wrong.
         */
        virtual const char* what() const noexcept;

        /**
         * Frees memory taken by errormessage.
         */
        virtual ~InvalidDay();
    private:
        int day;
        int month;
        char* errormessage;
};

#endif//INVALIDDAY_H
