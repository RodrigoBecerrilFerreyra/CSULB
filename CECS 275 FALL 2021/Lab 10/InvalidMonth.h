/**
 * Header file for InvalidMonth error class.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef INVALIDMONTH_H
#define INVALIDMONTH_H

#include <exception>

/**
 * This class should be thrown if the month is not valid.
 * Extends std::exception.
 */
class InvalidMonth : std::exception
{
    public:
        /**
         * Initializes variables and creates the error message.
         * @param month The month that caused the error.
         */
        InvalidMonth(int month);

        /**
         * Frees up memory taken by errormessage.
         */
        virtual ~InvalidMonth();

        /**
         * Virtual function that returns the error message.
         * @return The error message (null-terminated).
         */
        virtual const char* what () const noexcept;
    private:
        int month;
        char* errormessage;
};

#endif//INVALIDMONTH_H
