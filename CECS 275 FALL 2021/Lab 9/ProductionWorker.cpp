/**
 * Production Worker class implementation file.
 * CECS 275 - Fall 2021
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 1
 */

#include "ProductionWorker.h"
#include "Employee.h"
#include <string>

/**
 * Class constructor for a known employee (including ID and hire date),  
 * their hourly earnings, and their assigned shift.
 * @return "Production Worker" that works at X time that makes Y amount. 
*/
ProductionWorker::ProductionWorker(std::string empName, int empID, 
                                   std::string hireDate, int empShift,
                                   double empWage)
                : Employee(empName, empID, hireDate){
    minWage();
    setShift(empShift);
    setWages(empWage);
}

/**
 * Mutator member function that attempts to assign the employee with their 
 * corresponding shift timing if given a valid shift; otherwise maintains 
 * their current shift (or default).
 * @param newShift Integer value of 1 or 2 representing worker's shift.
*/
void ProductionWorker::setShift(int newShift){
    // Verify that the employee's shift is one of two valid values.
    if ( (newShift == 1) || (newShift == 2) ) {
        shift = newShift;
    } else {
        shift = shift;
    }
}

/**
 * Mutator member function that attempts to set the employee to their 
 * appropriate hourly compensation assuming that they are being paid 
 * a positive amount of money; otherwise maintains their current 
 * wages (or default).
 * @param newWage Worker's hourly payment rate.
*/
void ProductionWorker::setWages(double newWage){
    // Verify that the employee is actually being paid.
    if (newWage > 0) {
        hourWages = newWage;
    } else {
        hourWages = hourWages;
    }
}

/**
 * Private function used by constructors to quickly default to given 
 * arbitrary values before user's new information is known.
*/
void ProductionWorker::minWage(){
    // Default assumption is a day shift.
    shift = 1;
    // Default assumption is a payment of USD$15.50/hour.
    hourWages = 15.50;
}
