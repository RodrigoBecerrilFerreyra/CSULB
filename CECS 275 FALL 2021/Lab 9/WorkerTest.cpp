/**
 * Program to generate employee profiles.
 * CECS 275 - Fall 2021
 * @author Ethan Hua
 * @author Rodrigo Becerril Ferreyra
 * @version 1.3
 */

#include <iostream>           // Used for terminal I/O
#include <iomanip>            // Used to format payment output to terminal
#include <string>             // Used for string object creation
#include "Employee.h"         // Base class; employee identification profiles
#include "ProductionWorker.h" // Derived class from "Employee"; work profiles

using namespace std;

// Function Prototypes
void massPrint(const Employee&);
void massPrint(const ProductionWorker&);

int main(){
    // Context
    cout << "Beginning tests. \n";
    cout << "======================================== \n";
    // Employee-class constructor; no parameters (default)
    cout << "Default Employee Constructor: \n";
    Employee defaultTest;
    massPrint(defaultTest);

    // Employee-class constructor; all parameters
    cout << "Populated Employee Constructor: \n";
    Employee fullTest("Johnny Test",605081427,"October 21, 2021");
    massPrint(fullTest);

    // ProductionWorker-class constructor; no parameters (default)
    cout << "Default Production Worker Constructor: \n";
    ProductionWorker defaultWorker;
    massPrint(defaultWorker);

    // ProductionWorker-class constructor; all parameters (incl. base class)
    // Note the order flows from base class to derived class.
    cout << "Populated Production Worker Constructor: \n";
    ProductionWorker defWork("Big Bob",963485712,"October 22, 2021",2,16.75);
    massPrint(defWork);

    // ProductionWorker-class constructor; all parameters (incl. base class)
    // Deliberate use of a known, invalid wage to show default override
    cout << "Production Worker Test (Negative Wage): \n";
    ProductionWorker noMons("Al Portland",275720172,
                            "September 21, 2021",2,-24.84);
    massPrint(noMons);

    // ProductionWorker-class constructor; all parameters (incl. base class)
    // Deliberate use of a known, invalid shift to show default override
    cout << "Production Worker Test (Invalid Shift): \n";
    ProductionWorker timeBreak("Thieu-Thanh Do",883368649,
                               "July 29, 2021",982,31.84);
    massPrint(timeBreak);

    cout << "Terminating... \n";
    return 0;
}

/**
 * Overloaded function variant used to output formatted and distinct block 
 * of all variables inherent to an Employee. Constant pass by address 
 * used as the program is only reading from object.
 * @param target  Employee-class object to be read out.
*/
void massPrint(const Employee &target){
    // Access all private variables
    string targetName = target.getName();
    int targetNumber = target.getNumber();
    string targetDate = target.getDate();
    // Terminal output
    cout << "======================================== \n";
    cout << "Employee Name : " << targetName << "\n";
    cout << "Employee ID   : " << targetNumber << "\n";
    cout << "Employee Hired: " << targetDate << "\n";
    cout << "======================================== \n";
}

/**
 * Overloaded function variant used to output formatted and distinct block 
 * of all variables inherent to a Production Worker. Constant pass by address 
 * used as the program is only reading from object.
 * @param target  ProductionWorker-class object to be read out.
*/
void massPrint(const ProductionWorker &target){
    // Access all private variables + inherited variables
    string targetName = target.getName();
    int targetNumber = target.getNumber();
    string targetDate = target.getDate();
    string targetShiftType = target.getShiftFormat();
    int targetShiftNum = target.getShiftNum();
    double targetPay = target.getWages();
    // Terminal output
    cout << "======================================== \n";
    cout << "Employee Name : " << targetName << "\n";
    cout << "Employee ID   : " << targetNumber << "\n";
    cout << "Employee Hired: " << targetDate << "\n";
    // Provide both name/string of shift type & corresponding value
    cout << "Employee Shift: " << targetShiftType << "/"  
         << targetShiftNum << "\n";
    // getWages() does not automatically format value
    cout << "Employee's Pay: USD$" << fixed << setprecision(2) 
         << targetPay << "\n";
    cout << "======================================== \n";
}
