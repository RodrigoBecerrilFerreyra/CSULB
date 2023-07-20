/**
 * Header file for Date library containing calendar date-management functions
 * CECS 275 - Fall 2021
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 2.5
 */
#ifndef DATE_H
#define DATE_H

#include <iostream> // for overloading ostream and istream operators
#include <string> // Used for object creation and concatenation of values
#include "InvalidDay.h"
#include "InvalidMonth.h"

/**
 * "Date" class stores data that represents a user-defined current calendar
 * date. Values of the date are stored as the day, the month, and the year
 * in three separate integers. Class also includes array containing month
 * names for reference purposes and a private leap-year calculator for
 * date verification.
 */
class Date
{
    private:
        int day;       // Date's currently set day
        int month;     // Date's currently recorded month
        int year;      // Date's chosen year
        // Array contains names of each month indexed relative to zero
        const std::string monthNames[12] = {"January","February","March",
                                            "April","May","June","July",
                                            "August","September","October",
                                            "November","December"};

        /**
         * Initialization function used by constructors to quickly set all
         * members of class to base values.
        */
        void defaults(void){
            day = 1; month = 1; year = 2021;// leapYear = false;
            validate();
        }

        /**
         * Performs validation on the day, month, and year inputted.
         * Days over the month's limit become days in the next month.
         * Days over 31 December become days in the next year.
         * Days under the month's limit (non-positive days) become days in the
         * previous month. Days subtracted from 1 January become days in the
         * previous year.
         */
        void validate();

        /**
         * Static function that checks whether or not a day is valid. This
         * function only performs one pass. This uses the same algorithm as
         * Date::validate().
         * @param day_ The day to validate.
         * @param month_ The month to validate.
         * @param year_ The year to validate.
         * @throws InvalidDay if the day does not match the month.
         * @throws InvalidMonth if the month is out of expected range.
         */
        static void isValid(int day_, int month_, int year_);
    public:
        // Constructors
        Date();
        Date(int upDay);
        Date(int upDay,int upMonth);
        Date(int upDay,int upMonth,int upYear);

        // Mutators
        void setDay(int);
        void setMonth(int);
        void setYear(int);

        // Accessors
        /**
         * Accessor member function used to obtain currently-set day.
         * @return The object's current day setting.
        */
        int getDay() const
            { return day; }
        /**
         * Accessor member function used to obtain currently-set month.
         * @return The object's current month setting.
        */
        int getMonth() const
            { return month; }
        /**
         * Accessor member function used to obtain currently-set year.
         * @return The object's current year setting.
        */
        int getYear() const
            { return year; }

        /**
         * Accessor member function that generates the date using the
         * current member variables' values and concatenates into a string
         * delineated by forward-slash marks between values.
         * @return String containing current date in numerical-slash form.
        */
        std::string printNumDate() const
            { std::string sday   = std::to_string(day);
              std::string smonth = std::to_string(month);
              std::string syear  = std::to_string(year);
              std::string print = smonth + "/" + sday + "/" + syear;
              return print; }
        /**
         * Accessor member function that generates the date using the
         * current member variables' values and concatenates into a string
         * format of [(Month) (Day), (Year)].
         * @return String containing current date in middle-endian rendering.
        */
        std::string printCommaDate() const
            { std::string sday   = std::to_string(day);
              std::string smonth = monthNames[month-1];
              std::string syear  = std::to_string(year);
              std::string print = smonth + " " + sday + ", " + syear;
              return print; }
        /**
         * Accessor member function that generates the date using the
         * current member variables' values and concatenates into a string
         * format of [(Day) (Month) (Year)].
         * @return String containing current date in little-endian rendering.
        */
        std::string printDMYDate() const
            { std::string sday   = std::to_string(day);
              std::string smonth = monthNames[month-1];
              std::string syear  = std::to_string(year);
              std::string print = sday + " " + smonth + " " + syear;
              return print; }

        /**
         * Private member function verifies if input is "leap year" value.
         * A year is considered a leap year if it is divisible by 4 unless
         * it is the turn of a century, in which case it must be divisible by
         * 400 instead.
         * @param verify The year to check.
         * @return Truth value of current input's "leap year" validity.
        */
        static bool yearCheck(int verify){
            if (verify%4 == 0) {
                if (verify%100 == 0 && verify%400 == 0) {
                    return true;
                } else if (verify%100 == 0 && verify%400 != 0) {
                    return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        }

        /**
         * Pre-increment operator overload. Adds 1 to the day variable,
         * then returns itself.
         * @return The Date object that called this function (updated).
         */
        Date operator++();

        /**
         * Post-increment operator overload. Makes a copy of itself, adds 1 to
         * the day variable, then returns the copy. The Date returned is
         * the Date before the day was incremented.
         * @return The Date object that called this function (not updated).
         */
        Date operator++(int);

        /**
         * Pre-decrement operator overload. Subtracts 1 to the day variable,
         * then returns itself.
         * @return The Date object that called this function (updated).
         */
        Date operator--();

        /**
         * Post-decrement operator overload. Makes a copy of itself, subtracts 1
         * from the day variable, then returns the copy. The Date returned is
         * the Date before the day was decremented.
         * @return The Date object that called this function (not updated).
         */
        Date operator--(int);

        /**
         * Greater-than operator overload.
         * @returns true if the Date on the left-hand side is later than
         * the Date on the right-hand side; false otherwise.
         */
        bool operator>(const Date &rhs) const;

        /**
         * Subtraction operator overload. Subtracts two Date objects and gives
         * the number of days between them.
         * @param rhs The Date object on the right of the subtraction sign.
         * @return The number of days between the first and second Dates
         * (this value is always non-negative).
         */
        int operator-(const Date &rhs);

        /**
         * Equality operator overload.
         * @param rhs The Date object on the right of the equality operator.
         * @return true if the days, months, and years of both Date objects
         * match, or false if they don't.
         */
        bool operator==(const Date &rhs);

        /**
         * Inequality operator overload.
         * @param rhs The Date object on the right of the inequality operator.
         * @return true if the days, months, and years of both Date objects
         * don't match, or false if they do.
         */
        bool operator!=(const Date &rhs);

        /**
         * Stream extraction operator overload. Outputs the date in the
         * format Month Day, Year.
         * @return The reference to the ostream operator used to allow the
         * chaining of <<.
         */
        friend std::ostream& operator<<(std::ostream &os, const Date &date);

        /**
         * Stream insertion operator overload. Allows the user to input the
         * date. The data is expected in the following order:
         * is >> day >> month >> year;
         * @return The reference to the istream operator used to allow the
         * chaining of >>.
         * @throws InvalidDay if the day does not match the month.
         * @throws InvalidMonth if the month is out of expected range.
         */
        friend std::istream& operator>>(std::istream &is, Date &date);
};

#endif
