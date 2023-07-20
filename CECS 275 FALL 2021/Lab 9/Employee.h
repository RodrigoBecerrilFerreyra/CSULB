/**
 * Employee class header file.
 * CECS 275 - Fall 2021
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 1.21
 */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string> // Used for storing employee's name and date hired.

/**
 * "Employee" class stores data about a given workplace's employee as an
 * object, intended to be used as a base class for further specific
 * workplace needs.
*/
class Employee
{
    private:
        std::string employeeName;
        int employeeNumber;
        std::string hireDate; // NOTE: Professor recommended use of string.
        void setDefaults();
    public:
        // Constructors
        Employee();
        Employee(std::string);
        Employee(std::string,int);
        Employee(std::string,int,std::string);

        // Mutators
        void setName(std::string);
        void setNumber(int);
        void setDate(std::string);

        // Accessors
        /**
         * Accessor member function used to obtain employee's name.
         * @return Target employee name.
        */
        std::string getName() const
            { return employeeName; }
        /**
         * Accessor member function used to obtain employee's numerical ID. 
         * @return Target employee identification number.
        */
        int getNumber() const
            { return employeeNumber; }
        /**
         * Accessor member function used to obtain date of employment.
         * @return Target employee's date they were initially hired.
        */
        std::string getDate() const
            { return hireDate; }
};

#endif
