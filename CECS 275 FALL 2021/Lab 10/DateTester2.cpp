/**
 * Header file for InvalidDay error class.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
// Including excpetion is not strictly necessary, since the program includes
//   Date.h which includes InvalidDay.h which includes exception.
#include <exception>
#include "Date.h"

int main()
{
    Date* myDate = nullptr;
    // test day constructor only
    try
    {
        myDate = new Date(99);
    }
    catch(InvalidDay &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(InvalidMonth &e)
    {
        std::cerr << e.what() << std::endl;
    }
    delete myDate; myDate = nullptr;

    // now test the day and month constructor
    try
    {
        myDate = new Date(12, 99);
    }
    catch(InvalidDay &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(InvalidMonth &e)
    {
        std::cerr << e.what() << std::endl;
    }
    delete myDate; myDate = nullptr;

    try
    {
        myDate = new Date(99, 12);
    }
    catch(InvalidDay &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(InvalidMonth &e)
    {
        std::cerr << e.what() << std::endl;
    }
    delete myDate; myDate = nullptr;

    // lastly, try the same, but with the year parameter as well
    try
    {
        myDate = new Date(12, 99, 1999);
    }
    catch(InvalidDay &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(InvalidMonth &e)
    {
        std::cerr << e.what() << std::endl;
    }
    delete myDate; myDate = nullptr;

    try
    {
        myDate = new Date(99, 12, 1999);
    }
    catch(InvalidDay &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(InvalidMonth &e)
    {
        std::cerr << e.what() << std::endl;
    }
    delete myDate; myDate = nullptr;

    // try the individual set functions
    myDate = new Date;
    try
    {
        myDate->setDay(99);
    }
    catch(InvalidDay &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(InvalidMonth &e)
    {
        std::cerr << e.what() << std::endl;
    }
    delete myDate; myDate = nullptr;
    
    myDate = new Date;
    try
    {
        myDate->setMonth(99);
    }
    catch(InvalidDay &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(InvalidMonth &e)
    {
        std::cerr << e.what() << std::endl;
    }
    delete myDate; myDate = nullptr;

    // test stream insertion operator
    myDate = new Date;

    try
    {
        std::cout << "Please enter a date in DD MM YYYY format: ";
        std::cin >> *myDate;
    }
    catch(InvalidDay &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(InvalidMonth &e)
    {
        std::cerr << e.what() << std::endl;
    }

    delete myDate; myDate = nullptr;
    return 0;
}
