/**
 * Library containing class Date that manages calendar date formatting.
 * CECS 275 - Fall 2021
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 2.5
 */
#include <iostream> // for << and >> overloading
#include "Date.h" // Associated header file

/**
 * Default class constructor for a no-parameter object creation.
 * Loads up pre-defined default values into member variables.
 * @return Date object defaulted to date of Jan./1, 1, 2021
*/
Date::Date(){
    defaults();
}

/**
 * Class constructor for object creation that has custom day.
 * Loads up pre-defined default values into member variables, then
 * attempts to overwrite current day with input parameter day if
 * detected as valid.
 * @return Date object with updated day if applicable.
*/
Date::Date(int upDay){
    defaults();
    setDay(upDay);
}

/**
 * Class constructor for object creation that has custom day & month.
 * Loads up pre-defined default values into member variables, then
 * attempts to overwrite current month and current day with input parameter
 * month then input parameter day in that order.
 * @return Date object with updated day & month if applicable.
*/
Date::Date(int upDay,int upMonth){
    defaults();
    setMonth(upMonth);
    setDay(upDay);
}

/**
 * Class constructor for object creation that has wholly custom date.
 * Loads up pre-defined default values into member variables, then
 * attempts to overwrite current year, current month, and current day
 * with input parameter year, input parameter month, and input parameter
 * day in that order.
 * @return Customized date object where valid inputs were fed.
*/
Date::Date(int upDay,int upMonth,int upYear){
    defaults();
    setYear(upYear);
    setMonth(upMonth);
    setDay(upDay);
}

void Date::validate()
{
    // The upper limit on the number of days depending on the month.
    int daycap, prevmonthdaycap;
    // holds whether or not the year is a leap year
    int leapYear;

    // This do-while loop fixes anything wrong with the dates iteratively.
    // It only exits when everything is in good working order.
    // If even one thing was changed, the loop will restart when finished.
    while(true)
    {
        // Do not accept non-positive years.
        if(year < 1)
            year = 1900;

        // positive month validation
        if(month > 12)
        {
            month -= 12;
            ++year;
            continue;
        }
        // negative month validation
        if(month < 1)
        {
            month = 12 - month;
            --year;
            continue;
        }
        
        leapYear = yearCheck(year);

        // The following block of code calculates the maximum amount of
        // days a month can have.
        if(month == 2) // February
            daycap = leapYear ? 29 : 28;
        else if(month == 4 || month == 6 || month == 9 || month == 11)
            daycap = 30;
        else // 1, 3, 5, 7, 8, 10, 12
            daycap = 31;

        // Same as above, but for the previous month.
        if(month == 3)
            prevmonthdaycap = leapYear ? 29 : 28;
        else if(month == 5 || month == 7 || month == 10 || month == 12)
            prevmonthdaycap = 30;
        else // 1, 2, 4, 6, 8, 9, 11
            prevmonthdaycap = 31;

        // positive day validation
        if(day > daycap)
        {
            day -= daycap;
            ++month;
            continue;
        }
        // negative day validation
        if(day < 1)
        {
            day = prevmonthdaycap + day;
            --month;
            continue;
        }
        // The code only reaches this break statement if no date
        // manipulation has occurred.
        break;
    }
}

bool Date::isValid(int day_, int month_, int year_)
{
    // Do not accept non-positive years.
    if(year_ < 1)
        return false;

    // month validation
    if(month_ > 12 || month_ < 1)
        return false;
    
    int leapYear_ = yearCheck(year_);
    int daycap;

    // The following block of code calculates the maximum amount of
    // days a month can have.
    if(month_ == 2) // February
        daycap = leapYear_ ? 29 : 28;
    else if(month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11)
        daycap = 30;
    else // 1, 3, 5, 7, 8, 10, 12
        daycap = 31;

    // day validation
    if(day_ > daycap || day_ < 1)
        return false;

    return true;
}

/**
 * Mutator member function that attempts to overwrite the object's current
 * day with the new input parameter day.
 * @param upDay   The desired new day to change to.
*/
void Date::setDay(int upDay){
   day = upDay;
   validate();
}

/**
 * Mutator member function that attempts to overwrite the object's current
 * month with the new input parameter month.
 * @param upMonth   The desired new month to change to.
*/
void Date::setMonth(int upMonth){
    month = upMonth;
    validate();
}

/**
 * Mutator member function that attempts to overwrite the object's current
 * year with the new input parameter year. If the input is not within
 * expected bounds, the current value of "year" is preserved.
 * @param upYear   The desired new year to change to.
*/
void Date::setYear(int upYear){
    year = upYear;
    validate();
}

Date Date::operator++()
{
    ++day;
    validate();
    return *this;
}

Date Date::operator++(int)
{
    Date temp = *this;
    day++;
    validate();
    return temp;
}

Date Date::operator--()
{
    --day;
    validate();
    return *this;
}

Date Date::operator--(int)
{
    Date temp = *this;
    day--;
    validate();
    return temp;
}

bool Date::operator>(const Date &rhs) const
{
    if(year > rhs.year)
        return true;
    else if(year == rhs.year)
    {
        if(month > rhs.month)
            return true;
        else if(month == rhs.month)
        {
            if(day > rhs.day)
                return true;
        }
    }
    return false;
}

bool Date::operator==(const Date &rhs)
{
    if(day == rhs.day && month == rhs.month && year == rhs.year)
        return true;
    return false;
}

bool Date::operator!=(const Date &rhs)
{
    if(day != rhs.day || month != rhs.month || year != rhs.year)
        return true;
    return false;
}

int Date::operator-(const Date &rhs)
{
    int daysPassed = 0;
    
    // The way this works is that the function picks the lower Date, then
    // increments (a copy of) the lower date until the lower date matches the
    // upper date. The function counts how many times the lower date was
    // incremented, and returns this value.

    // if(*this == rhs) then the functions returns 0
    // else
    if(*this > rhs)
    {
        Date temp = rhs; // we need to modify the lower Date
        while(temp != *this) // *this is the higher Date
        {
            ++temp;
            ++daysPassed;
        }
    }
    else if (rhs > *this)
    {
        Date temp = *this; // *this is the lower Date this time
        while(temp != rhs) // rhs is the higher Date
        {
            ++temp;
            ++daysPassed;
        }
    }

    return daysPassed;
}

std::ostream& operator<<(std::ostream &os, const Date &date)
{
    os << date.printCommaDate();
    return os;
}

std::istream& operator>>(std::istream &is, Date &date)
{
    // get values from istream object
    int tempday, tempmonth, tempyear;
    is >> tempday >> tempmonth >> tempyear;
    
    // The following block only update values if they are valid.
    // The best way to handle invalidity is to throw an exception,
    // but we technically have not learned that yet, so there is currently
    // no way for the callee to know if the input is invalid.
    // If I could use the Date::validate() function, I could accept any date,
    // even invalid ones (the validate() function would fix these dates),
    // but the textbook says that >> should not accept invalid dates,
    // so I have no choice but to comply.
    if(Date::isValid(tempday, tempmonth, tempyear))
    {
        date.setDay(tempday);
        date.setMonth(tempmonth);
        date.setYear(tempyear);
    }

    return is;
}
