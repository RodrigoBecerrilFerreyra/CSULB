/**
 * Production Worker class header file.
 * CECS 275 - Fall 2021
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 1
 */

#ifndef PRODUCTIONWORKER_H
#define PRODUCTIONWORKER_H

#include <string>
#include "Employee.h"

/**
 * "Production Worker" class acts as an extension of the "Employee" 
 * base class. Associates the employee's identifying characteristics 
 * with the shift they work (assuming a binary shift schedule) and 
 * their wages earned.
*/
class ProductionWorker : public Employee
{
    private:
        int shift;
        double hourWages;
        /* 
        NOTE: Chapter 15 Programming Challenges 1 notes that a "shift" of 
        1 should correspond to a Day shift and that a "shift" of 2 should 
        correspond to a Night shift. This array is used to implement this 
        relation by way of indexing.
        */
        const std::string shiftHalves[3] = {"None","Day","Night"};
        void minWage();
    public:
        // Constructors
        /**
         * Default class constructor for a no-parameter object creation. 
         * Loads pre-defined default values into member variables.
         * @return Worker with a presumed minimum wage and day shift.
        */
        ProductionWorker() : Employee()
            { minWage(); }
        ProductionWorker(std::string,int,std::string,int,double);
        
        // Mutators
        void setShift(int);
        void setWages(double);

        // Accessors
        /**
         * Accessor member function used to obtain worker's hourly wage. 
         * @return Worker's payments; unformatted raw double.
        */
        double getWages() const
            { return hourWages; }
        /**
         * Accessor member function used to obtain worker's shift as a string. 
         * @return Worker's job shift written out.
        */
        std::string getShiftFormat() const
            { return shiftHalves[shift]; }
        /**
         * Accessor member function used to obtain worker's shift as an int. 
         * @return Worker's job shift as a raw int value.
        */
        int getShiftNum() const
            { return shift; }
};

#endif
